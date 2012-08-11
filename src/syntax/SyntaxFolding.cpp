#include "SyntaxFolding.h"

class Syntax::FoldingData : public QSharedData
{
public:
    bool indentationSensitive;
    
    FoldingData()
        : QSharedData(),
            indentationSensitive( false )
    {
    }
    
    FoldingData( const Syntax::FoldingData& other )
        : QSharedData( other ),
            SYNTAX_OTHER_INIT( indentationSensitive )
    {
    }
    
    virtual ~FoldingData()
    {
    }
};

Syntax::Folding::Folding()
    : d( new Syntax::FoldingData )
{
}

Syntax::Folding::Folding( const Syntax::Folding& other )
    : d( other.d )
{
}

Syntax::Folding::~Folding()
{
}

SYNTAX_IMPL_MEMBER( bool, indentationSensitive, Folding )
SYNTAX_IMPL_OPERATORS( Folding )
