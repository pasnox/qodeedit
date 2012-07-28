#include "SyntaxEmptyLine.h"

Syntax::EmptyLine::EmptyLine()
{
}

Syntax::EmptyLine::~EmptyLine()
{
}

bool Syntax::EmptyLine::operator==( const Syntax::EmptyLine& other ) const
{
    return regExpr == other.regExpr &&
        caseSensitive == other.caseSensitive
    ;
}

bool Syntax::EmptyLine::operator!=( const Syntax::EmptyLine& other ) const
{
    return !operator==( other );
}
