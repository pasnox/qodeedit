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
    // Required
    // Optional
    SYNTAX_DECL_MEMBER( QString, encodingReplacementPolicy ); // enum: EncodeAlways, EncodeWhenPresent, EncodeNever,
    
    Configuration();
    Configuration( const Syntax::Configuration& other );
    virtual ~Configuration();
    
    SYNTAX_DECL_OPERATORS( Configuration );
};

}; // Syntax

#endif // SYNTAXCONFIGURATION_H
