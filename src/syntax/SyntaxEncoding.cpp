#include "SyntaxEncoding.h"

Syntax::Encoding::Encoding()
{
    ignored = false;
}

Syntax::Encoding::~Encoding()
{
}

bool Syntax::Encoding::operator==( const Syntax::Encoding& other ) const
{
    return char_ == other.char_ &&
        string == other.string &&
        ignored == other.ignored
    ;
}

bool Syntax::Encoding::operator!=( const Syntax::Encoding& other ) const
{
    return !operator==( other );
}
