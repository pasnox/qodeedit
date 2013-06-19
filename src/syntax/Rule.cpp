/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : Rule.cpp
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#include "Rule.h"
#include "QodeEdit.h"

#include <QSharedData>
#include <QSet>
#include <QDebug>

class Syntax::RuleData : public QSharedData
{
public:
    QodeEdit::Rule type; // the type of the rule, default InvalidRule

    RuleData()
        : QSharedData(),
            type( QodeEdit::InvalidRule )
    {
    }

    RuleData( const Syntax::RuleData& other )
        : QSharedData( other ),
            QE_OTHER_INIT( type )
    {
    }

    virtual ~RuleData() {
    }
};

class Syntax::CommonRuleData : public Syntax::RuleData
{
public:
    // Optional
    QString attribute; // attribute maps to a defined itemData. Default: the attribute from the destination context
    QString context; // context specifies the context to which the highlighting system switches if the rule matches. Default: #stay
    QString beginRegion; // beginRegion starts a code folding block. Default: unset.
    QString endRegion; // endRegion closes a code folding block. Default: unset.
    bool lookAhead; // lookAhead, if true, the highlighting system will not process the matches length. Default: false.
    bool firstNonSpace; // firstNonSpace, if true, the rule only matches, if the string is the first non-whitespace in the line. Default: false.
    int column; // column defines the column. The rule only matches, if the current column matches the given one. Default: unset.

    CommonRuleData()
        : Syntax::RuleData(),
            context( "#stay" ),
            lookAhead( false ),
            firstNonSpace( false ),
            column( -1 )
    {
    }

    CommonRuleData( const Syntax::CommonRuleData& other )
        : Syntax::RuleData( other ),
            QE_OTHER_INIT( attribute ),
            QE_OTHER_INIT( context ),
            QE_OTHER_INIT( beginRegion ),
            QE_OTHER_INIT( endRegion ),
            QE_OTHER_INIT( lookAhead ),
            QE_OTHER_INIT( firstNonSpace ),
            QE_OTHER_INIT( column )

    {
    }

    virtual ~CommonRuleData() {
    }
};

class Syntax::CommonRulesRuleData : public Syntax::CommonRuleData
{
public:
    Syntax::Rule::List rules;

    CommonRulesRuleData()
        : Syntax::CommonRuleData()
    {
    }

    CommonRulesRuleData( const Syntax::CommonRulesRuleData& other )
        : Syntax::CommonRuleData( other ),
            QE_OTHER_INIT( rules )
    {
    }

    virtual ~CommonRulesRuleData() {
    }
};

class Syntax::CommonStringRuleData : public Syntax::CommonRuleData
{
public:
    // Required
    QString string;
    // Optional
    bool insensitive;
    bool dynamic;

    CommonStringRuleData()
        : Syntax::CommonRuleData(),
            insensitive( false ),
            dynamic( false )
    {
    }

    CommonStringRuleData( const Syntax::CommonStringRuleData& other )
        : Syntax::CommonRuleData( other ),
            QE_OTHER_INIT( string ),
            QE_OTHER_INIT( insensitive ),
            QE_OTHER_INIT( dynamic )
    {
    }

    virtual ~CommonStringRuleData() {
    }
};

class Syntax::KeywordRuleData : public Syntax::CommonRuleData
{
public:
    // Optional
    bool insensitive;
    QString string;
    QString weakDelimiter;

    KeywordRuleData()
        : Syntax::CommonRuleData(),
            insensitive( false )
    {
    }

    KeywordRuleData( const Syntax::KeywordRuleData& other )
        : Syntax::CommonRuleData( other ),
            QE_OTHER_INIT( insensitive ),
            QE_OTHER_INIT( string ),
            QE_OTHER_INIT( weakDelimiter )
    {
    }

    virtual ~KeywordRuleData() {
    }
};

class Syntax::DetectCharRuleData : public Syntax::CommonRuleData
{
public:
    // Required
    QChar char_;
    // Optional
    bool dynamic;

    DetectCharRuleData()
        : Syntax::CommonRuleData(),
            dynamic( false )
    {
    }

