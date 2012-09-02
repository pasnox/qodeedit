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
    QE_DECL_SHARED_CLASS( Configuration );
    
    // Required
    // Optional
    QE_DECL_MEMBER( QString, encodingReplacementPolicy ); // enum: EncodeAlways, EncodeWhenPresent, EncodeNever,
};

}; // Syntax

#endif // SYNTAXCONFIGURATION_H
