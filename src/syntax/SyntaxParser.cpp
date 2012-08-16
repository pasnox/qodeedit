#include "SyntaxParser.h"
#include "SyntaxDocument.h"
#include "QodeEdit.h"

#include <QStack>
#include <QVariant>
#include <QDebug>

// ParserPrivate

class Syntax::ParserPrivate {
public:
    const Syntax::List ruleNames;
    Syntax::Document* document;
    QString error;
    QString listName;
    QString contextName;
    QString text;
    QStack<QString> nodesName;
    QMap<QString, int> counts;
    
#if !defined( QT_NO_DEBUG )
    Syntax::Parser::Debug debug;
#endif
    
    ParserPrivate( Syntax::Parser* _parser )
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
            document( 0 ),
            parser( _parser )
    {
    }
    
private:
    Syntax::Parser* parser;
};

// Reader

bool Syntax::Reader::parse( Syntax::Document* document, const QXmlInputSource& input )
{
    Syntax::Parser* parser = static_cast<Syntax::Parser*>( contentHandler() );
    
    Q_ASSERT( parser );
    
    parser->d->document = document;
    return QXmlSimpleReader::parse( input );
}

// Parser

Syntax::Parser::Parser()
    : QXmlDefaultHandler(),
        d( new Syntax::ParserPrivate( this ) )
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
    d->nodesName.clear();
    d->nodesName.reserve( 1000 );
    d->counts.clear();
    return true;
}

bool Syntax::Parser::endDocument()
{
    Q_ASSERT( !d->document->name().isEmpty() );
    Q_ASSERT( !d->document->section().isEmpty() );
    Q_ASSERT( d->counts.value( "highlighting" ) <= 1 );
    Q_ASSERT( d->counts.value( "contexts" ) <= 1 );
    Q_ASSERT( d->counts.value( "itemdatas" ) <= 1 );
    Q_ASSERT( d->counts.value( "general" ) <= 1 );
    Q_ASSERT( d->counts.value( "comments" ) <= 1 );
    Q_ASSERT( d->counts.value( "keywords" ) <= 1 );
    Q_ASSERT( d->counts.value( "folding" ) <= 1 );
    Q_ASSERT( d->counts.value( "indentation" ) <= 1 );
    Q_ASSERT( d->counts.value( "configuration" ) <= 1 );
    Q_ASSERT( d->counts.value( "spellchecking" ) <= 1 );
    Q_ASSERT( d->counts.value( "emptylines" ) <= 1 );
    Q_ASSERT( d->counts.value( "encodings" ) <= 1 );
    
    d->error.clear();
    d->listName.clear();
    d->contextName.clear();
    d->text.clear();
    d->nodesName.clear();
    d->counts.clear();
    return true;
}

