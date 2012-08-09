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
    
    virtual ~DocumentData()
    {
    }
};

Syntax::Document::Document()
    : d( new Syntax::DocumentData ),
        SYNTAX_D_INIT( name ),
        SYNTAX_D_INIT( localizedName ),
        SYNTAX_D_INIT( section ),
        SYNTAX_D_INIT( extensions ),
        SYNTAX_D_INIT( version ),
        SYNTAX_D_INIT( kateVersion ),
        SYNTAX_D_INIT( indenter ),
        SYNTAX_D_INIT( mimeTypes ),
        SYNTAX_D_INIT( priority ),
        SYNTAX_D_INIT( hidden ),
        SYNTAX_D_INIT( style ),
        SYNTAX_D_INIT( author ),
        SYNTAX_D_INIT( license ),
        SYNTAX_D_INIT( caseSensitive ),
        //SYNTAX_D_INIT( identifier ),
        SYNTAX_D_INIT( finalyzed ),
        SYNTAX_D_INIT( highlighting ),
        SYNTAX_D_INIT( general ),
        SYNTAX_D_INIT( spellChecking )
{
}

Syntax::Document::Document( const Syntax::Document& other )
    : d( other.d ),
        SYNTAX_D_INIT( name ),
        SYNTAX_D_INIT( localizedName ),
        SYNTAX_D_INIT( section ),
        SYNTAX_D_INIT( extensions ),
        SYNTAX_D_INIT( version ),
        SYNTAX_D_INIT( kateVersion ),
        SYNTAX_D_INIT( indenter ),
        SYNTAX_D_INIT( mimeTypes ),
        SYNTAX_D_INIT( priority ),
        SYNTAX_D_INIT( hidden ),
        SYNTAX_D_INIT( style ),
        SYNTAX_D_INIT( author ),
        SYNTAX_D_INIT( license ),
        SYNTAX_D_INIT( caseSensitive ),
        //SYNTAX_D_INIT( identifier ),
        SYNTAX_D_INIT( finalyzed ),
        SYNTAX_D_INIT( highlighting ),
        SYNTAX_D_INIT( general ),
        SYNTAX_D_INIT( spellChecking )
{
}

Syntax::Document::~Document()
{
}

Syntax::Document& Syntax::Document::operator=( const Syntax::Document& other )
{
    if ( this != &other ) {
        d = other.d;
        SYNTAX_D_COPY( name );
        SYNTAX_D_COPY( localizedName );
        SYNTAX_D_COPY( section );
        SYNTAX_D_COPY( extensions );
        SYNTAX_D_COPY( version );
        SYNTAX_D_COPY( kateVersion );
        SYNTAX_D_COPY( indenter );
        SYNTAX_D_COPY( mimeTypes );
        SYNTAX_D_COPY( priority );
        SYNTAX_D_COPY( hidden );
        SYNTAX_D_COPY( style );
        SYNTAX_D_COPY( author );
        SYNTAX_D_COPY( license );
        SYNTAX_D_COPY( caseSensitive );
        //SYNTAX_D_COPY( identifier );
        SYNTAX_D_COPY( finalyzed );
        SYNTAX_D_COPY( highlighting );
        SYNTAX_D_COPY( general );
        SYNTAX_D_COPY( spellChecking );
    }
    
    return *this;
}

bool Syntax::Document::operator<( const Syntax::Document& other ) const
{
    // HINT: compare priority too ?
    return QodeEdit::localeAwareStringLessThan(
        localizedName.isEmpty() ? name : localizedName,
        other.localizedName.isEmpty() ? other.name : other.localizedName
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
            Q_ASSERT( !document.name.isEmpty() );
            
            Syntax::Document& currentDocument = documents[ document.name ];
            
            if ( QodeEdit::versionStringLessThan( currentDocument.version, document.version ) ) {
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
