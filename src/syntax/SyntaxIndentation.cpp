#include "SyntaxIndentation.h"

Syntax::Indentation::Indentation()
{
}

Syntax::Indentation::~Indentation()
{
}

bool Syntax::Indentation::operator==( const Syntax::Indentation& other ) const
{
    return
        mode == other.mode
    ;
}

bool Syntax::Indentation::operator!=( const Syntax::Indentation& other ) const
{
    return !operator==( other );
}
