#include "SyntaxDocument.h"
#include "SyntaxParser.h"

#include <QXmlInputSource>
#include <QTime>
#include <QFileInfo>
#include <QDebug>

Syntax::Document::Document()
{
}

Syntax::Document::~Document()
{
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
        parser.debug();
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
            documents[ document.name ] = document;
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
    parser.debug();
#endif
    
    return documents;
}
