#include "SyntaxKeywords.h"

Syntax::Keywords::Keywords()
{
    caseSensitive = false;
}

Syntax::Keywords::~Keywords()
{
}

bool Syntax::Keywords::operator==( const Syntax::Keywords& other ) const
{
    return caseSensitive == other.caseSensitive &&
        weakDeliminator == other.weakDeliminator &&
        additionalDeliminator == other.additionalDeliminator &&
        wordWrapDeliminator == other.wordWrapDeliminator
    ;
}

bool Syntax::Keywords::operator!=( const Syntax::Keywords& other ) const
{
    return !operator==( other );
}
