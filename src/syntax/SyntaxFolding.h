#ifndef SYNTAXFOLDING_H
#define SYNTAXFOLDING_H

#include <QString>

namespace Syntax {

class Folding
{
public:
    bool indentationSensitive;
    
    Folding();
    virtual ~Folding();
};

}; // Syntax

#endif // SYNTAXFOLDING_H
