#include "SyntaxDocument.h"
#include "SyntaxParser.h"

#include <QXmlInputSource>

Syntax::Document::Document()
{
}

Syntax::Document::~Document()
{
}

bool Syntax::Document::open( const QString& filePath )
{
    QFile file( filePath );
    
    if ( !file.exists() ) {
        qWarning( "%s: File doesn't exists %s", Q_FUNC_INFO, qPrintable( filePath ) );
        return false;
    }
    
    if ( !file.open( QIODevice::ReadOnly ) ) {
        qWarning( "%s: Can't open file %s", Q_FUNC_INFO, qPrintable( filePath ) );
        return false;
    }
    
    Syntax::Document document;
    QXmlSimpleReader xmlReader;
    QXmlInputSource source( &file );
    Syntax::Parser parser( &document );
    
    xmlReader.setContentHandler( &parser );
    xmlReader.setDTDHandler( &parser );
    xmlReader.setDeclHandler( &parser );
    xmlReader.setEntityResolver( &parser );
    xmlReader.setErrorHandler( &parser );
    xmlReader.setLexicalHandler( &parser );
    
    if ( xmlReader.parse( source ) ) {
        *this = document;
        return true;
    }
    
    return false;
}
