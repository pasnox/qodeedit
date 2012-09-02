#include "SyntaxHighlighting.h"

class Syntax::HighlightingData : public QSharedData
{
public:
    QString defaultContext;
    Syntax::HashList lists;
    Syntax::Context::Hash contexts;
    Syntax::ItemData::Hash itemDatas;
    
    HighlightingData()
        : QSharedData()
    {
    }
    
    HighlightingData( const Syntax::HighlightingData& other )
        : QSharedData( other ),
            QE_OTHER_INIT( defaultContext ),
            QE_OTHER_INIT( lists ),
            QE_OTHER_INIT( contexts ),
            QE_OTHER_INIT( itemDatas )
    {
    }
    
    virtual ~HighlightingData() {
    }
};

QE_IMPL_SHARED_CLASS( Highlighting )

Syntax::Highlighting::~Highlighting()
{
}

QE_IMPL_MEMBER( QString, defaultContext, Highlighting )
QE_IMPL_MEMBER( Syntax::HashList, lists, Highlighting )
QE_IMPL_MEMBER( Syntax::Context::Hash, contexts, Highlighting )
QE_IMPL_MEMBER( Syntax::ItemData::Hash, itemDatas, Highlighting )

Syntax::List Syntax::Highlighting::list( const QString& name ) const
{
    return d->lists.value( name );
}
