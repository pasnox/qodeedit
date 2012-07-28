#include "SyntaxSpellChecking.h"

Syntax::SpellChecking::SpellChecking()
{
}

Syntax::SpellChecking::~SpellChecking()
{
}

bool Syntax::SpellChecking::operator==( const Syntax::SpellChecking& other ) const
{
    return configuration == other.configuration &&
        encodings == other.encodings
    ;
}

bool Syntax::SpellChecking::operator!=( const Syntax::SpellChecking& other ) const
{
    return !operator==( other );
}
