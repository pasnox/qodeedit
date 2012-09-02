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
            QE_OTHER_INIT( configuration ),
            QE_OTHER_INIT( encodings )
    {
    }
    
    virtual ~SpellCheckingData() {
    }
};

QE_IMPL_SHARED_CLASS( SpellChecking )

Syntax::SpellChecking::~SpellChecking()
{
}

QE_IMPL_MEMBER( Syntax::Configuration, configuration, SpellChecking )
QE_IMPL_MEMBER( Syntax::Encoding::List, encodings, SpellChecking )
