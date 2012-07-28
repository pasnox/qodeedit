#include "SyntaxRule.h"

Syntax::Rule::Rule()
{
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
