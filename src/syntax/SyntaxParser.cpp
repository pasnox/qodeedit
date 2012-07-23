#include "SyntaxParser.h"
#include "SyntaxDocument.h"

#include <QDebug>

// ParserPrivate

class Syntax::ParserPrivate {
public:
    Syntax::Document* document;
    QString error;
    QString listName;
    QString text;
    
    ParserPrivate( Syntax::Parser* _parser, Syntax::Document* _document )
        : document( _document ),
            parser( _parser )
    {
        Q_ASSERT( document );
    }
    
private:
    Syntax::Parser* parser;
};

// Parser

Syntax::Parser::Parser( Syntax::Document* document )
    : QXmlDefaultHandler(),
        d( new Syntax::ParserPrivate( this, document ) )
{
}

Syntax::Parser::~Parser()
{
    delete d;
}

bool Syntax::Parser::attributeDecl( const QString& eName, const QString& aName, const QString& type, const QString& valueDefault, const QString& value )
{
    return QXmlDefaultHandler::attributeDecl( eName, aName, type, valueDefault, value );
}

bool Syntax::Parser::fatalError( const QXmlParseException& exception )
{
    qWarning()
        << "Fatal error on line" << exception.lineNumber()
        << ", column" << exception.columnNumber()
        << ":" << exception.message()
        << exception.publicId()
        << exception.systemId()
    ;

    return false;
}

bool Syntax::Parser::characters( const QString& ch )
{
    d->text += ch;
    return true;
}

bool Syntax::Parser::startDocument()
{
    d->error.clear();
    d->listName.clear();
    d->text.clear();
    return true;
}

bool Syntax::Parser::endDocument()
{
    return true;
}

bool Syntax::Parser::startElement( const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& atts )
{
    //qWarning() << namespaceURI << localName << qName;
    
    if ( qName == "language" ) {
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            if ( name == "name" ) {
                d->document->name = atts.value( i );
            }
            else if ( name == "section" ) {
                d->document->section = atts.value( i );
            }
            else if ( name == "version" ) {
                d->document->version = atts.value( i );
            }
            else if ( name == "kateversion" ) {
                d->document->kateVersion = atts.value( i );
            }
            else if ( name == "indenter" ) {
                d->document->indenter = atts.value( i );
            }
            else if ( name == "mimetype" ) {
                d->document->mimeTypes = atts.value( i ).split( ";", QString::SkipEmptyParts ).toSet();
            }
            else if ( name == "extensions" ) {
                d->document->extensions = atts.value( i ).split( ";", QString::SkipEmptyParts ).toSet();
            }
            else if ( name == "priority" ) {
                d->document->priority = atts.value( i ).toInt();
            }
            else {
                d->error = QString( "%1: Unhandled language attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
                return false;
            }
        }
    }
    else if ( qName == "highlighting" ) {
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            d->error = QString( "%1: Unhandled highlighting attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
            return false;
        }
    }
    else if ( qName == "list" ) {
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            if ( name == "name" ) {
                d->listName = atts.value( i );
            }
            else {
                d->error = QString( "%1: Unhandled list attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
                return false;
            }
        }
    }
    else if ( qName == "item" ) {
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            d->error = QString( "%1: Unhandled item attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
            return false;
        }
    }
    else if ( qName == "contexts" ) {
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            d->error = QString( "%1: Unhandled contexts attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
            return false;
        }
    }
    else if ( qName == "context" ) {
        Syntax::Context context;
        
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            if ( name == "name" ) {
                context.name = atts.value( i );
            }
            else if ( name == "lineEndContext" ) {
                context.lineEndContext = atts.value( i );
            }
            else if ( name == "attribute" ) {
                context.attribute = atts.value( i );
            }
            else {
                d->error = QString( "%1: Unhandled context attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
                return false;
            }
        }
        
        d->document->highlighting.contexts[ context.name ] = context;
    }
    else if ( qName == "DetectSpaces" ) {
        /*Syntax::Rule rule;
        
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            if ( name == "name" ) {
                context.name = atts.value( i );
            }
            else if ( name == "lineEndContext" ) {
                context.lineEndContext = atts.value( i );
            }
            else if ( name == "attribute" ) {
                context.attribute = atts.value( i );
            }
            else {
                d->error = QString( "%1: Unhandled context attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
                return false;
            }
        }
        
        d->document->highlighting.contexts[ context.name ] = context;*/
    }
    else {
        d->error = QString( "%1: Unhandled starting qName element: %2" ).arg( Q_FUNC_INFO ).arg( qName );
        return false;
    }
    
    return QXmlDefaultHandler::startElement( namespaceURI, localName, qName, atts );
}

