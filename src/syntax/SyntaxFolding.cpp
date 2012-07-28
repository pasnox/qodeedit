#include "SyntaxFolding.h"

Syntax::Folding::Folding()
{
}

Syntax::Folding::~Folding()
{
}

bool Syntax::Folding::operator==( const Syntax::Folding& other ) const
{
    return
        indentationSensitive == other.indentationSensitive
    ;
}

bool Syntax::Folding::operator!=( const Syntax::Folding& other ) const
{
    return !operator==( other );
}
