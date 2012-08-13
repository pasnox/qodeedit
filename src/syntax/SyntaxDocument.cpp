#include "SyntaxDocument.h"
#include "SyntaxParser.h"
#include "QodeEdit.h"

#include <QXmlInputSource>
#include <QFileInfo>
#include <QDebug>

class Syntax::DocumentData : public QSharedData
{
public:
    QString name;
    QString localizedName;
    QString section;
    Syntax::List extensions;
    QString version;
    QString kateVersion;
    QString indenter;
    Syntax::List mimeTypes;
    int priority;
    bool hidden;
    QString style;
    QString author;
    QString license;
    bool caseSensitive;
    //QString identifier;
    bool finalyzed;
    Syntax::Highlighting highlighting;
    Syntax::General general;
    Syntax::SpellChecking spellChecking;
    
    DocumentData()
        : QSharedData(),
            priority( -1 ),
            hidden( false ),
            caseSensitive( false ),
            finalyzed( false )
    {
    }
    
    DocumentData( const Syntax::DocumentData& other )
        : QSharedData( other ),
            SYNTAX_OTHER_INIT( name ),
            SYNTAX_OTHER_INIT( localizedName ),
            SYNTAX_OTHER_INIT( section ),
            SYNTAX_OTHER_INIT( extensions ),
            SYNTAX_OTHER_INIT( version ),
            SYNTAX_OTHER_INIT( kateVersion ),
            SYNTAX_OTHER_INIT( indenter ),
            SYNTAX_OTHER_INIT( mimeTypes ),
            SYNTAX_OTHER_INIT( priority ),
            SYNTAX_OTHER_INIT( hidden ),
            SYNTAX_OTHER_INIT( style ),
            SYNTAX_OTHER_INIT( author ),
            SYNTAX_OTHER_INIT( license ),
            SYNTAX_OTHER_INIT( caseSensitive ),
            //SYNTAX_OTHER_INIT( identifier ),
            SYNTAX_OTHER_INIT( finalyzed ),
            SYNTAX_OTHER_INIT( highlighting ),
            SYNTAX_OTHER_INIT( general ),
            SYNTAX_OTHER_INIT( spellChecking )
    {
    }
    
    virtual ~DocumentData() {
    }
};

Syntax::Document::Document()
    : d( new Syntax::DocumentData )
{
}

Syntax::Document::Document( const Syntax::Document& other )
    : d( other.d )
{
}

Syntax::Document::~Document()
{
}

SYNTAX_IMPL_MEMBER( QString, name, Document )
SYNTAX_IMPL_MEMBER( QString, localizedName, Document )
SYNTAX_IMPL_MEMBER( QString, section, Document )
SYNTAX_IMPL_MEMBER( Syntax::List, extensions, Document )
SYNTAX_IMPL_MEMBER( QString, version, Document )
SYNTAX_IMPL_MEMBER( QString, kateVersion, Document )
SYNTAX_IMPL_MEMBER( QString, indenter, Document )
SYNTAX_IMPL_MEMBER( Syntax::List, mimeTypes, Document )
SYNTAX_IMPL_MEMBER( int, priority, Document )
SYNTAX_IMPL_MEMBER( bool, hidden, Document )
SYNTAX_IMPL_MEMBER( QString, style, Document )
SYNTAX_IMPL_MEMBER( QString, author, Document )
SYNTAX_IMPL_MEMBER( QString, license, Document )
SYNTAX_IMPL_MEMBER( bool, caseSensitive, Document )
//SYNTAX_IMPL_MEMBER( QString, identifier, Document )
SYNTAX_IMPL_MEMBER( bool, finalyzed, Document )
SYNTAX_IMPL_MEMBER( Syntax::Highlighting, highlighting, Document )
SYNTAX_IMPL_MEMBER( Syntax::General, general, Document )
SYNTAX_IMPL_MEMBER( Syntax::SpellChecking, spellChecking, Document )
SYNTAX_IMPL_OPERATORS( Document )

bool Syntax::Document::operator<( const Syntax::Document& other ) const
{
    // HINT: compare priority too ?
    return QodeEdit::localeAwareStringLessThan(
        d->localizedName.isEmpty() ? d->name : d->localizedName,
        other.d->localizedName.isEmpty() ? other.d->name : other.d->localizedName
    );
}