bool Syntax::Parser::startElement( const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& atts )
{
    d->counts[ qName.toLower() ]++;
    
#if !defined( QT_NO_DEBUG )
    const QString name = qName.trimmed().toLower();
    
    for ( int i = 0; i < atts.count(); i++ ) {
        d->debug[ name ][ atts.qName( i ).trimmed().toLower() ] << atts.value( i ).trimmed().toLower();
        const QString name = atts.qName( i );
        
    }
#endif
    
    if ( QodeEdit::stringEquals( qName, "language" ) ) {
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            if ( QodeEdit::stringEquals( name, "name" ) ) {
                d->document->name() = atts.value( i );
            }
            else if ( QodeEdit::stringEquals( name, "section" ) ) {
                d->document->section() = atts.value( i );
            }
            else if ( QodeEdit::stringEquals( name, "version" ) ) {
                d->document->version() = atts.value( i );
            }
            else if ( QodeEdit::stringEquals( name, "kateVersion" ) ) {
                d->document->kateVersion() = atts.value( i );
            }
            else if ( QodeEdit::stringEquals( name, "indenter" ) ) {
                d->document->indenter() = atts.value( i );
            }
            else if ( QodeEdit::stringEquals( name, "mimeType" ) ) {
                d->document->mimeTypes() = atts.value( i ).split( ";", QString::SkipEmptyParts ).toSet();
            }
            else if ( QodeEdit::stringEquals( name, "extensions" ) ) {
                d->document->extensions() = atts.value( i ).split( ";", QString::SkipEmptyParts ).toSet();
            }
            else if ( QodeEdit::stringEquals( name, "priority" ) ) {
                d->document->priority() = atts.value( i ).toInt();
            }
            else if ( QodeEdit::stringEquals( name, "author" ) ) {
                d->document->author() = atts.value( i );
            }
            else if ( QodeEdit::stringEquals( name, "license" ) ) {
                d->document->license() = atts.value( i );
            }
            else if ( QodeEdit::stringEquals( name, "caseSensitive" ) ) {
                d->document->caseSensitive() = QVariant( atts.value( i ) ).toBool();
            }
            else if ( QodeEdit::stringEquals( name, "hidden" ) ) {
                d->document->hidden() = QVariant( atts.value( i ) ).toBool();
            }
            else if ( QodeEdit::stringEquals( name, "style" ) ) {
                d->document->style() = atts.value( i );
            }
            else {
                d->error = QString( "%1: Unhandled language attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
                return false;
            }
        }
    }
    else if ( QodeEdit::stringEquals( qName, "highlighting" ) ) {
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            d->error = QString( "%1: Unhandled highlighting attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
            return false;
        }
    }
    else if ( QodeEdit::stringEquals( qName, "list" ) ) {
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            if ( QodeEdit::stringEquals( name, "name" ) ) {
                d->listName = atts.value( i );
            }
            else {
                d->error = QString( "%1: Unhandled list attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
                return false;
            }
        }
    }
    else if ( QodeEdit::stringEquals( qName, "item" ) ) {
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            d->error = QString( "%1: Unhandled item attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
            return false;
        }
    }
    else if ( QodeEdit::stringEquals( qName, "contexts" ) ) {
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            d->error = QString( "%1: Unhandled contexts attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
            return false;
        }
    }
    else if ( QodeEdit::stringEquals( qName, "context" ) ) {
        Syntax::Context context;
        
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            if ( QodeEdit::stringEquals( name, "name" ) ) {
                d->contextName = atts.value( i );
                context.name() = d->contextName;
            }
            else if ( QodeEdit::stringEquals( name, "lineEndContext" ) ) {
                context.lineEndContext() = atts.value( i );
            }
            else if ( QodeEdit::stringEquals( name, "attribute" ) ) {
                context.attribute() = atts.value( i );
            }
            else if ( QodeEdit::stringEquals( name, "fallThrough" ) ) {
                context.fallThrough() = QVariant( atts.value( i ) ).toBool();
            }
            else if ( QodeEdit::stringEquals( name, "fallThroughContext" ) ) {
                context.fallThroughContext() = atts.value( i );
            }
            else if ( QodeEdit::stringEquals( name, "dynamic" ) ) {
                context.dynamic() = QVariant( atts.value( i ) ).toBool();
            }
            else if ( QodeEdit::stringEquals( name, "noIndentationBasedFolding" ) ) {
                context.noIndentationBasedFolding() = QVariant( atts.value( i ) ).toBool();
            }
            else if ( QodeEdit::stringEquals( name, "caseSensitive" ) ) {
                context.caseSensitive() = QVariant( atts.value( i ) ).toBool();
            }
            else {
                d->error = QString( "%1: Unhandled context attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
                return false;
            }
        }
        
        d->document->highlighting().contexts()[ context.name() ] = context;
        
        if ( d->document->highlighting().initialContext().isEmpty() ) {
            d->document->highlighting().initialContext() = context.name();
        }
        
        Q_ASSERT( !context.name().isEmpty() );
    }
    else if ( d->ruleNames.contains( qName.toLower() ) ) {
        Q_ASSERT( !d->contextName.isEmpty() );
        Syntax::Context& context = d->document->highlighting().contexts()[ d->contextName ];
        Syntax::Rule rule;
        
        rule.name() = qName;
        
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            if ( QodeEdit::stringEquals( name, "attribute" ) ) {
                rule.attribute() = atts.value( i );
            }
            else if ( QodeEdit::stringEquals( name, "context" ) || QodeEdit::stringEquals( name, "contex" ) ) { // fucking bad ruby xml file
                rule.context() = atts.value( i );
            }
            else if ( QodeEdit::stringEquals( name, "string" ) ) {
                rule.string() = atts.value( i );
            }
            else if ( QodeEdit::stringEquals( name, "beginRegion" ) ) {
                rule.beginRegion() = atts.value( i );
            }
            else if ( QodeEdit::stringEquals( name, "firstNonSpace" ) ) {
                rule.firstNonSpace() = QVariant( atts.value( i ) ).toBool();
            }
            else if ( QodeEdit::stringEquals( name, "char" ) ) {
                rule.char_() = atts.value( i );
            }
            else if ( QodeEdit::stringEquals( name, "lookAhead" ) ) {
                rule.lookAhead() = QVariant( atts.value( i ) ).toBool();
            }
            else if ( QodeEdit::stringEquals( name, "endRegion" ) ) {
                rule.endRegion() = atts.value( i );
            }
            else if ( QodeEdit::stringEquals( name, "insensitive" ) ) {
                rule.insensitive() = QVariant( atts.value( i ) ).toBool();
            }
            else if ( QodeEdit::stringEquals( name, "char1" ) ) {
                rule.char1() = atts.value( i );
            }
            else if ( QodeEdit::stringEquals( name, "column" ) ) {
                rule.column() = atts.value( i ).toInt();
            }
            else if ( QodeEdit::stringEquals( name, "dynamic" ) ) {
                rule.dynamic() = QVariant( atts.value( i ) ).toBool();
            }
            else if ( QodeEdit::stringEquals( name, "minimal" ) ) {
                rule.minimal() = QVariant( atts.value( i ) ).toBool();
            }
            else if ( QodeEdit::stringEquals( name, "includeAttrib" ) ) {
                rule.includeAttrib() = QVariant( atts.value( i ) ).toBool();
            }
            else if ( QodeEdit::stringEquals( name, "region" ) ) {
                rule.region() = atts.value( i );
            }
            else if ( QodeEdit::stringEquals( name, "lineEndContext" ) ) {
                rule.lineEndContext() = atts.value( i );
            }
            else if ( QodeEdit::stringEquals( name, "weakDelimiter" ) ) {
                rule.weakDelimiter() = atts.value( i );
            }
            else {
                d->error = QString( "%1: Unhandled rule attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
                return false;
            }
        }
        
        // add to context rules
        if ( d->nodesName.top().toLower() == "context" ) {
            context.rules() << rule;
        }
        // add to last context rule' rule
        else {
            context.rules().last().rules() << rule;
        }
    }
    else if ( QodeEdit::stringEquals( qName, "itemDatas" ) ) {
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            d->error = QString( "%1: Unhandled itemDatas attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
            return false;
        }
    }
    else if ( QodeEdit::stringEquals( qName, "itemData" ) ) {
        Syntax::ItemData itemData;
        
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            if ( QodeEdit::stringEquals( name, "name" ) ) {
                itemData.name() = atts.value( i );
            }
            else if ( QodeEdit::stringEquals( name, "defStyleNum" ) ) {
                itemData.defStyleNum() = atts.value( i );
            }
            else if ( QodeEdit::stringEquals( name, "spellChecking" ) ) {
                itemData.spellChecking() = QVariant( atts.value( i ) ).toBool();
            }
            else if ( QodeEdit::stringEquals( name, "color" ) ) {
                itemData.color() = QColor( atts.value( i ) );
            }
            else if ( QodeEdit::stringEquals( name, "selColor" ) ) {
                itemData.selColor() = QColor( atts.value( i ) );
            }
            else if ( QodeEdit::stringEquals( name, "bold" ) ) {
                itemData.bold() = QVariant( atts.value( i ) ).toBool();
            }
            else if ( QodeEdit::stringEquals( name, "italic" ) ) {
                itemData.italic() = QVariant( atts.value( i ) ).toBool();
            }
            else if ( QodeEdit::stringEquals( name, "strikeOut" ) ) {
                itemData.strikeOut() = QVariant( atts.value( i ) ).toBool();
            }
            else if ( QodeEdit::stringEquals( name, "underline" ) ) {
                itemData.underline() = QVariant( atts.value( i ) ).toBool();
            }
            else if ( QodeEdit::stringEquals( name, "backgroundColor" ) ) {
                itemData.backgroundColor() = QColor( atts.value( i ) );
            }
            else {
                d->error = QString( "%1: Unhandled itemData attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
                return false;
            }
        }
        
        d->document->highlighting().itemDatas()[ itemData.name() ] = itemData;
    }
    else if ( QodeEdit::stringEquals( qName, "general" ) ) {
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            d->error = QString( "%1: Unhandled general attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
            return false;
        }
    }
    else if ( QodeEdit::stringEquals( qName, "comments" ) ) {
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            d->error = QString( "%1: Unhandled comments attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
            return false;
        }
    }
    else if ( QodeEdit::stringEquals( qName, "comment" ) ) {
        Syntax::Comment comment;
        
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            if ( QodeEdit::stringEquals( name, "name" ) ) {
                comment.name() = atts.value( i );
            }
            else if ( QodeEdit::stringEquals( name, "start" ) ) {
                comment.start() = atts.value( i );
            }
            else if ( QodeEdit::stringEquals( name, "end" ) ) {
                comment.end() = atts.value( i );
            }
            else if ( QodeEdit::stringEquals( name, "region" ) ) {
                comment.region() = atts.value( i );
            }
            else if ( QodeEdit::stringEquals( name, "weakDeliminator" ) ) {
                comment.weakDeliminator() = atts.value( i );
            }
            else if ( QodeEdit::stringEquals( name, "position" ) ) {
                comment.position() = atts.value( i );
            }
            else {
                d->error = QString( "%1: Unhandled comment attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
                return false;
            }
        }
        
        d->document->general().comments() << comment;
    }
    else if ( QodeEdit::stringEquals( qName, "keywords" ) ) {
        Syntax::Keywords& keywords = d->document->general().keywords();
        
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            if ( QodeEdit::stringEquals( name, "caseSensitive" ) ) {
                keywords.caseSensitive() = QVariant( atts.value( i ) ).toBool();
            }
            else if ( QodeEdit::stringEquals( name, "weakDeliminator" ) ) {
                keywords.weakDeliminator() = atts.value( i );
            }
            else if ( QodeEdit::stringEquals( name, "additionalDeliminator" ) ) {
                keywords.additionalDeliminator() = atts.value( i );
            }
            else if ( QodeEdit::stringEquals( name, "wordWrapDeliminator" ) ) {
                keywords.wordWrapDeliminator() = atts.value( i );
            }
            else {
                d->error = QString( "%1: Unhandled keywords attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
                return false;
            }
        }
    }
    else if ( QodeEdit::stringEquals( qName, "folding" ) ) {
        Syntax::Folding& folding = d->document->general().folding();
        
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            if ( QodeEdit::stringEquals( name, "indentationSensitive" ) ) {
                folding.indentationSensitive() = QVariant( atts.value( i ) ).toBool();
            }
            else {
                d->error = QString( "%1: Unhandled folding attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
                return false;
            }
        }
    }
    else if ( QodeEdit::stringEquals( qName, "indentation" ) ) {
        Syntax::Indentation& indentation = d->document->general().indentation();
        
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            if ( QodeEdit::stringEquals( name, "mode" ) ) {
                indentation.mode() = atts.value( i );
            }
            else {
                d->error = QString( "%1: Unhandled indentation attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
                return false;
            }
        }
    }
    else if ( QodeEdit::stringEquals( qName, "emptyLines" ) ) {
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            d->error = QString( "%1: Unhandled emptyLines attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
            return false;
        }
    }
    else if ( QodeEdit::stringEquals( qName, "emptyLine" ) ) {
        Syntax::EmptyLine emptyLine;
        
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            if ( QodeEdit::stringEquals( name, "regExpr" ) ) {
                emptyLine.regExpr() = atts.value( i );
            }
            else if ( QodeEdit::stringEquals( name, "caseSensitive" ) ) {
                emptyLine.caseSensitive() = QVariant( atts.value( i ) ).toBool();
            }
            else {
                d->error = QString( "%1: Unhandled emptyLine attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
                return false;
            }
        }
        
        d->document->general().emptyLines() << emptyLine;
    }
    else if ( QodeEdit::stringEquals( qName, "spellChecking" ) ) {
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            d->error = QString( "%1: Unhandled spellChecking attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
            return false;
        }
    }
    else if ( QodeEdit::stringEquals( qName, "configuration" ) ) {
        Syntax::Configuration& configuration = d->document->spellChecking().configuration();
        
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            if ( QodeEdit::stringEquals( name, "encodingReplacementPolicy" ) ) {
                configuration.encodingReplacementPolicy() = atts.value( i );
            }
            else {
                d->error = QString( "%1: Unhandled configuration attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
                return false;
            }
        }
    }
    else if ( QodeEdit::stringEquals( qName, "encodings" ) ) {
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            d->error = QString( "%1: Unhandled encodings attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
            return false;
        }
    }
    else if ( QodeEdit::stringEquals( qName, "encoding" ) ) {
        Syntax::Encoding encoding;
        
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            if ( QodeEdit::stringEquals( name, "char" ) ) {
                encoding.char_() = atts.value( i );
            }
            else if ( QodeEdit::stringEquals( name, "string" ) ) {
                encoding.string() = atts.value( i );
            }
            else if ( QodeEdit::stringEquals( name, "ignored" ) ) {
                encoding.ignored() = QVariant( atts.value( i ) ).toBool();
            }
            else {
                d->error = QString( "%1: Unhandled encoding attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
                return false;
            }
        }
        
        d->document->spellChecking().encodings() << encoding;
    }
    else {
        d->error = QString( "%1: Unhandled starting qName element: %2" ).arg( Q_FUNC_INFO ).arg( qName );
        return false;
    }
    
    d->nodesName.push( qName );
    
    return QXmlDefaultHandler::startElement( namespaceURI, localName, qName, atts );
}

