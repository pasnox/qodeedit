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
            QE_OTHER_INIT( indentationSensitive )
    {
    }
    
    virtual ~FoldingData() {
    }
};

QE_IMPL_SHARED_CLASS( Folding )

Syntax::Folding::~Folding()
{
}

QE_IMPL_MEMBER( bool, indentationSensitive, Folding )
