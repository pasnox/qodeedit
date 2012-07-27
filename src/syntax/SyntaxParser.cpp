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
    QMap<QString, int> counts;
    
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
            
            << "worddetect" // WordDetect
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
    d->counts.clear();
    return true;
}

bool Syntax::Parser::endDocument()
{
    Q_ASSERT( d->counts.value( "highlighting" ) <= 1 );
    Q_ASSERT( d->counts.value( "general" ) <= 1 );
    Q_ASSERT( d->counts.value( "spellchecking" ) <= 1 );
    Q_ASSERT( d->counts.value( "keywords" ) <= 1 );
    Q_ASSERT( d->counts.value( "folding" ) <= 1 );
    Q_ASSERT( d->counts.value( "indentation" ) <= 1 );
    Q_ASSERT( d->counts.value( "configuration" ) <= 1 );
    
    d->error.clear();
    d->listName.clear();
    d->contextName.clear();
    d->text.clear();
    d->counts.clear();
    return true;
}

bool Syntax::Parser::startElement( const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& atts )
{
    d->counts[ qName.toLower() ]++;
    
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
            else if ( caseInsensitiveComparison( name, "style" ) ) {
                d->document->style = atts.value( i );
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
            else if ( caseInsensitiveComparison( name, "dynamic" ) ) {
                context.dynamic = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "noIndentationBasedFolding" ) ) {
                context.noIndentationBasedFolding = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "caseSensitive" ) ) {
                context.caseSensitive = atts.value( i );
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
            else if ( caseInsensitiveComparison( name, "context" ) || caseInsensitiveComparison( name, "contex" ) ) { // fucking bad ruby xml file
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
            else if ( caseInsensitiveComparison( name, "dynamic" ) ) {
                rule.dynamic = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "minimal" ) ) {
                rule.minimal = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "includeAttrib" ) ) {
                rule.includeAttrib = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "region" ) ) {
                rule.region = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "lineEndContext" ) ) {
                rule.lineEndContext = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "weakDelimiter" ) ) {
                rule.weakDelimiter = atts.value( i );
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
            else if ( caseInsensitiveComparison( name, "strikeOut" ) ) {
                itemData.strikeOut = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "underline" ) ) {
                itemData.underline = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "backgroundColor" ) ) {
                itemData.backgroundColor = atts.value( i );
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
            else if ( caseInsensitiveComparison( name, "weakDeliminator" ) ) {
                comment.weakDeliminator = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "position" ) ) {
                comment.position = atts.value( i );
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
            else if ( caseInsensitiveComparison( name, "weakDeliminator" ) ) {
                d->document->general.keywords.weakDeliminator = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "additionalDeliminator" ) ) {
                d->document->general.keywords.additionalDeliminator = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "wordWrapDeliminator" ) ) {
                d->document->general.keywords.wordWrapDeliminator = atts.value( i );
            }
            else {
                d->error = QString( "%1: Unhandled keywords attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
                return false;
            }
        }
    }
    else if ( caseInsensitiveComparison( qName, "folding" ) ) {
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            if ( caseInsensitiveComparison( name, "indentationSensitive" ) ) {
                d->document->general.folding.indentationSensitive = atts.value( i );
            }
            else {
                d->error = QString( "%1: Unhandled folding attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
                return false;
            }
        }
    }
    else if ( caseInsensitiveComparison( qName, "indentation" ) ) {
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            if ( caseInsensitiveComparison( name, "mode" ) ) {
                d->document->general.indentation.mode = atts.value( i );
            }
            else {
                d->error = QString( "%1: Unhandled indentation attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
                return false;
            }
        }
    }
    else if ( caseInsensitiveComparison( qName, "emptyLines" ) ) {
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            d->error = QString( "%1: Unhandled emptyLines attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
            return false;
        }
    }
    else if ( caseInsensitiveComparison( qName, "emptyLine" ) ) {
        Syntax::EmptyLine emptyLine;
        
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            if ( caseInsensitiveComparison( name, "regExpr" ) ) {
                emptyLine.regExpr = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "caseSensitive" ) ) {
                emptyLine.caseSensitive = atts.value( i );
            }
            else {
                d->error = QString( "%1: Unhandled emptyLine attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
                return false;
            }
        }
        
        d->document->general.emptyLines << emptyLine;
    }
    else if ( caseInsensitiveComparison( qName, "spellChecking" ) ) {
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            d->error = QString( "%1: Unhandled spellChecking attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
            return false;
        }
    }
    else if ( caseInsensitiveComparison( qName, "configuration" ) ) {
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            if ( caseInsensitiveComparison( name, "encodingReplacementPolicy" ) ) {
                d->document->spellChecking.configuration.encodingReplacementPolicy = atts.value( i );
            }
            else {
                d->error = QString( "%1: Unhandled configuration attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
                return false;
            }
        }
    }
    else if ( caseInsensitiveComparison( qName, "encodings" ) ) {
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            d->error = QString( "%1: Unhandled encodings attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
            return false;
        }
    }
    else if ( caseInsensitiveComparison( qName, "encoding" ) ) {
        Syntax::Encoding encoding;
        
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            if ( caseInsensitiveComparison( name, "char" ) ) {
                encoding.char_ = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "string" ) ) {
                encoding.string = atts.value( i );
            }
            else if ( caseInsensitiveComparison( name, "ignored" ) ) {
                encoding.ignored = atts.value( i );
            }
            else {
                d->error = QString( "%1: Unhandled encoding attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
                return false;
            }
        }
        
        d->document->spellChecking.encodings << encoding;
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
    else if ( caseInsensitiveComparison( qName, "folding" ) ) {
    }
    else if ( caseInsensitiveComparison( qName, "indentation" ) ) {
    }
    else if ( caseInsensitiveComparison( qName, "emptyLine" ) ) {
    }
    else if ( caseInsensitiveComparison( qName, "emptyLines" ) ) {
    }
    else if ( caseInsensitiveComparison( qName, "general" ) ) {
    }
    else if ( caseInsensitiveComparison( qName, "configuration" ) ) {
    }
    else if ( caseInsensitiveComparison( qName, "encoding" ) ) {
    }
    else if ( caseInsensitiveComparison( qName, "encodings" ) ) {
    }
    else if ( caseInsensitiveComparison( qName, "spellChecking" ) ) {
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