    DetectCharRuleData( const Syntax::DetectCharRuleData& other )
        : Syntax::CommonRuleData( other ),
            QE_OTHER_INIT( char_ ),
            QE_OTHER_INIT( dynamic )
    {
    }

    virtual ~DetectCharRuleData() {
    }
};

class Syntax::Detect2CharsRuleData : public Syntax::DetectCharRuleData
{
public:
    // Required
    QChar char1;

    Detect2CharsRuleData()
        : Syntax::DetectCharRuleData()
    {
    }

    Detect2CharsRuleData( const Syntax::Detect2CharsRuleData& other )
        : Syntax::DetectCharRuleData( other ),
            QE_OTHER_INIT( char1 )
    {
    }

    virtual ~Detect2CharsRuleData() {
    }
};

class Syntax::AnyCharRuleData : public Syntax::CommonRuleData
{
public:
    // Required
    QString string;

    AnyCharRuleData()
        : Syntax::CommonRuleData()
    {
    }

    AnyCharRuleData( const Syntax::AnyCharRuleData& other )
        : Syntax::CommonRuleData( other ),
            QE_OTHER_INIT( string )
    {
    }

    virtual ~AnyCharRuleData() {
    }
};

class Syntax::RegExprRuleData : public Syntax::CommonStringRuleData
{
public:
    // Optional
    bool minimal;

    RegExprRuleData()
        : Syntax::CommonStringRuleData(),
            minimal( false )
    {
    }

    RegExprRuleData( const Syntax::RegExprRuleData& other )
        : Syntax::CommonStringRuleData( other ),
            QE_OTHER_INIT( minimal )
    {
    }

    virtual ~RegExprRuleData() {
    }
};

class Syntax::RangeDetectRuleData : public Syntax::CommonRuleData
{
public:
    // Required
    QChar char_;
    QChar char1;

    RangeDetectRuleData()
        : Syntax::CommonRuleData()
    {
    }

    RangeDetectRuleData( const Syntax::RangeDetectRuleData& other )
        : Syntax::CommonRuleData( other ),
            QE_OTHER_INIT( char_ ),
            QE_OTHER_INIT( char1 )
    {
    }

    virtual ~RangeDetectRuleData() {
    }
};

class Syntax::IncludeRulesRuleData : public Syntax::RuleData
{
public:
    // Required
    QString context;
    // Optional
    bool includeAttrib;

    Syntax::Rule::List rules;

    IncludeRulesRuleData()
        : Syntax::RuleData(),
            includeAttrib( false )
    {
    }

    IncludeRulesRuleData( const Syntax::IncludeRulesRuleData& other )
        : Syntax::RuleData( other ),
            QE_OTHER_INIT( context ),
            QE_OTHER_INIT( includeAttrib ),
            QE_OTHER_INIT( rules )
    {
    }

    virtual ~IncludeRulesRuleData() {
    }
};

// Rule

QE_IMPL_SHARED_CLASS_WITH_DEFAULT_DESTRUCTOR( Rule, Syntax )
QE_IMPL_MEMBER( QodeEdit::Rule, type, Rule, Syntax )

bool Syntax::Rule::isNull() const
{
    return d->type == QodeEdit::InvalidRule;
}

QString Syntax::Rule::context() const
{
    switch ( type() ) {
        case QodeEdit::InvalidRule:
            return QString::null;
        case QodeEdit::IncludeRulesRule:
            return toIncludeRules().context();
        default:
            return toCommon().context();
    }
}

Syntax::Rule::List Syntax::Rule::rules() const
{
    switch ( type() ) {
        case QodeEdit::FloatRule:
            return toFloat().rules();
        case QodeEdit::IntRule:
            return toInt().rules();
        case QodeEdit::IncludeRulesRule:
            return toIncludeRules().rules();
        default:
            return Syntax::Rule::List();
    }
}

Syntax::CommonRule Syntax::Rule::toCommon() const
{
    switch ( type() ) {
        case QodeEdit::InvalidRule:
        case QodeEdit::IncludeRulesRule:
            return Syntax::CommonRule();
        default:
            return Syntax::CommonRule( static_cast<Syntax::CommonRuleData*>( d.data() ) );
    }
}

