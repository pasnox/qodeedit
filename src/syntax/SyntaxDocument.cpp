#include "SyntaxDocument.h"
#include "SyntaxParser.h"
#include "SyntaxTheme.h"
#include "QodeEdit.h"

#include <QXmlInputSource>
#include <QFileInfo>
#include <QDebug>

class Syntax::DocumentData : public QSharedData
{
public:
    static QString globalDefaultDeliminator;
    
    QString name;
    QString localizedName;
    QString section;
    Syntax::List extensions;
    QString version;
    QString kateVersion;
    QString indenter;
    Syntax::List mimeType;
    int priority;
    bool hidden;
    QString style;
    QString author;
    QString license;
    bool caseSensitive;
    //QString identifier;
    QString defaultDeliminator;
    bool finalyzed;
    Syntax::Highlighting highlighting;
    Syntax::General general;
    Syntax::SpellChecking spellChecking;
    
    DocumentData()
        : QSharedData(),
            priority( -1 ),
            hidden( false ),
            caseSensitive( true ),
            defaultDeliminator( Syntax::DocumentData::globalDefaultDeliminator ),
            finalyzed( false )
    {
    }
    
    DocumentData( const Syntax::DocumentData& other )
        : QSharedData( other ),
            QE_OTHER_INIT( name ),
            QE_OTHER_INIT( localizedName ),
            QE_OTHER_INIT( section ),
            QE_OTHER_INIT( extensions ),
            QE_OTHER_INIT( version ),
            QE_OTHER_INIT( kateVersion ),
            QE_OTHER_INIT( indenter ),
            QE_OTHER_INIT( mimeType ),
            QE_OTHER_INIT( priority ),
            QE_OTHER_INIT( hidden ),
            QE_OTHER_INIT( style ),
            QE_OTHER_INIT( author ),
            QE_OTHER_INIT( license ),
            QE_OTHER_INIT( caseSensitive ),
            //QE_OTHER_INIT( identifier ),
            QE_OTHER_INIT( defaultDeliminator ),
            QE_OTHER_INIT( finalyzed ),
            QE_OTHER_INIT( highlighting ),
            QE_OTHER_INIT( general ),
            QE_OTHER_INIT( spellChecking )
    {
    }
    
    virtual ~DocumentData() {
    }
};

QString Syntax::DocumentData::globalDefaultDeliminator( ".():!+,-<=>%&*/;?[]^{|}~\\ \t" );


QE_IMPL_SHARED_CLASS( Document )

Syntax::Document::~Document()
{
}

bool Syntax::Document::operator<( const Syntax::Document& other ) const
{
    // HINT: compare priority too ?
    return QodeEdit::localeAwareStringLessThan(
        d->localizedName.isEmpty() ? d->name : d->localizedName,
        other.d->localizedName.isEmpty() ? other.d->name : other.d->localizedName
    );
}

QE_IMPL_MEMBER( QString, name, Document )
QE_IMPL_MEMBER( QString, localizedName, Document )
QE_IMPL_MEMBER( QString, section, Document )
QE_IMPL_MEMBER( Syntax::List, extensions, Document )
QE_IMPL_MEMBER( QString, version, Document )
QE_IMPL_MEMBER( QString, kateVersion, Document )
QE_IMPL_MEMBER( QString, indenter, Document )
QE_IMPL_MEMBER( Syntax::List, mimeType, Document )
QE_IMPL_MEMBER( int, priority, Document )
QE_IMPL_MEMBER( bool, hidden, Document )
QE_IMPL_MEMBER( QString, style, Document )
QE_IMPL_MEMBER( QString, author, Document )
QE_IMPL_MEMBER( QString, license, Document )
QE_IMPL_MEMBER( bool, caseSensitive, Document )
//QE_IMPL_MEMBER( QString, identifier, Document )
QE_IMPL_MEMBER( QString, defaultDeliminator, Document )
QE_IMPL_MEMBER( bool, finalyzed, Document )
QE_IMPL_MEMBER( Syntax::Highlighting, highlighting, Document )
QE_IMPL_MEMBER( Syntax::General, general, Document )
QE_IMPL_MEMBER( Syntax::SpellChecking, spellChecking, Document )

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
            *error = QString( "%1: Can't parse file %2: %3" ).arg( Q_FUNC_INFO ).arg( filePath ).arg( xmlReader.errorHandler()->errorString() );
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
