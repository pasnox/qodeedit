#include "SyntaxParser.h"
#include "SyntaxDocument.h"

#include <QDebug>

bool caseInsensitiveComparison( const QString& left, const QString& right ) {
    return QString::compare( left, right, Qt::CaseInsensitive ) == 0;
}

// ParserPrivate

class Syntax::ParserPrivate {
public:
    const Syntax::List ruleNames;
    Syntax::Document* document;
    QString error;
    QString listName;
    QString contextName;
    QString text;
    
    ParserPrivate( Syntax::Parser* _parser, Syntax::Document* _document )
        : ruleNames( Syntax::List()
            << "anychar" // AnyChar
            
            << "detect2chars" // Detect2Chars
            << "detectchar" // DetectChar
            << "detectidentifier" // DetectIdentifier
            << "detectspaces" // DetectSpaces
            
            << "float" // Float
            
            << "hlcchar" // HlCChar
            << "hlchex" // HlCHex
            << "hlcoct" // HlCOct
            << "hlcstringchar" // HlCStringChar
            
            << "includerules" // IncludeRules
            << "int" // Int
            
            << "keyword" // Keyword
            
            << "linecontinue" // LineContinue
            
            << "rangedetect" // RangeDetect
            << "regexpr" // RegExpr
            
            << "stringdetect" // StringDetect
            ),
            document( _document ),
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
    d->contextName.clear();
    d->text.clear();
    return true;
}

bool Syntax::Parser::endDocument()
{
    d->error.clear();
    d->listName.clear();
    d->contextName.clear();
    d->text.clear();
    return true;
}