Syntax::KeywordRule Syntax::Rule::toKeyword() const
{
    return d->type != QodeEdit::KeywordRule
        ? Syntax::KeywordRule()
        : Syntax::KeywordRule( static_cast<Syntax::KeywordRuleData*>( d.data() ) )
    ;
}

Syntax::FloatRule Syntax::Rule::toFloat() const
{
    return d->type != QodeEdit::FloatRule
        ? Syntax::FloatRule()
        : Syntax::FloatRule( static_cast<Syntax::FloatRuleData*>( d.data() ) )
    ;
}

Syntax::HlCOctRule Syntax::Rule::toHlCOct() const
{
    return d->type != QodeEdit::HlCOctRule
        ? Syntax::HlCOctRule()
        : Syntax::HlCOctRule( static_cast<Syntax::HlCOctRuleData*>( d.data() ) )
    ;
}

Syntax::HlCHexRule Syntax::Rule::toHlCHex() const
{
    return d->type != QodeEdit::HlCHexRule
        ? Syntax::HlCHexRule()
        : Syntax::HlCHexRule( static_cast<Syntax::HlCHexRuleData*>( d.data() ) )
    ;
}

Syntax::HlCFloatRule Syntax::Rule::toHlCFloat() const
{
    return d->type != QodeEdit::HlCFloatRule
        ? Syntax::HlCFloatRule()
        : Syntax::HlCFloatRule( static_cast<Syntax::HlCFloatRuleData*>( d.data() ) )
    ;
}

Syntax::HlCCharRule Syntax::Rule::toHlCChar() const
{
    return d->type != QodeEdit::HlCCharRule
        ? Syntax::HlCCharRule()
        : Syntax::HlCCharRule( static_cast<Syntax::HlCCharRuleData*>( d.data() ) )
    ;
}

Syntax::HlCStringCharRule Syntax::Rule::toHlCStringChar() const
{
    return d->type != QodeEdit::HlCStringCharRule
        ? Syntax::HlCStringCharRule()
        : Syntax::HlCStringCharRule( static_cast<Syntax::HlCStringCharRuleData*>( d.data() ) )
    ;
}

Syntax::IntRule Syntax::Rule::toInt() const
{
    return d->type != QodeEdit::IntRule
        ? Syntax::IntRule()
        : Syntax::IntRule( static_cast<Syntax::IntRuleData*>( d.data() ) )
    ;
}

Syntax::DetectCharRule Syntax::Rule::toDetectChar() const
{
    return d->type != QodeEdit::DetectCharRule
        ? Syntax::DetectCharRule()
        : Syntax::DetectCharRule( static_cast<Syntax::DetectCharRuleData*>( d.data() ) )
    ;
}

Syntax::Detect2CharsRule Syntax::Rule::toDetect2Chars() const
{
    return d->type != QodeEdit::Detect2CharsRule
        ? Syntax::Detect2CharsRule()
        : Syntax::Detect2CharsRule( static_cast<Syntax::Detect2CharsRuleData*>( d.data() ) )
    ;
}

Syntax::AnyCharRule Syntax::Rule::toAnyChar() const
{
    return d->type != QodeEdit::AnyCharRule
        ? Syntax::AnyCharRule()
        : Syntax::AnyCharRule( static_cast<Syntax::AnyCharRuleData*>( d.data() ) )
    ;
}

Syntax::StringDetectRule Syntax::Rule::toStringDetect() const
{
    return d->type != QodeEdit::StringDetectRule
        ? Syntax::StringDetectRule()
        : Syntax::StringDetectRule( static_cast<Syntax::StringDetectRuleData*>( d.data() ) )
    ;
}

Syntax::WordDetectRule Syntax::Rule::toWordDetect() const
{
    return d->type != QodeEdit::WordDetectRule
        ? Syntax::WordDetectRule()
        : Syntax::WordDetectRule( static_cast<Syntax::WordDetectRuleData*>( d.data() ) )
    ;
}

Syntax::RegExprRule Syntax::Rule::toRegExpr() const
{
    return d->type != QodeEdit::RegExprRule
        ? Syntax::RegExprRule()
        : Syntax::RegExprRule( static_cast<Syntax::RegExprRuleData*>( d.data() ) )
    ;
}

