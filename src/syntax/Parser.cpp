/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : Parser.cpp
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#include "Parser.h"
#include "Document.h"
#include "Tools.h"

#include <QStack>
#include <QVariant>
#include <QDebug>

/*QHash<QString, QodeEdit::Style> initializedStyleMapping()
{
    QHash<QString, QodeEdit::Style> hash;
    hash[ "alert" ] = QodeEdit::AlertStyle;
    hash[ "base-n integer" ] = QodeEdit::BaseNStyle;
    hash[ "character" ] = QodeEdit::CharStyle;
    hash[ "string char" ] = QodeEdit::CharStyle;
    hash[ "comment" ] = QodeEdit::CommentStyle;
    hash[ "data type" ] = QodeEdit::DataTypeStyle;
    hash[ "decimal/value" ] = QodeEdit::DecValStyle;
    hash[ "error" ] = QodeEdit::ErrorStyle;
    hash[ "floating point" ] = QodeEdit::FloatStyle;
    hash[ "function" ] = QodeEdit::FunctionStyle;
    hash[ "keyword" ] = QodeEdit::KeywordStyle;
    hash[ "normal" ] = QodeEdit::NormalStyle;
    hash[ "others" ] = QodeEdit::OthersStyle;
    hash[ "region marker" ] = QodeEdit::RegionMarkerStyle;
    hash[ "string" ] = QodeEdit::StringStyle;
    return hash;
}

static QHash<QString, QodeEdit::Style> globalStyleMapping( initializedStyleMapping() );*/

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
    typedef QHash<QString, QHash<QString, QSet<QString> > > Debug;
    Syntax::ParserPrivate::Debug debug;
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
                << "hlcfloat" // HlCFloat
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
        //const QString name = atts.qName( i );
    }
