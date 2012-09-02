#include "SyntaxIndentation.h"

class Syntax::IndentationData : public QSharedData
{
public:
    QString mode;
    
    IndentationData()
        : QSharedData()
    {
    }
    
    IndentationData( const Syntax::IndentationData& other )
        : QSharedData( other ),
            QE_OTHER_INIT( mode )
    {
    }
    
    virtual ~IndentationData() {
    }
};

QE_IMPL_SHARED_CLASS( Indentation )

Syntax::Indentation::~Indentation()
{
}

QE_IMPL_MEMBER( QString, mode, Indentation )
