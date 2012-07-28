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
    
    virtual bool operator==( const Syntax::Folding& other ) const;
    virtual bool operator!=( const Syntax::Folding& other ) const;
};

}; // Syntax

#endif // SYNTAXFOLDING_H