#endif
    
    if ( QodeEdit::Tools::stringEquals( qName, "language" ) ) {
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            if ( QodeEdit::Tools::stringEquals( name, "name" ) ) {
                d->document->name() = atts.value( i ).toLower();
            }
            else if ( QodeEdit::Tools::stringEquals( name, "section" ) ) {
                d->document->section() = atts.value( i );
            }
            else if ( QodeEdit::Tools::stringEquals( name, "version" ) ) {
                d->document->version() = atts.value( i );
            }
            else if ( QodeEdit::Tools::stringEquals( name, "kateVersion" ) ) {
                d->document->kateVersion() = atts.value( i );
            }
            else if ( QodeEdit::Tools::stringEquals( name, "indenter" ) ) {
                d->document->indenter() = atts.value( i );
            }
            else if ( QodeEdit::Tools::stringEquals( name, "mimeType" ) ) {
                d->document->mimeType() = atts.value( i ).split( ";", QString::SkipEmptyParts ).toSet();
            }
            else if ( QodeEdit::Tools::stringEquals( name, "extensions" ) ) {
                d->document->extensions() = atts.value( i ).split( ";", QString::SkipEmptyParts ).toSet();
            }
            else if ( QodeEdit::Tools::stringEquals( name, "priority" ) ) {
                d->document->priority() = atts.value( i ).toInt();
            }
            else if ( QodeEdit::Tools::stringEquals( name, "author" ) ) {
                d->document->author() = atts.value( i );
            }
            else if ( QodeEdit::Tools::stringEquals( name, "license" ) ) {
                d->document->license() = atts.value( i );
            }
            else if ( QodeEdit::Tools::stringEquals( name, "caseSensitive" ) ) {
                d->document->caseSensitive() = QVariant( atts.value( i ) ).toBool();
            }
            else if ( QodeEdit::Tools::stringEquals( name, "hidden" ) ) {
                d->document->hidden() = QVariant( atts.value( i ) ).toBool();
            }
            else if ( QodeEdit::Tools::stringEquals( name, "style" ) ) {
                d->document->style() = atts.value( i );
            }
            else {
                d->error = QString( "%1: Unhandled language attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
                return false;
            }
        }
    }
    else if ( QodeEdit::Tools::stringEquals( qName, "highlighting" ) ) {
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            d->error = QString( "%1: Unhandled highlighting attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
            return false;
        }
    }
    else if ( QodeEdit::Tools::stringEquals( qName, "list" ) ) {
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            if ( QodeEdit::Tools::stringEquals( name, "name" ) ) {
                d->listName = atts.value( i ).toLower();
            }
            else {
                d->error = QString( "%1: Unhandled list attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
                return false;
            }
        }
    }
    else if ( QodeEdit::Tools::stringEquals( qName, "item" ) ) {
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            d->error = QString( "%1: Unhandled item attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
            return false;
        }
    }
    else if ( QodeEdit::Tools::stringEquals( qName, "contexts" ) ) {
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            d->error = QString( "%1: Unhandled contexts attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
            return false;
        }
    }
    else if ( QodeEdit::Tools::stringEquals( qName, "context" ) ) {
        Syntax::Context context;
        
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            if ( QodeEdit::Tools::stringEquals( name, "name" ) ) {
                d->contextName = atts.value( i ).toLower();
                context.name() = d->contextName;
            }
            else if ( QodeEdit::Tools::stringEquals( name, "lineBeginContext" ) ) {
                context.lineBeginContext() = atts.value( i ).toLower();
            }
            else if ( QodeEdit::Tools::stringEquals( name, "lineEndContext" ) ) {
                context.lineEndContext() = atts.value( i ).toLower();
            }
            else if ( QodeEdit::Tools::stringEquals( name, "attribute" ) ) {
                context.attribute() = atts.value( i ).toLower();
            }
            else if ( QodeEdit::Tools::stringEquals( name, "fallThrough" ) ) {
                context.fallThrough() = QVariant( atts.value( i ) ).toBool();
            }
            else if ( QodeEdit::Tools::stringEquals( name, "fallThroughContext" ) ) {
                context.fallThroughContext() = atts.value( i ).toLower();
            }
            else if ( QodeEdit::Tools::stringEquals( name, "dynamic" ) ) {
                context.dynamic() = QVariant( atts.value( i ) ).toBool();
            }
            else if ( QodeEdit::Tools::stringEquals( name, "noIndentationBasedFolding" ) ) {
                context.noIndentationBasedFolding() = QVariant( atts.value( i ) ).toBool();
            }
            else if ( QodeEdit::Tools::stringEquals( name, "caseSensitive" ) ) {
                qWarning( "%s: Invalid attribute (%s) meet in %s", Q_FUNC_INFO, qPrintable( name ), qPrintable( qName ) );
            }
            else {
                d->error = QString( "%1: Unhandled context attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
                return false;
            }
        }
        
        if ( !context.fallThrough() ) {
            context.fallThroughContext().clear();
        }
        
        d->document->highlighting().contexts()[ context.name() ] = context;
        
        if ( d->document->highlighting().defaultContextName().isEmpty() ) {
            d->document->highlighting().defaultContextName() = context.name();
        }
        
        Q_ASSERT( !context.name().isEmpty() );
    }
    else if ( d->ruleNames.contains( qName.toLower() ) ) {
        Q_ASSERT( !d->contextName.isEmpty() );
        const QodeEdit::Rule type = QodeEdit::Tools::stringToRule( qName );
        Syntax::Context& context = d->document->highlighting().contexts()[ d->contextName ];
        QHash<QString, QVariant> data;
        static QSet<QString> knownAttributes;
        
        if ( knownAttributes.isEmpty() ) {
            knownAttributes
                << "attribute"
                << "context"
                << "string"
                << "beginregion"
                << "firstnonspace"
                << "char"
                << "lookahead"
                << "endregion"
                << "insensitive"
                << "char1"
                << "column"
                << "dynamic"
                << "minimal"
                << "includeattrib"
                << "region"
                << "lineendcontext"
                << "weakdelimiter"
            ;
        }
        
        for ( int i = 0; i < atts.count(); i++ ) {
            QString name = atts.qName( i ).toLower();
            
            // fucking ruby file
            if ( name == "contex" ) {
                qWarning( "%s: Invalid attribute (%s) meet in %s", Q_FUNC_INFO, qPrintable( name ), qPrintable( qName ) );
                name = "context";
            }
            
            if ( knownAttributes.contains( name ) ) {
                data[ name ] = atts.value( i );
            }
            else {
                d->error = QString( "%1: Unhandled rule attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
                return false;
            }
        }
        
        // add to context rules
        if ( d->nodesName.top().toLower() == "context" ) {
            context.rules() << Syntax::Rule::create( type, data );
        }
        // add to last context rules' rule
        else {
            Syntax::Rule& lastRule = context.rules().last();
            const QodeEdit::Rule lastType = lastRule.type();
            
            switch ( lastType ) {
                case QodeEdit::FloatRule:
                    lastRule.toFloat().rules() << Syntax::Rule::create( type, data );
                    break;
                case QodeEdit::IntRule:
                    lastRule.toInt().rules() << Syntax::Rule::create( type, data );
                    break;
                default:
                    qWarning( "%s: Type not Float nor Int '%i'", Q_FUNC_INFO, type );
                    Q_ASSERT( 0 );
            }
            
            Q_ASSERT( context.rules().last() == lastRule );
        }
    }
    else if ( QodeEdit::Tools::stringEquals( qName, "itemDatas" ) ) {
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            d->error = QString( "%1: Unhandled itemDatas attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
            return false;
        }
    }
    else if ( QodeEdit::Tools::stringEquals( qName, "itemData" ) ) {
        Syntax::ItemData itemData;
        
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            if ( QodeEdit::Tools::stringEquals( name, "name" ) ) {
                itemData.name() = atts.value( i ).toLower();
            }
            else if ( QodeEdit::Tools::stringEquals( name, "defStyleNum" ) ) {
                itemData.defStyleNum() = atts.value( i );
                
                if ( QodeEdit::Tools::stringToDefaultStyle( itemData.defStyleNum() ) == -1 ) {
                    qWarning( "%s: Fixed invalid style to dsNormal in %s", Q_FUNC_INFO, qPrintable( d->document->name() ) );
                    itemData.defStyleNum() = "dsNormal";
                }
            }
            else if ( QodeEdit::Tools::stringEquals( name, "spellChecking" ) ) {
                itemData.spellChecking() = QVariant( atts.value( i ) ).toBool();
            }
            else if ( QodeEdit::Tools::stringEquals( name, "color" ) ) {
                itemData.color() = QColor( atts.value( i ) );
            }
            else if ( QodeEdit::Tools::stringEquals( name, "selColor" ) ) {
                itemData.selColor() = QColor( atts.value( i ) );
            }
            else if ( QodeEdit::Tools::stringEquals( name, "bold" ) ) {
                itemData.bold() = QVariant( atts.value( i ) ).toBool();
            }
            else if ( QodeEdit::Tools::stringEquals( name, "italic" ) ) {
                itemData.italic() = QVariant( atts.value( i ) ).toBool();
            }
            else if ( QodeEdit::Tools::stringEquals( name, "strikeOut" ) ) {
                itemData.strikeOut() = QVariant( atts.value( i ) ).toBool();
            }
            else if ( QodeEdit::Tools::stringEquals( name, "underline" ) ) {
                itemData.underline() = QVariant( atts.value( i ) ).toBool();
            }
            else if ( QodeEdit::Tools::stringEquals( name, "backgroundColor" ) ) {
                itemData.backgroundColor() = QColor( atts.value( i ) );
            }
            else if ( QodeEdit::Tools::stringEquals( name, "selBackgroundColor" ) ) {
                itemData.selBackgroundColor() = QColor( atts.value( i ) );
            }
            else {
                d->error = QString( "%1: Unhandled itemData attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
                return false;
            }
        }
        
        d->document->highlighting().itemDatas()[ itemData.name() ] = itemData;
    }
    else if ( QodeEdit::Tools::stringEquals( qName, "general" ) ) {
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            d->error = QString( "%1: Unhandled general attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
            return false;
        }
    }
    else if ( QodeEdit::Tools::stringEquals( qName, "comments" ) ) {
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            d->error = QString( "%1: Unhandled comments attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
            return false;
        }
    }
    else if ( QodeEdit::Tools::stringEquals( qName, "comment" ) ) {
        Syntax::Comment comment;
        
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            if ( QodeEdit::Tools::stringEquals( name, "name" ) ) {
                comment.name() = atts.value( i ).toLower();
            }
            else if ( QodeEdit::Tools::stringEquals( name, "start" ) ) {
                comment.start() = atts.value( i );
            }
            else if ( QodeEdit::Tools::stringEquals( name, "end" ) ) {
                comment.end() = atts.value( i );
            }
            else if ( QodeEdit::Tools::stringEquals( name, "region" ) ) {
                comment.region() = atts.value( i );
            }
            else if ( QodeEdit::Tools::stringEquals( name, "position" ) ) {
                comment.position() = atts.value( i );
            }
            else if ( QodeEdit::Tools::stringEquals( name, "weakDeliminator" ) ) {
                qWarning( "%s: Invalid attribute (%s) meet in %s", Q_FUNC_INFO, qPrintable( name ), qPrintable( qName ) );
            }
            else {
                d->error = QString( "%1: Unhandled comment attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
                return false;
            }
        }
        
        d->document->general().comments() << comment;
    }
    else if ( QodeEdit::Tools::stringEquals( qName, "keywords" ) ) {
        Syntax::Keywords& keywords = d->document->general().keywords();
        
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            if ( QodeEdit::Tools::stringEquals( name, "caseSensitive" ) ) {
                keywords.caseSensitive() = QVariant( atts.value( i ) ).toBool();
            }
            else if ( QodeEdit::Tools::stringEquals( name, "weakDeliminator" ) ) {
                keywords.weakDeliminator() = atts.value( i );
            }
            else if ( QodeEdit::Tools::stringEquals( name, "additionalDeliminator" ) ) {
                keywords.additionalDeliminator() = atts.value( i );
            }
            else if ( QodeEdit::Tools::stringEquals( name, "wordWrapDeliminator" ) ) {
                keywords.wordWrapDeliminator() = atts.value( i );
            }
            else {
                d->error = QString( "%1: Unhandled keywords attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
                return false;
            }
        }
    }
    else if ( QodeEdit::Tools::stringEquals( qName, "folding" ) ) {
        Syntax::Folding& folding = d->document->general().folding();
        
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            if ( QodeEdit::Tools::stringEquals( name, "indentationSensitive" ) ) {
                folding.indentationSensitive() = QVariant( atts.value( i ) ).toBool();
            }
            else {
                d->error = QString( "%1: Unhandled folding attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
                return false;
            }
        }
    }
    else if ( QodeEdit::Tools::stringEquals( qName, "indentation" ) ) {
        Syntax::Indentation& indentation = d->document->general().indentation();
        
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            if ( QodeEdit::Tools::stringEquals( name, "mode" ) ) {
                indentation.mode() = atts.value( i );
            }
            else {
                d->error = QString( "%1: Unhandled indentation attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
                return false;
            }
        }
    }
    else if ( QodeEdit::Tools::stringEquals( qName, "emptyLines" ) ) {
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            d->error = QString( "%1: Unhandled emptyLines attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
            return false;
        }
    }
    else if ( QodeEdit::Tools::stringEquals( qName, "emptyLine" ) ) {
        Syntax::EmptyLine emptyLine;
        
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            if ( QodeEdit::Tools::stringEquals( name, "regExpr" ) ) {
                emptyLine.regExpr() = atts.value( i );
            }
            else if ( QodeEdit::Tools::stringEquals( name, "caseSensitive" ) ) {
                emptyLine.caseSensitive() = QVariant( atts.value( i ) ).toBool();
            }
            else {
                d->error = QString( "%1: Unhandled emptyLine attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
                return false;
            }
        }
        
        d->document->general().emptyLines() << emptyLine;
    }
    else if ( QodeEdit::Tools::stringEquals( qName, "spellChecking" ) ) {
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            d->error = QString( "%1: Unhandled spellChecking attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
            return false;
        }
    }
    else if ( QodeEdit::Tools::stringEquals( qName, "configuration" ) ) {
        Syntax::Configuration& configuration = d->document->spellChecking().configuration();
        
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            if ( QodeEdit::Tools::stringEquals( name, "encodingReplacementPolicy" ) ) {
                configuration.encodingReplacementPolicy() = atts.value( i );
            }
            else {
                d->error = QString( "%1: Unhandled configuration attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
                return false;
            }
        }
    }
    else if ( QodeEdit::Tools::stringEquals( qName, "encodings" ) ) {
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            d->error = QString( "%1: Unhandled encodings attribute: %2" ).arg( Q_FUNC_INFO ).arg( name );
            return false;
        }
    }
    else if ( QodeEdit::Tools::stringEquals( qName, "encoding" ) ) {
        Syntax::Encoding encoding;
        
        for ( int i = 0; i < atts.count(); i++ ) {
            const QString name = atts.qName( i );
            
            if ( QodeEdit::Tools::stringEquals( name, "char" ) ) {
                encoding.char_() = atts.value( i );
            }
            else if ( QodeEdit::Tools::stringEquals( name, "string" ) ) {
                encoding.string() = atts.value( i );
            }
            else if ( QodeEdit::Tools::stringEquals( name, "ignored" ) ) {
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
    if ( QodeEdit::Tools::stringEquals( qName, "item" ) ) {
        Q_ASSERT( !d->listName.isEmpty() );
        d->document->highlighting().lists()[ d->listName ] << ( d->document->caseSensitive() ? d->text.trimmed() : d->text.trimmed().toLower() );
        d->text.clear();
    }
    else if ( QodeEdit::Tools::stringEquals( qName, "list" ) ) {
        d->listName.clear();
    }
    else if ( d->ruleNames.contains( qName.toLower() ) ) {
    }
    else if ( QodeEdit::Tools::stringEquals( qName, "context" ) ) {
        d->contextName.clear();
    }
    else if ( QodeEdit::Tools::stringEquals( qName, "contexts" ) ) {
    }
    else if ( QodeEdit::Tools::stringEquals( qName, "itemData" ) ) {
    }
    else if ( QodeEdit::Tools::stringEquals( qName, "itemDatas" ) ) {
    }
    else if ( QodeEdit::Tools::stringEquals( qName, "highlighting" ) ) {
    }
    else if ( QodeEdit::Tools::stringEquals( qName, "comment" ) ) {
    }
    else if ( QodeEdit::Tools::stringEquals( qName, "comments" ) ) {
    }
    else if ( QodeEdit::Tools::stringEquals( qName, "keywords" ) ) {
    }
    else if ( QodeEdit::Tools::stringEquals( qName, "folding" ) ) {
    }
    else if ( QodeEdit::Tools::stringEquals( qName, "indentation" ) ) {
    }
    else if ( QodeEdit::Tools::stringEquals( qName, "emptyLine" ) ) {
    }
    else if ( QodeEdit::Tools::stringEquals( qName, "emptyLines" ) ) {
    }
    else if ( QodeEdit::Tools::stringEquals( qName, "general" ) ) {
    }
    else if ( QodeEdit::Tools::stringEquals( qName, "configuration" ) ) {
    }
    else if ( QodeEdit::Tools::stringEquals( qName, "encoding" ) ) {
    }
    else if ( QodeEdit::Tools::stringEquals( qName, "encodings" ) ) {
    }
    else if ( QodeEdit::Tools::stringEquals( qName, "spellChecking" ) ) {
    }
    else if ( QodeEdit::Tools::stringEquals( qName, "language" ) ) {
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
