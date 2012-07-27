#ifndef SYNTAXCONFIGURATION_H
#define SYNTAXCONFIGURATION_H

#include <QString>

namespace Syntax {

class Configuration
{
public:
    QString encodingReplacementPolicy;
    
    Configuration();
    virtual ~Configuration();
};

}; // Syntax

#endif // SYNTAXCONFIGURATION_H
