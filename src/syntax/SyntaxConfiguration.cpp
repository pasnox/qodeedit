#include "SyntaxConfiguration.h"

class Syntax::ConfigurationData : public QSharedData
{
public:
    QString encodingReplacementPolicy;
    
    ConfigurationData()
        : QSharedData()
    {
    }
    
    ConfigurationData( const Syntax::ConfigurationData& other )
        : QSharedData( other ),
            SYNTAX_OTHER_INIT( encodingReplacementPolicy )
    {
    }
    
    virtual ~ConfigurationData() {
    }
};

Syntax::Configuration::Configuration()
    : d( new Syntax::ConfigurationData )
{
}

Syntax::Configuration::Configuration( const Syntax::Configuration& other )
    : d( other.d )
{
}

Syntax::Configuration::~Configuration()
{
}

SYNTAX_IMPL_MEMBER( QString, encodingReplacementPolicy, Configuration )
SYNTAX_IMPL_OPERATORS( Configuration )
