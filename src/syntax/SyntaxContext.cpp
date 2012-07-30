#include "SyntaxContext.h"

Syntax::Context::Context()
{
    fallThrough = false;
    dynamic = false;
    noIndentationBasedFolding = false;
    caseSensitive = false;
}

Syntax::Context::~Context()
{
}

bool Syntax::Context::operator==( const Syntax::Context& other ) const
{
    return name == other.name &&
        attribute == other.attribute &&
        lineEndContext == other.lineEndContext &&
        fallThrough == other.fallThrough &&
        fallThroughContext == other.fallThroughContext &&
        dynamic == other.dynamic &&
        noIndentationBasedFolding == other.noIndentationBasedFolding &&
        caseSensitive == other.caseSensitive &&
        rules == other.rules
    ;
}

bool Syntax::Context::operator!=( const Syntax::Context& other ) const
{
    return !operator==( other );
}
