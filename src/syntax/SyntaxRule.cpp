#include "SyntaxRule.h"
#include "QodeEdit.h"

Syntax::Rule::Rule()
{
    firstNonSpace = false;
    lookAhead = false;
    insensitive = false;
    column = -1;
    dynamic = false;
    minimal = false;
    includeAttrib = false;
}

Syntax::Rule::~Rule()
{
}

bool Syntax::Rule::operator==( const Syntax::Rule& other ) const
{
    return type == other.type &&
        attribute == other.attribute &&
        context == other.context &&
        string == other.string &&
        beginRegion == other.beginRegion &&
        firstNonSpace == other.firstNonSpace &&
        char_ == other.char_ &&
        lookAhead == other.lookAhead &&
        endRegion == other.endRegion &&
        insensitive == other.insensitive &&
        char1 == other.char1 &&
        column == other.column &&
        dynamic == other.dynamic &&
        minimal == other.minimal &&
        includeAttrib == other.includeAttrib &&
        region == other.region &&
        lineEndContext == other.lineEndContext &&
        weakDelimiter == other.weakDelimiter &&
        rules == other.rules
    ;
}

bool Syntax::Rule::operator!=( const Syntax::Rule& other ) const
{
    return !operator==( other );
}

Syntax::Rule::Type Syntax::Rule::enumType() const
{
    if ( type.isEmpty() ) {
        return Syntax::Rule::Invalid;
    }
    else if ( QodeEdit::stringEquals( type, "AnyChar" ) ) {
        return Syntax::Rule::AnyChar;
    }
    else if ( QodeEdit::stringEquals( type, "Detect2Chars" ) ) {
        return Syntax::Rule::Detect2Chars;
    }
    else if ( QodeEdit::stringEquals( type, "DetectChar" ) ) {
        return Syntax::Rule::DetectChar;
    }
    else if ( QodeEdit::stringEquals( type, "DetectIdentifier" ) ) {
        return Syntax::Rule::DetectIdentifier;
    }
    else if ( QodeEdit::stringEquals( type, "DetectSpaces" ) ) {
        return Syntax::Rule::DetectSpaces;
    }
    else if ( QodeEdit::stringEquals( type, "Float" ) ) {
        return Syntax::Rule::Float;
    }
    else if ( QodeEdit::stringEquals( type, "HlCChar" ) ) {
        return Syntax::Rule::HlCChar;
    }
    else if ( QodeEdit::stringEquals( type, "HlCHex" ) ) {
        return Syntax::Rule::HlCHex;
    }
    else if ( QodeEdit::stringEquals( type, "HlCOct" ) ) {
        return Syntax::Rule::HlCOct;
    }
    else if ( QodeEdit::stringEquals( type, "HlCStringChar" ) ) {
        return Syntax::Rule::HlCStringChar;
    }
    else if ( QodeEdit::stringEquals( type, "IncludeRules" ) ) {
        return Syntax::Rule::IncludeRules;
    }
    else if ( QodeEdit::stringEquals( type, "Int" ) ) {
        return Syntax::Rule::Int;
    }
    else if ( QodeEdit::stringEquals( type, "Keyword" ) ) {
        return Syntax::Rule::Keyword;
    }
    else if ( QodeEdit::stringEquals( type, "LineContinue" ) ) {
        return Syntax::Rule::LineContinue;
    }
    else if ( QodeEdit::stringEquals( type, "RangeDetect" ) ) {
        return Syntax::Rule::RangeDetect;
    }
    else if ( QodeEdit::stringEquals( type, "RegExpr" ) ) {
        return Syntax::Rule::RegExpr;
    }
    else if ( QodeEdit::stringEquals( type, "StringDetect" ) ) {
        return Syntax::Rule::StringDetect;
    }
    else if ( QodeEdit::stringEquals( type, "WordDetect" ) ) {
        return Syntax::Rule::WordDetect;
    }
    
    return Syntax::Rule::Invalid;
}