bool Syntax::Parser::endElement( const QString& namespaceURI, const QString& localName, const QString& qName )
{
    if ( qName == "language" ) {
    }
    else if ( qName == "highlighting" ) {
    }
    else if ( qName == "list" ) {
    }
    else if ( qName == "item" ) {
        Q_ASSERT( !d->listName.isEmpty() );
        d->document->highlighting.lists[ d->listName ] << d->text;
        d->text.clear();
    }
    else if ( qName == "contexts" ) {
    }
    else if ( qName == "context" ) {
    }
    else {
        d->error = QString( "%1: Unhandled ending qName element: %2" ).arg( Q_FUNC_INFO ).arg( qName );
        return false;
    }
    
    return QXmlDefaultHandler::endElement( namespaceURI, localName, qName );
}

bool Syntax::Parser::comment( const QString& ch )
{
    return QXmlDefaultHandler::comment( ch );
}

bool Syntax::Parser::endCDATA()
{
    return QXmlDefaultHandler::endCDATA();
}

bool Syntax::Parser::endDTD()
{
    return QXmlDefaultHandler::endDTD();
}

bool Syntax::Parser::endEntity( const QString& name )
{
    return QXmlDefaultHandler::endEntity( name );
}

bool Syntax::Parser::endPrefixMapping( const QString& prefix )
{
    return QXmlDefaultHandler::endPrefixMapping( prefix );
}

bool Syntax::Parser::error( const QXmlParseException& exception )
{
    qWarning()
        << "Error on line" << exception.lineNumber()
        << ", column" << exception.columnNumber()
        << ":" << exception.message()
        << exception.publicId()
        << exception.systemId()
    ;
    
    return QXmlDefaultHandler::error( exception );
}

QString Syntax::Parser::errorString() const
{
    return d->error;
}

bool Syntax::Parser::externalEntityDecl( const QString& name, const QString& publicId, const QString& systemId )
{
    return QXmlDefaultHandler::externalEntityDecl( name, publicId, systemId );
}

bool Syntax::Parser::ignorableWhitespace( const QString& ch )
{
    return QXmlDefaultHandler::ignorableWhitespace( ch );
}

bool Syntax::Parser::internalEntityDecl( const QString& name, const QString& value )
{
    return QXmlDefaultHandler::internalEntityDecl( name, value );
}

bool Syntax::Parser::notationDecl( const QString& name, const QString& publicId, const QString& systemId )
{
    return QXmlDefaultHandler::notationDecl( name, publicId, systemId );
}

bool Syntax::Parser::processingInstruction( const QString& target, const QString& data )
{
    return QXmlDefaultHandler::processingInstruction( target, data );
}

bool Syntax::Parser::resolveEntity( const QString& publicId, const QString& systemId, QXmlInputSource*& ret )
{
    return QXmlDefaultHandler::resolveEntity( publicId, systemId, ret );
}

void Syntax::Parser::setDocumentLocator( QXmlLocator* locator )
{
    QXmlDefaultHandler::setDocumentLocator( locator );
}

bool Syntax::Parser::skippedEntity( const QString& name )
{
    return QXmlDefaultHandler::skippedEntity( name );
}

bool Syntax::Parser::startCDATA()
{
    return QXmlDefaultHandler::startCDATA();
}

bool Syntax::Parser::startDTD( const QString& name, const QString& publicId, const QString& systemId )
{
    return QXmlDefaultHandler::startDTD( name, publicId, systemId );
}

bool Syntax::Parser::startEntity( const QString& name )
{
    return QXmlDefaultHandler::startEntity( name );
}

bool Syntax::Parser::startPrefixMapping( const QString& prefix, const QString& uri )
{
    return QXmlDefaultHandler::startPrefixMapping( prefix, uri );
}

bool Syntax::Parser::unparsedEntityDecl( const QString& name, const QString& publicId, const QString& systemId, const QString& notationName )
{
    return QXmlDefaultHandler::unparsedEntityDecl( name, publicId, systemId, notationName );
}

bool Syntax::Parser::warning( const QXmlParseException& exception )
{
    qWarning()
        << "Warning on line" << exception.lineNumber()
        << ", column" << exception.columnNumber()
        << ":" << exception.message()
        << exception.publicId()
        << exception.systemId()
    ;
    
    return QXmlDefaultHandler::warning( exception );
}