Syntax::LineContinueRule Syntax::Rule::toLineContinue() const
{
    return d->type != QodeEdit::LineContinueRule
        ? Syntax::LineContinueRule()
        : Syntax::LineContinueRule( static_cast<Syntax::LineContinueRuleData*>( d.data() ) )
    ;
}

Syntax::RangeDetectRule Syntax::Rule::toRangeDetect() const
{
    return d->type != QodeEdit::RangeDetectRule
        ? Syntax::RangeDetectRule()
        : Syntax::RangeDetectRule( static_cast<Syntax::RangeDetectRuleData*>( d.data() ) )
    ;
}

Syntax::DetectSpacesRule Syntax::Rule::toDetectSpaces() const
{
    return d->type != QodeEdit::DetectSpacesRule
        ? Syntax::DetectSpacesRule()
        : Syntax::DetectSpacesRule( static_cast<Syntax::DetectSpacesRuleData*>( d.data() ) )
    ;
}

Syntax::DetectIdentifierRule Syntax::Rule::toDetectIdentifier() const
{
    return d->type != QodeEdit::DetectIdentifierRule
        ? Syntax::DetectIdentifierRule()
        : Syntax::DetectIdentifierRule( static_cast<Syntax::DetectIdentifierRuleData*>( d.data() ) )
    ;
}

Syntax::IncludeRulesRule Syntax::Rule::toIncludeRules() const
{
    return d->type != QodeEdit::IncludeRulesRule
        ? Syntax::IncludeRulesRule()
        : Syntax::IncludeRulesRule( static_cast<Syntax::IncludeRulesRuleData*>( d.data() ) )
    ;
}

