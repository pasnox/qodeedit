#include "SyntaxHighlighting.h"

Syntax::Highlighting::Highlighting()
{
}

Syntax::Highlighting::~Highlighting()
{
}

bool Syntax::Highlighting::operator==( const Syntax::Highlighting& other ) const
{
    return lists == other.lists &&
        contexts == other.contexts &&
        itemDatas == other.itemDatas
    ;
}

bool Syntax::Highlighting::operator!=( const Syntax::Highlighting& other ) const
{
    return !operator==( other );
}

Syntax::List Syntax::Highlighting::list( const QString& name ) const
{
    return lists.value( name );
}
