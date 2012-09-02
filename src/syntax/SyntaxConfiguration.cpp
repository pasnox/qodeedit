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
            QE_OTHER_INIT( encodingReplacementPolicy )
    {
    }
    
    virtual ~ConfigurationData() {
    }
};

QE_IMPL_SHARED_CLASS( Configuration )

Syntax::Configuration::~Configuration()
{
}

QE_IMPL_MEMBER( QString, encodingReplacementPolicy, Configuration )