Syntax::Rule Syntax::Rule::create( QodeEdit::Rule type, const QHash<QString, QVariant>& data )
{
    static QHash<QodeEdit::Rule, QSet<QString> > requiredAttributes;

    if ( requiredAttributes[ type ].isEmpty() ) {
        switch ( type ) {
            case QodeEdit::KeywordRule:
                requiredAttributes[ type ] << "string";
                break;
            case QodeEdit::DetectCharRule:
                requiredAttributes[ type ] << "char";
                break;
            case QodeEdit::Detect2CharsRule:
                requiredAttributes[ type ] << "char" << "char1";
                break;
            case QodeEdit::AnyCharRule:
                requiredAttributes[ type ] << "string";
                break;
            case QodeEdit::StringDetectRule:
                requiredAttributes[ type ] << "string";
                break;
            case QodeEdit::WordDetectRule:
                requiredAttributes[ type ] << "string";
                break;
            case QodeEdit::RegExprRule:
                requiredAttributes[ type ] << "string";
                break;
            case QodeEdit::RangeDetectRule:
                requiredAttributes[ type ] << "char" << "char1";
                break;
            case QodeEdit::IncludeRulesRule:
                requiredAttributes[ type ] << "context";
                break;
            case QodeEdit::InvalidRule:
            case QodeEdit::FloatRule:
            case QodeEdit::HlCOctRule:
            case QodeEdit::HlCHexRule:
            case QodeEdit::HlCFloatRule:
            case QodeEdit::IntRule:
            case QodeEdit::LineContinueRule:
            case QodeEdit::HlCStringCharRule:
            case QodeEdit::HlCCharRule:
            case QodeEdit::DetectSpacesRule:
            case QodeEdit::DetectIdentifierRule:
                break;
        }
    }

    const QSet<QString> requiredKeys = requiredAttributes.value( type );

    if ( !requiredAttributes.value( type ).isEmpty() ) {

        foreach ( const QString& requiredKey, requiredKeys ) {
            if ( data.value( requiredKey ).isNull() ) {
                qWarning( "%s: Missing required attribute '%s' for type %i", Q_FUNC_INFO, qPrintable( requiredKey ), type );
                Q_ASSERT( 0 );
            }
        }
    }

    if ( type == QodeEdit::IncludeRulesRule ) {
        Syntax::IncludeRulesRuleData* d = new Syntax::IncludeRulesRuleData;

        d->type = type;
        d->context = data.value( "context", d->context ).toString().toLower();
        d->includeAttrib = data.value( "includeattrib", d->includeAttrib ).toBool();

        return Syntax::IncludeRulesRule( d );
    }

    Syntax::CommonRuleData* d = 0;

    switch ( type ) {
        case QodeEdit::InvalidRule:
        case QodeEdit::IncludeRulesRule:
            Q_ASSERT( 0 );
            break;
        case QodeEdit::KeywordRule: {
            d = new Syntax::KeywordRuleData;
            Syntax::KeywordRuleData* p = static_cast<Syntax::KeywordRuleData*>( d );
            p->string = data.value( "string", p->string ).toString();
            p->insensitive = data.value( "insensitive", p->insensitive ).toBool();
            p->weakDelimiter = data.value( "weakdelimiter", p->weakDelimiter ).toString();
            break;
        }
        case QodeEdit::FloatRule: {
            d = new Syntax::FloatRuleData;
            //Syntax::FloatRuleData* p = static_cast<Syntax::FloatRuleData*>( d );
            break;
        }
        case QodeEdit::HlCOctRule: {
            d = new Syntax::HlCOctRuleData;
            //Syntax::HlCOctRuleData* p = static_cast<Syntax::HlCOctRuleData*>( d );
            break;
        }
        case QodeEdit::HlCHexRule: {
            d = new Syntax::HlCHexRuleData;
            //Syntax::HlCHexRuleData* p = static_cast<Syntax::HlCHexRuleData*>( d );
            break;
        }
        case QodeEdit::HlCFloatRule: {
            d = new Syntax::HlCFloatRuleData;
            //Syntax::HlCFloatRuleData* p = static_cast<Syntax::HlCFloatRuleData*>( d );
            break;
        }
        case QodeEdit::IntRule: {
            d = new Syntax::IntRuleData;
            //Syntax::IntRuleData* p = static_cast<Syntax::IntRuleData*>( d );
            break;
        }
        case QodeEdit::DetectCharRule: {
            d = new Syntax::DetectCharRuleData;
            Syntax::DetectCharRuleData* p = static_cast<Syntax::DetectCharRuleData*>( d );
            p->dynamic = data.value( "dynamic", p->dynamic ).toBool();
            p->char_ = data.value( "char", p->char_ ).toChar();
            break;
        }
        case QodeEdit::Detect2CharsRule: {
            d = new Syntax::Detect2CharsRuleData;
            Syntax::Detect2CharsRuleData* p = static_cast<Syntax::Detect2CharsRuleData*>( d );
            p->dynamic = data.value( "dynamic", p->dynamic ).toBool();
            p->char_ = data.value( "char", p->char_ ).toChar();
            p->char1 = data.value( "char1", p->char1 ).toChar();
            break;
        }
        case QodeEdit::AnyCharRule: {
            d = new Syntax::AnyCharRuleData;
            Syntax::AnyCharRuleData* p = static_cast<Syntax::AnyCharRuleData*>( d );
            p->string = data.value( "string", p->string ).toString();
            break;
        }
        case QodeEdit::StringDetectRule: {
            d = new Syntax::StringDetectRuleData;
            Syntax::StringDetectRuleData* p = static_cast<Syntax::StringDetectRuleData*>( d );
            p->string = data.value( "string", p->string ).toString();
            p->insensitive = data.value( "insensitive", p->insensitive ).toBool();
            p->dynamic = data.value( "dynamic", p->dynamic ).toBool();
            break;
        }
        case QodeEdit::WordDetectRule: {
            d = new Syntax::WordDetectRuleData;
            Syntax::WordDetectRuleData* p = static_cast<Syntax::WordDetectRuleData*>( d );
            p->string = data.value( "string", p->string ).toString();
            p->insensitive = data.value( "insensitive", p->insensitive ).toBool();
            p->dynamic = data.value( "dynamic", p->dynamic ).toBool();
            break;
        }
        case QodeEdit::RegExprRule: {
            d = new Syntax::RegExprRuleData;
            Syntax::RegExprRuleData* p = static_cast<Syntax::RegExprRuleData*>( d );
            p->string = data.value( "string", p->string ).toString();
            p->insensitive = data.value( "insensitive", p->insensitive ).toBool();
            p->dynamic = data.value( "dynamic", p->dynamic ).toBool();
            p->minimal = data.value( "minimal", p->minimal ).toBool();
            break;
        }
        case QodeEdit::LineContinueRule: {
            d = new Syntax::LineContinueRuleData;
            //Syntax::LineContinueRuleData* p = static_cast<Syntax::LineContinueRuleData*>( d );
            break;
        }
        case QodeEdit::HlCStringCharRule: {
            d = new Syntax::HlCStringCharRuleData;
            //Syntax::HlCStringCharRuleData* p = static_cast<Syntax::HlCStringCharRuleData*>( d );
            break;
        }
        case QodeEdit::RangeDetectRule: {
            d = new Syntax::RangeDetectRuleData;
            Syntax::RangeDetectRuleData* p = static_cast<Syntax::RangeDetectRuleData*>( d );
            p->char_ = data.value( "char", p->char_ ).toChar();
            p->char1 = data.value( "char1", p->char1 ).toChar();
            break;
        }
        case QodeEdit::HlCCharRule: {
            d = new Syntax::HlCCharRuleData;
            //Syntax::HlCCharRuleData* p = static_cast<Syntax::HlCCharRuleData*>( d );
            break;
        }
        case QodeEdit::DetectSpacesRule: {
            d = new Syntax::DetectSpacesRuleData;
            //Syntax::DetectSpacesRuleData* p = static_cast<Syntax::DetectSpacesRuleData*>( d );
            break;
        }
        case QodeEdit::DetectIdentifierRule: {
            d = new Syntax::DetectIdentifierRuleData;
            //Syntax::DetectIdentifierRuleData* p = static_cast<Syntax::DetectIdentifierRuleData*>( d );
            break;
        }
    }

    // common attributes
    if ( d ) {
        d->type = type;
        d->attribute = data.value( "attribute", d->attribute ).toString().toLower();
        d->context = data.value( "context", d->context ).toString().toLower();
        d->beginRegion = data.value( "beginregion", d->beginRegion ).toString();
        d->endRegion = data.value( "endregion", d->endRegion ).toString();
        d->lookAhead = data.value( "lookahead", d->lookAhead ).toBool();
        d->firstNonSpace = data.value( "firstnonspace", d->firstNonSpace ).toBool();
        d->column = data.value( "column", d->column ).toInt();
    }

    return Syntax::Rule( d );
}