bool Syntax::Parser::endElement( const QString& namespaceURI, const QString& localName, const QString& qName )
{
    if ( QodeEdit::stringEquals( qName, "item" ) ) {
        Q_ASSERT( !d->listName.isEmpty() );
        d->document->highlighting().lists()[ d->listName ] << ( d->document->caseSensitive() ? d->text.trimmed() : d->text.trimmed().toLower() );
        d->text.clear();
    }
    else if ( QodeEdit::stringEquals( qName, "list" ) ) {
        d->listName.clear();
    }
    else if ( d->ruleNames.contains( qName.toLower() ) ) {
    }
    else if ( QodeEdit::stringEquals( qName, "context" ) ) {
        d->contextName.clear();
    }
    else if ( QodeEdit::stringEquals( qName, "contexts" ) ) {
    }
    else if ( QodeEdit::stringEquals( qName, "itemData" ) ) {
    }
    else if ( QodeEdit::stringEquals( qName, "itemDatas" ) ) {
    }
    else if ( QodeEdit::stringEquals( qName, "highlighting" ) ) {
    }
    else if ( QodeEdit::stringEquals( qName, "comment" ) ) {
    }
    else if ( QodeEdit::stringEquals( qName, "comments" ) ) {
    }
    else if ( QodeEdit::stringEquals( qName, "keywords" ) ) {
    }
    else if ( QodeEdit::stringEquals( qName, "folding" ) ) {
    }
    else if ( QodeEdit::stringEquals( qName, "indentation" ) ) {
    }
    else if ( QodeEdit::stringEquals( qName, "emptyLine" ) ) {
    }
    else if ( QodeEdit::stringEquals( qName, "emptyLines" ) ) {
    }
    else if ( QodeEdit::stringEquals( qName, "general" ) ) {
    }
    else if ( QodeEdit::stringEquals( qName, "configuration" ) ) {
    }
    else if ( QodeEdit::stringEquals( qName, "encoding" ) ) {
    }
    else if ( QodeEdit::stringEquals( qName, "encodings" ) ) {
    }
    else if ( QodeEdit::stringEquals( qName, "spellChecking" ) ) {
    }
    else if ( QodeEdit::stringEquals( qName, "language" ) ) {
    }
    else {
        d->error = QString( "%1: Unhandled ending qName element: %2" ).arg( Q_FUNC_INFO ).arg( qName );
        return false;
    }
    
    d->nodesName.pop();
    
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

#if !defined( QT_NO_DEBUG )
void Syntax::Parser::debug() const
{
    int weight = 0;
    
    foreach ( const QString& element, d->debug.keys() ) {
        const QHash<QString, QSet<QString> >& attributes = d->debug[ element ];
        
        qWarning() << QString( "%1%2" ).arg( QString( weight, '\t' ) ).arg( element ).toLocal8Bit().constData();
        
        weight++;
        
        foreach ( const QString& attribute, attributes.keys() ) {
            const QSet<QString> values = attributes[ attribute ];
            int count = 0;
            
            qWarning() << QString( "%1%2" ).arg( QString( weight, '\t' ) ).arg( attribute ).toLocal8Bit().constData();
            
            weight++;
            
            foreach ( const QString& value, values ) {
                qWarning() << QString( "%1%2" ).arg( QString( weight, '\t' ) ).arg( value ).toLocal8Bit().constData();
                count++;
                
                if ( count == 5 ) {
                    break;
                }
            }
            
            weight--;
        }
        
        weight--;
    }
}
#endif
