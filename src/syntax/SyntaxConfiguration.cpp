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
    
    virtual ~ConfigurationData()
    {
    }
};

Syntax::Configuration::Configuration()
    : d( new Syntax::ConfigurationData ),
        SYNTAX_D_INIT( encodingReplacementPolicy )
{
}

Syntax::Configuration::Configuration( const Syntax::Configuration& other )
    : d( other.d ),
        SYNTAX_D_INIT( encodingReplacementPolicy )
{
}

Syntax::Configuration::~Configuration()
{
}

Syntax::Configuration& Syntax::Configuration::operator=( const Syntax::Configuration& other )
{
    if ( this != &other ) {
        d = other.d;
        SYNTAX_D_COPY( encodingReplacementPolicy );
    }
    
    return *this;
}
