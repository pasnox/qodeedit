#include "SyntaxRule.h"
#include "QodeEdit.h"

class Syntax::RuleData : public QSharedData
{
public:
    QString type;
    QString attribute;
    QString context;
    QString string;
    QString beginRegion;
    bool firstNonSpace;
    QString char_;
    bool lookAhead;
    QString endRegion;
    bool insensitive;
    QString char1;
    int column;
    bool dynamic;
    bool minimal;
    bool includeAttrib;
    QString region;
    QString lineEndContext;
    QString weakDelimiter;
    Syntax::Rule::List rules;
    
    RuleData()
        : QSharedData(),
            firstNonSpace( false ),
            lookAhead( false ),
            insensitive( false ),
            column( -1 ),
            dynamic( false ),
            minimal( false ),
            includeAttrib( false )
    {
    }
    
    RuleData( const Syntax::RuleData& other )
        : QSharedData( other ),
            SYNTAX_OTHER_INIT( type ),
            SYNTAX_OTHER_INIT( attribute ),
            SYNTAX_OTHER_INIT( context ),
            SYNTAX_OTHER_INIT( string ),
            SYNTAX_OTHER_INIT( beginRegion ),
            SYNTAX_OTHER_INIT( firstNonSpace ),
            SYNTAX_OTHER_INIT( char_ ),
            SYNTAX_OTHER_INIT( lookAhead ),
            SYNTAX_OTHER_INIT( endRegion ),
            SYNTAX_OTHER_INIT( insensitive ),
            SYNTAX_OTHER_INIT( char1 ),
            SYNTAX_OTHER_INIT( column ),
            SYNTAX_OTHER_INIT( dynamic ),
            SYNTAX_OTHER_INIT( minimal ),
            SYNTAX_OTHER_INIT( includeAttrib ),
            SYNTAX_OTHER_INIT( region ),
            SYNTAX_OTHER_INIT( lineEndContext ),
            SYNTAX_OTHER_INIT( weakDelimiter ),
            SYNTAX_OTHER_INIT( rules )
    {
    }
    
    virtual ~RuleData() {
    }
};

Syntax::Rule::Rule()
    : d( new Syntax::RuleData )
{
}

Syntax::Rule::Rule( const Syntax::Rule& other )
    : d( other.d )
{
}

Syntax::Rule::~Rule()
{
}

SYNTAX_IMPL_MEMBER( QString, type, Rule )
SYNTAX_IMPL_MEMBER( QString, attribute, Rule )
SYNTAX_IMPL_MEMBER( QString, context, Rule )
SYNTAX_IMPL_MEMBER( QString, string, Rule )
SYNTAX_IMPL_MEMBER( QString, beginRegion, Rule )
SYNTAX_IMPL_MEMBER( bool, firstNonSpace, Rule )
SYNTAX_IMPL_MEMBER( QString, char_, Rule )
SYNTAX_IMPL_MEMBER( bool, lookAhead, Rule )
SYNTAX_IMPL_MEMBER( QString, endRegion, Rule )
SYNTAX_IMPL_MEMBER( bool, insensitive, Rule )
SYNTAX_IMPL_MEMBER( QString, char1, Rule )
SYNTAX_IMPL_MEMBER( int, column, Rule )
SYNTAX_IMPL_MEMBER( bool, dynamic, Rule )
SYNTAX_IMPL_MEMBER( bool, minimal, Rule )
SYNTAX_IMPL_MEMBER( bool, includeAttrib, Rule )
SYNTAX_IMPL_MEMBER( QString, region, Rule )
SYNTAX_IMPL_MEMBER( QString, lineEndContext, Rule )
SYNTAX_IMPL_MEMBER( QString, weakDelimiter, Rule )
SYNTAX_IMPL_MEMBER( Syntax::Rule::List, rules, Rule )
SYNTAX_IMPL_OPERATORS( Rule )

Syntax::Rule::Type Syntax::Rule::enumType() const
{
    if ( d->type.isEmpty() ) {
        return Syntax::Rule::Invalid;
    }
    else if ( QodeEdit::stringEquals( d->type, "AnyChar" ) ) {
        return Syntax::Rule::AnyChar;
    }
    else if ( QodeEdit::stringEquals( d->type, "Detect2Chars" ) ) {
        return Syntax::Rule::Detect2Chars;
    }
    else if ( QodeEdit::stringEquals( d->type, "DetectChar" ) ) {
        return Syntax::Rule::DetectChar;
    }
    else if ( QodeEdit::stringEquals( d->type, "DetectIdentifier" ) ) {
        return Syntax::Rule::DetectIdentifier;
    }
    else if ( QodeEdit::stringEquals( d->type, "DetectSpaces" ) ) {
        return Syntax::Rule::DetectSpaces;
    }
    else if ( QodeEdit::stringEquals( d->type, "Float" ) ) {
        return Syntax::Rule::Float;
    }
    else if ( QodeEdit::stringEquals( d->type, "HlCChar" ) ) {
        return Syntax::Rule::HlCChar;
    }
    else if ( QodeEdit::stringEquals( d->type, "HlCHex" ) ) {
        return Syntax::Rule::HlCHex;
    }
    else if ( QodeEdit::stringEquals( d->type, "HlCOct" ) ) {
        return Syntax::Rule::HlCOct;
    }
    else if ( QodeEdit::stringEquals( d->type, "HlCStringChar" ) ) {
        return Syntax::Rule::HlCStringChar;
    }
    else if ( QodeEdit::stringEquals( d->type, "IncludeRules" ) ) {
        return Syntax::Rule::IncludeRules;
    }
    else if ( QodeEdit::stringEquals( d->type, "Int" ) ) {
        return Syntax::Rule::Int;
    }
    else if ( QodeEdit::stringEquals( d->type, "Keyword" ) ) {
        return Syntax::Rule::Keyword;
    }
    else if ( QodeEdit::stringEquals( d->type, "LineContinue" ) ) {
        return Syntax::Rule::LineContinue;
    }
    else if ( QodeEdit::stringEquals( d->type, "RangeDetect" ) ) {
        return Syntax::Rule::RangeDetect;
    }
    else if ( QodeEdit::stringEquals( d->type, "RegExpr" ) ) {
        return Syntax::Rule::RegExpr;
    }
    else if ( QodeEdit::stringEquals( d->type, "StringDetect" ) ) {
        return Syntax::Rule::StringDetect;
    }
    else if ( QodeEdit::stringEquals( d->type, "WordDetect" ) ) {
        return Syntax::Rule::WordDetect;
    }
    
    return Syntax::Rule::Invalid;
}
