#include "SyntaxComment.h"

Syntax::Comment::Comment()
{
}

Syntax::Comment::~Comment()
{
}

bool Syntax::Comment::operator==( const Syntax::Comment& other ) const
{
    return name == other.name &&
        start == other.start &&
        end == other.end &&
        region == other.region &&
        weakDeliminator == other.weakDeliminator &&
        position == other.position
    ;
}

bool Syntax::Comment::operator!=( const Syntax::Comment& other ) const
{
    return !operator==( other );
}
