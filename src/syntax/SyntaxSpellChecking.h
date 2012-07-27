#ifndef SYNTAXSPELLCHECKING_H
#define SYNTAXSPELLCHECKING_H

#include "SyntaxConfiguration.h"
#include "SyntaxEncoding.h"

namespace Syntax {

class SpellChecking
{
public:
    Syntax::Configuration configuration;
    Syntax::Encoding::List encodings;
    
    SpellChecking();
    virtual ~SpellChecking();
};

}; // Syntax

#endif // SYNTAXSPELLCHECKING_H
