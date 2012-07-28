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
    
    virtual bool operator==( const Syntax::Configuration& other ) const;
    virtual bool operator!=( const Syntax::Configuration& other ) const;
};

}; // Syntax

#endif // SYNTAXCONFIGURATION_H
