#include "SyntaxDocument.h"
#include "SyntaxParser.h"
#include "QodeEdit.h"

#include <QXmlInputSource>
#include <QFileInfo>
#include <QDebug>

Syntax::Document::Document()
{
    priority = -1;
    hidden = false;
    caseSensitive = false;
}

Syntax::Document::~Document()
{
}

bool Syntax::Document::operator==( const Syntax::Document& other ) const
{
    return name == other.name &&
        localizedName == other.localizedName &&
        section == other.section &&
        extensions == other.extensions &&
        version == other.version &&
        kateVersion == other.kateVersion &&
        indenter == other.indenter &&
        mimeTypes == other.mimeTypes &&
        priority == other.priority &&
        hidden == other.hidden &&
        style == other.style &&
        author == other.author &&
        license == other.license &&
        caseSensitive == other.caseSensitive &&
        //identifier == other.identifier &&
        highlighting == other.highlighting &&
        general == other.general &&
        spellChecking == other.spellChecking
    ;
}

bool Syntax::Document::operator!=( const Syntax::Document& other ) const
{
    return !operator==( other );
}

bool Syntax::Document::operator<( const Syntax::Document& other ) const
{
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
#if !defined( QT_NO_DEBUG )
        qWarning() << QString( "--- Parsing %1" ).arg( QFileInfo( filePath ).fileName() ).toLocal8Bit().constData();
#endif
        
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