bool Syntax::Parser::startElement( const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& atts )
{
    //qWarning() << namespaceURI << localName << qName;
    
    if ( caseInsensitiveComparison( qName, "language" )) {
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            if ( caseInsensitiveComparison( name, "name" ) ) {
                d->document->name = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "section" ) ) {
                d->document->section = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "version" ) ) {
                d->document->version = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "kateVersion" ) ) {
                d->document->kateVersion = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "indenter" ) ) {
                d->document->indenter = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "mimeType" ) ) {
                d->document->mimeTypes = atts.value( i ).split( ";", QString::SkipEmptyParts ).toSet();
            }
            else if ( caseInsensitiveComparison( name, "extensions" ) ) {
                d->document->extensions = atts.value( i ).split( ";", QString::SkipEmptyParts ).toSet();
            }
            else if ( caseInsensitiveComparison( name, "priority" ) ) {
                d->document->priority = atts.value( i ).toInt();
            }
            else if ( caseInsensitiveComparison( name, "author" ) ) {
                d->document->author = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "license" ) ) {
                d->document->license = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "caseSensitive" ) ) {
                d->document->caseSensitive = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "hidden" ) ) {
                d->document->hidden = atts.value( i );
            }
            else {
                d->error = QString( "%1: Unhandled language attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
                return false;
            }
        }
    }
    else if ( caseInsensitiveComparison( qName, "highlighting" ) ) {
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            d->error = QString( "%1: Unhandled highlighting attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
            return false;
        }
    }
    else if ( caseInsensitiveComparison( qName, "list" ) ) {
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            if ( caseInsensitiveComparison( name, "name" ) ) {
                d->listName = atts.value( i );
            }
            else {
                d->error = QString( "%1: Unhandled list attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
                return false;
            }
        }
    }
    else if ( caseInsensitiveComparison( qName, "item" ) ) {
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            d->error = QString( "%1: Unhandled item attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
            return false;
        }
    }
    else if ( caseInsensitiveComparison( qName, "contexts" ) ) {
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            d->error = QString( "%1: Unhandled contexts attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
            return false;
        }
    }
    else if ( caseInsensitiveComparison( qName, "context" ) ) {
        Syntax::Context context;
        
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            if ( caseInsensitiveComparison( name, "name" ) ) {
                d->contextName = atts.value( i );
                context.name = d->contextName;
            }
            else if ( caseInsensitiveComparison( name, "lineEndContext" ) ) {
                context.lineEndContext = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "attribute" ) ) {
                context.attribute = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "fallThrough" ) ) {
                context.fallThrough = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "fallThroughContext" ) ) {
                context.fallThroughContext = atts.value( i );
            }
            else {
                d->error = QString( "%1: Unhandled context attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
                return false;
            }
        }
        
        d->document->highlighting.contexts[ context.name ] = context;
    }
    else if ( d->ruleNames.contains( qName.toLower() ) ) {
        Q_ASSERT( !d->contextName.isEmpty() );
        Syntax::Context& context = d->document->highlighting.contexts[ d->contextName ];
        Syntax::Rule rule;
        
        rule.type = qName;
        
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            if ( caseInsensitiveComparison( name, "attribute" ) ) {
                rule.attribute = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "context" ) ) {
                rule.context = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "string" ) ) {
                rule.string = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "beginRegion" ) ) {
                rule.beginRegion = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "firstNonSpace" ) ) {
                rule.firstNonSpace = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "char" ) ) {
                rule.char_ = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "lookAhead" ) ) {
                rule.lookAhead = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "endRegion" ) ) {
                rule.endRegion = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "insensitive" ) ) {
                rule.insensitive = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "char1" ) ) {
                rule.char1 = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "column" ) ) {
                rule.column = atts.value( i );
            }
            else {
                d->error = QString( "%1: Unhandled rule attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
                return false;
            }
        }
        
        context.rules << rule;
    }
    else if ( caseInsensitiveComparison( qName, "itemDatas" ) ) {
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            d->error = QString( "%1: Unhandled itemDatas attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
            return false;
        }
    }
    else if ( caseInsensitiveComparison( qName, "itemData" ) ) {
        Syntax::ItemData itemData;
        
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            if ( caseInsensitiveComparison( name, "name" ) ) {
                itemData.name = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "defStyleNum" ) ) {
                itemData.defStyleNum = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "spellChecking" ) ) {
                itemData.spellChecking = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "color" ) ) {
                itemData.color = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "selColor" ) ) {
                itemData.selColor = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "bold" ) ) {
                itemData.bold = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "italic" ) ) {
                itemData.italic = atts.value( i );
            }
            else {
                d->error = QString( "%1: Unhandled itemData attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
                return false;
            }
        }
        
        d->document->highlighting.itemDatas[ itemData.name ] = itemData;
    }
    else if ( caseInsensitiveComparison( qName, "general" ) ) {
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            d->error = QString( "%1: Unhandled general attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
            return false;
        }
    }
    else if ( caseInsensitiveComparison( qName, "comments" ) ) {
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            d->error = QString( "%1: Unhandled comments attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
            return false;
        }
    }
    else if ( caseInsensitiveComparison( qName, "comment" ) ) {
        Syntax::Comment comment;
        
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            if ( caseInsensitiveComparison( name, "name" ) ) {
                comment.name = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "start" ) ) {
                comment.start = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "end" ) ) {
                comment.end = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "region" ) ) {
                comment.region = atts.value( i );
            }
            else {
                d->error = QString( "%1: Unhandled comment attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
                return false;
            }
        }
        
        d->document->general.comments[ comment.name ] = comment;
    }
    else if ( caseInsensitiveComparison( qName, "keywords" ) ) {
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            if ( caseInsensitiveComparison( name, "caseSensitive" ) ) {
                d->document->general.keywords.caseSensitive = atts.value( i );
            }
            else {
                d->error = QString( "%1: Unhandled comment attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
                return false;
            }
        }
    }
    else {
        d->error = QString( "%1: Unhandled starting qName element: %2" ).arg( Q_FUNC_INFO ).arg( qName );
        return false;
    }
    
    return QXmlDefaultHandler::startElement( namespaceURI, localName, qName, atts );
}

bool Syntax::Parser::endElement( const QString& namespaceURI, const QString& localName, const QString& qName )
{
    if ( caseInsensitiveComparison( qName, "item" ) ) {
        Q_ASSERT( !d->listName.isEmpty() );
        d->document->highlighting.lists[ d->listName ] << QString( " %1 " ).arg( d->text.trimmed() );
        d->text.clear();
    }
    else if ( caseInsensitiveComparison( qName, "list" ) ) {
        d->listName.clear();
    }
    else if ( d->ruleNames.contains( qName.toLower() ) ) {
    }
    else if ( caseInsensitiveComparison( qName, "context" ) ) {
        d->contextName.clear();
    }
    else if ( caseInsensitiveComparison( qName, "contexts" ) ) {
    }
    else if ( caseInsensitiveComparison( qName, "itemData" ) ) {
    }
    else if ( caseInsensitiveComparison( qName, "itemDatas" ) ) {
    }
    else if ( caseInsensitiveComparison( qName, "highlighting" ) ) {
    }
    else if ( caseInsensitiveComparison( qName, "comment" ) ) {
    }
    else if ( caseInsensitiveComparison( qName, "comments" ) ) {
    }
    else if ( caseInsensitiveComparison( qName, "keywords" ) ) {
    }
    else if ( caseInsensitiveComparison( qName, "general" ) ) {
    }
    else if ( caseInsensitiveComparison( qName, "language" ) ) {
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
