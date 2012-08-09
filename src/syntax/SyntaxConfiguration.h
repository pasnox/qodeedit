#ifndef SYNTAXCONFIGURATION_H
#define SYNTAXCONFIGURATION_H

#include <QExplicitlySharedDataPointer>
#include <QString>

#include "SyntaxHelpers.h"

namespace Syntax {

class ConfigurationData;

class Configuration
{
private:
    QExplicitlySharedDataPointer<Syntax::ConfigurationData> d;
    
public:
    QString& encodingReplacementPolicy;
    
    Configuration();
    Configuration( const Syntax::Configuration& other );
    virtual ~Configuration();
    
    SYNTAX_OPERATORS( Configuration )
    virtual Syntax::Configuration& operator=( const Syntax::Configuration& other );
};

}; // Syntax

#endif // SYNTAXCONFIGURATION_H
