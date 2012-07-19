#include "SyntaxHighlighting.h"

Syntax::Highlighting::Highlighting()
{
}

Syntax::Highlighting::~Highlighting()
{
}

Syntax::List Syntax::Highlighting::list( const QString& name ) const
{
    return lists.value( name );
}
