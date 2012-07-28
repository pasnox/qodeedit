#include "SyntaxDocument.h"
#include "SyntaxParser.h"

#include <QXmlInputSource>
#include <QTime>
#include <QFileInfo>
#include <QDebug>

bool versionLessThan( const QString& left, const QString& right ) {
    if ( left == right ) {
        return false;
    }
    
    const QStringList leftParts = left.split( "." );
    const QStringList rightParts = right.split( "." );
    
    // major
    if ( leftParts.value( 0 ).toInt() != rightParts.value( 0 ).toInt() ) {
        return leftParts.value( 0 ).toInt() < rightParts.value( 0 ).toInt();
    }
    // minor
    else if ( leftParts.value( 1 ).toInt() != rightParts.value( 1 ).toInt() ) {
        return leftParts.value( 1 ).toInt() < rightParts.value( 1 ).toInt();
    }
    // patch
    else if ( leftParts.value( 2 ).toInt() != rightParts.value( 2 ).toInt() ) {
        return leftParts.value( 2 ).toInt() < rightParts.value( 2 ).toInt();
    }
    // build
    else if ( leftParts.value( 3 ).toInt() != rightParts.value( 3 ).toInt() ) {
        return leftParts.value( 3 ).toInt() < rightParts.value( 3 ).toInt();
    }
    // extra
    else if ( leftParts.value( 4 ).isEmpty() && !rightParts.value( 4 ).isEmpty() ) {
        return false;
    }
    // extra
    else if ( !leftParts.value( 4 ).isEmpty() && rightParts.value( 4 ).isEmpty() ) {
        return true;
    }
    
    // extra
    return leftParts.value( 4 ) < rightParts.value( 4 ); // not the best but afaik ;)
}

Syntax::Document::Document()
{
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
    return QString::localeAwareCompare( name, other.name ) < 0;
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
    
    QTime time;
    time.start();
    
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
            
            if ( versionLessThan( currentDocument.version, document.version ) ) {
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
    qWarning() << QString( "%1 files parsed in %2 seconds" ).arg( filePaths.count() ).arg( time.elapsed() /1000.0 ).toLocal8Bit().constData();
    //parser.debug();
#endif
    
    return documents;
}
