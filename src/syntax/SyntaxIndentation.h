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
};

}; // Syntax

#endif // SYNTAXINDENTATION_H
