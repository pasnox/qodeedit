#include "SyntaxGeneral.h"

Syntax::General::General()
{
}

Syntax::General::~General()
{
}

bool Syntax::General::operator==( const Syntax::General& other ) const
{
    return comments == other.comments &&
        keywords == other.keywords &&
        folding == other.folding &&
        indentation == other.indentation &&
        emptyLines == other.emptyLines
    ;
}

bool Syntax::General::operator!=( const Syntax::General& other ) const
{
    return !operator==( other );
}