bool Syntax::Document::open( const QString& filePath, QString* error )
{
    QFile file( filePath );
    
    if ( !file.exists() ) {
        if ( error ) {
            *error = QString( "%1: File doesn't exists %2" ).arg( Q_FUNC_INFO ).arg( filePath );
        }
        
#if !defined( QT_NO_DEBUG )
        qWarning( "%s: File doesn't exists %s", Q_FUNC_INFO, qPrintable( filePath ) );
#endif
        return false;
    }
    
    if ( !file.open( QIODevice::ReadOnly ) ) {
        if ( error ) {
            *error = QString( "%1: Can't open file %2" ).arg( Q_FUNC_INFO ).arg( filePath );
        }
        
#if !defined( QT_NO_DEBUG )
        qWarning( "%s: Can't open file %s", Q_FUNC_INFO, qPrintable( filePath ) );
#endif
        return false;
    }
    
    Syntax::Reader xmlReader;
    QXmlInputSource source( &file );
    Syntax::Parser parser;
    
    xmlReader.setContentHandler( &parser );
    xmlReader.setDTDHandler( &parser );
    xmlReader.setDeclHandler( &parser );
    xmlReader.setEntityResolver( &parser );
    xmlReader.setErrorHandler( &parser );
    xmlReader.setLexicalHandler( &parser );
    
    if ( xmlReader.parse( this, source ) ) {
#if !defined( QT_NO_DEBUG )
        //parser.debug();
#endif
        return true;
    }
    
    if ( error ) {
        *error = QString( "%1: Can't parse file %2" ).arg( Q_FUNC_INFO ).arg( filePath );
    }
    
#if !defined( QT_NO_DEBUG )
    qWarning( "%s: Can't parse file %s", Q_FUNC_INFO, qPrintable( filePath ) );
#endif
    
    return false;
}

QHash<QString, Syntax::Document> Syntax::Document::open( const QStringList& filePaths, QString* error )
{
    QHash<QString, Syntax::Document> documents;
    Syntax::Reader xmlReader;
    Syntax::Parser parser;
    
    xmlReader.setContentHandler( &parser );
    xmlReader.setDTDHandler( &parser );
    xmlReader.setDeclHandler( &parser );
    xmlReader.setEntityResolver( &parser );
    xmlReader.setErrorHandler( &parser );
    xmlReader.setLexicalHandler( &parser );
    
    foreach ( const QString& filePath, filePaths ) {
        QFile file( filePath );
        
        if ( !file.exists() ) {
            if ( error ) {
                *error = QString( "%1: File doesn't exists %2" ).arg( Q_FUNC_INFO ).arg( filePath );
            }
            
#if !defined( QT_NO_DEBUG )
            qWarning( "%s: File doesn't exists %s", Q_FUNC_INFO, qPrintable( filePath ) );
#endif
            Q_ASSERT( 0 );
            continue;
        }
        
        if ( !file.open( QIODevice::ReadOnly ) ) {
            if ( error ) {
                *error = QString( "%1: Can't open file %2" ).arg( Q_FUNC_INFO ).arg( filePath );
            }
            
#if !defined( QT_NO_DEBUG )
            qWarning( "%s: Can't open file %s", Q_FUNC_INFO, qPrintable( filePath ) );
#endif
            Q_ASSERT( 0 );
            continue;
        }
        
        Syntax::Document document;
        QXmlInputSource source( &file );
        
        if ( xmlReader.parse( &document, source ) ) {
            Q_ASSERT( !document.name().isEmpty() );
            
            Syntax::Document& currentDocument = documents[ document.name() ];
            
            if ( QodeEdit::versionStringLessThan( currentDocument.version(), document.version() ) ) {
                currentDocument = document;
            }
            
            continue;
        }
        
        if ( error ) {
            *error = QString( "%1: Can't parse file %2" ).arg( Q_FUNC_INFO ).arg( filePath );
        }
        
#if !defined( QT_NO_DEBUG )
        qWarning( "%s: Can't parse file %s", Q_FUNC_INFO, qPrintable( filePath ) );
#endif
        Q_ASSERT( 0 );
    }
    
#if !defined( QT_NO_DEBUG )
    //parser.debug();
#endif
    
    return documents;
}
