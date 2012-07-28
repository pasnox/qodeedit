#include "SyntaxConfiguration.h"

Syntax::Configuration::Configuration()
{
}

Syntax::Configuration::~Configuration()
{
}

bool Syntax::Configuration::operator==( const Syntax::Configuration& other ) const
{
    return
        encodingReplacementPolicy == other.encodingReplacementPolicy
    ;
}

bool Syntax::Configuration::operator!=( const Syntax::Configuration& other ) const
{
    return !operator==( other );
}