// CommonRule

QE_IMPL_HERITED_SHARED_CLASS_WITH_DEFAULT_DESTRUCTOR( CommonRule, Rule, Syntax )
QE_IMPL_MEMBER( QString, attribute, CommonRule, Syntax )
QE_IMPL_MEMBER( QString, context, CommonRule, Syntax )
QE_IMPL_MEMBER( QString, beginRegion, CommonRule, Syntax )
QE_IMPL_MEMBER( QString, endRegion, CommonRule, Syntax )
QE_IMPL_MEMBER( bool, lookAhead, CommonRule, Syntax )
QE_IMPL_MEMBER( bool, firstNonSpace, CommonRule, Syntax )
QE_IMPL_MEMBER( int, column, CommonRule, Syntax )

// CommonRulesRule

QE_IMPL_HERITED_SHARED_CLASS_WITH_DEFAULT_DESTRUCTOR( CommonRulesRule, CommonRule, Syntax )
QE_IMPL_MEMBER( Syntax::Rule::List, rules, CommonRulesRule, Syntax )

// KeywordRule

QE_IMPL_HERITED_SHARED_CLASS_WITH_DEFAULT_DESTRUCTOR( KeywordRule, CommonRule, Syntax )
QE_IMPL_MEMBER( bool, insensitive, KeywordRule, Syntax )
QE_IMPL_MEMBER( QString, string, KeywordRule, Syntax )
QE_IMPL_MEMBER( QString, weakDelimiter, KeywordRule, Syntax )

// FloatRule

QE_IMPL_HERITED_SHARED_CLASS_WITH_DEFAULT_DESTRUCTOR( FloatRule, CommonRulesRule, Syntax )

// HlCOctRule

QE_IMPL_HERITED_SHARED_CLASS_WITH_DEFAULT_DESTRUCTOR( HlCOctRule, CommonRule, Syntax )

