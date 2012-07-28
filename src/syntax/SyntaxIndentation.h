#ifndef SYNTAXINDENTATION_H
#define SYNTAXINDENTATION_H

#include <QString>

namespace Syntax {

class Indentation
{
public:
    QString mode;
    
    Indentation();
    virtual ~Indentation();
    
    virtual bool operator==( const Syntax::Indentation& other ) const;
    virtual bool operator!=( const Syntax::Indentation& other ) const;
};

}; // Syntax

#endif // SYNTAXINDENTATION_H
