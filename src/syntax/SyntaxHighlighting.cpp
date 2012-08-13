#include "SyntaxHighlighting.h"

class Syntax::HighlightingData : public QSharedData
{
public:
    QString initialContext;
    Syntax::Highlighting::Hash lists;
    Syntax::Context::Hash contexts;
    Syntax::ItemData::Hash itemDatas;
    
    HighlightingData()
        : QSharedData()
    {
    }
    
    HighlightingData( const Syntax::HighlightingData& other )
        : QSharedData( other ),
            SYNTAX_OTHER_INIT( initialContext ),
            SYNTAX_OTHER_INIT( lists ),
            SYNTAX_OTHER_INIT( contexts ),
            SYNTAX_OTHER_INIT( itemDatas )
    {
    }
    
    virtual ~HighlightingData() {
    }
};

Syntax::Highlighting::Highlighting()
    : d( new Syntax::HighlightingData )
{
}

Syntax::Highlighting::Highlighting( const Syntax::Highlighting& other )
    : d( other.d )
{
}

Syntax::Highlighting::~Highlighting()
{
}

SYNTAX_IMPL_MEMBER( QString, initialContext, Highlighting )
SYNTAX_IMPL_MEMBER( Syntax::Highlighting::Hash, lists, Highlighting )
SYNTAX_IMPL_MEMBER( Syntax::Context::Hash, contexts, Highlighting )
SYNTAX_IMPL_MEMBER( Syntax::ItemData::Hash, itemDatas, Highlighting )
SYNTAX_IMPL_OPERATORS( Highlighting )

Syntax::List Syntax::Highlighting::list( const QString& name ) const
{
    return d->lists.value( name );
}
