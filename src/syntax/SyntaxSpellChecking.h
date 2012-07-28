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
    
    virtual bool operator==( const Syntax::SpellChecking& other ) const;
    virtual bool operator!=( const Syntax::SpellChecking& other ) const;
};

}; // Syntax

#endif // SYNTAXSPELLCHECKING_H
