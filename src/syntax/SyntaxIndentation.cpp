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
            SYNTAX_OTHER_INIT( mode )
    {
    }
    
    virtual ~IndentationData()
    {
    }
};

Syntax::Indentation::Indentation()
    : d( new Syntax::IndentationData )
{
}

Syntax::Indentation::Indentation( const Syntax::Indentation& other )
    : d( other.d )
{
}

Syntax::Indentation::~Indentation()
{
}

SYNTAX_IMPL_MEMBER( QString, mode, Indentation )
SYNTAX_IMPL_OPERATORS( Indentation )
