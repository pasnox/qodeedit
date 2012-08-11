#include "SyntaxSpellChecking.h"

class Syntax::SpellCheckingData : public QSharedData
{
public:
    Syntax::Configuration configuration;
    Syntax::Encoding::List encodings;
    
    SpellCheckingData()
        : QSharedData()
    {
    }
    
    SpellCheckingData( const Syntax::SpellCheckingData& other )
        : QSharedData( other ),
            SYNTAX_OTHER_INIT( configuration ),
            SYNTAX_OTHER_INIT( encodings )
    {
    }
    
    virtual ~SpellCheckingData()
    {
    }
};

Syntax::SpellChecking::SpellChecking()
    : d( new Syntax::SpellCheckingData )
{
}

Syntax::SpellChecking::SpellChecking( const Syntax::SpellChecking& other )
    : d( other.d )
{
}

Syntax::SpellChecking::~SpellChecking()
{
}

SYNTAX_IMPL_MEMBER( Syntax::Configuration, configuration, SpellChecking )
SYNTAX_IMPL_MEMBER( Syntax::Encoding::List, encodings, SpellChecking )
SYNTAX_IMPL_OPERATORS( SpellChecking )