// HlCHexRule

QE_IMPL_HERITED_SHARED_CLASS_WITH_DEFAULT_DESTRUCTOR( HlCHexRule, CommonRule, Syntax )

// HlCFloatRule

QE_IMPL_HERITED_SHARED_CLASS_WITH_DEFAULT_DESTRUCTOR( HlCFloatRule, CommonRule, Syntax )

// IntRule

QE_IMPL_HERITED_SHARED_CLASS_WITH_DEFAULT_DESTRUCTOR( IntRule, CommonRulesRule, Syntax )

// DetectCharRule

QE_IMPL_HERITED_SHARED_CLASS_WITH_DEFAULT_DESTRUCTOR( DetectCharRule, CommonRule, Syntax )
QE_IMPL_MEMBER( QChar, char_, DetectCharRule, Syntax )
QE_IMPL_MEMBER( bool, dynamic, DetectCharRule, Syntax )

// Detect2CharsRule

QE_IMPL_HERITED_SHARED_CLASS_WITH_DEFAULT_DESTRUCTOR( Detect2CharsRule, DetectCharRule, Syntax )
QE_IMPL_MEMBER( QChar, char1, Detect2CharsRule, Syntax )

// AnyCharRule

QE_IMPL_HERITED_SHARED_CLASS_WITH_DEFAULT_DESTRUCTOR( AnyCharRule, CommonRule, Syntax )
QE_IMPL_MEMBER( QString, string, AnyCharRule, Syntax )

// StringDetectRule

QE_IMPL_HERITED_SHARED_CLASS_WITH_DEFAULT_DESTRUCTOR( StringDetectRule, CommonRule, Syntax )
QE_IMPL_MEMBER( QString, string, StringDetectRule, Syntax )
QE_IMPL_MEMBER( bool, insensitive, StringDetectRule, Syntax )
QE_IMPL_MEMBER( bool, dynamic, StringDetectRule, Syntax )

// WordDetectRule

QE_IMPL_HERITED_SHARED_CLASS_WITH_DEFAULT_DESTRUCTOR( WordDetectRule, StringDetectRule, Syntax )

// RegExprRule

QE_IMPL_HERITED_SHARED_CLASS_WITH_DEFAULT_DESTRUCTOR( RegExprRule, StringDetectRule, Syntax )
QE_IMPL_MEMBER( bool, minimal, RegExprRule, Syntax )

// LineContinueRule

QE_IMPL_HERITED_SHARED_CLASS_WITH_DEFAULT_DESTRUCTOR( LineContinueRule, CommonRule, Syntax )

// HlCStringCharRule

QE_IMPL_HERITED_SHARED_CLASS_WITH_DEFAULT_DESTRUCTOR( HlCStringCharRule, CommonRule, Syntax )

// RangeDetectRule

QE_IMPL_HERITED_SHARED_CLASS_WITH_DEFAULT_DESTRUCTOR( RangeDetectRule, CommonRule, Syntax )
QE_IMPL_MEMBER( QChar, char_, RangeDetectRule, Syntax )
QE_IMPL_MEMBER( QChar, char1, RangeDetectRule, Syntax )

// HlCCharRule

QE_IMPL_HERITED_SHARED_CLASS_WITH_DEFAULT_DESTRUCTOR( HlCCharRule, CommonRule, Syntax )

// DetectSpacesRule

QE_IMPL_HERITED_SHARED_CLASS_WITH_DEFAULT_DESTRUCTOR( DetectSpacesRule, CommonRule, Syntax )

// DetectIdentifierRule

QE_IMPL_HERITED_SHARED_CLASS_WITH_DEFAULT_DESTRUCTOR( DetectIdentifierRule, CommonRule, Syntax )

// IncludeRulesRule

QE_IMPL_HERITED_SHARED_CLASS_WITH_DEFAULT_DESTRUCTOR( IncludeRulesRule, Rule, Syntax )
QE_IMPL_MEMBER( QString, context, IncludeRulesRule, Syntax )
QE_IMPL_MEMBER( bool, includeAttrib, IncludeRulesRule, Syntax )
QE_IMPL_MEMBER( Syntax::Rule::List, rules, IncludeRulesRule, Syntax )
