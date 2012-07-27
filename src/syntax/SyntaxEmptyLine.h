#ifndef SYNTAXEMPTYLINE_H
#define SYNTAXEMPTYLINE_H

#include <QString>

namespace Syntax {

class EmptyLine
{
public:
    typedef QList<Syntax::EmptyLine> List;
    
    QString regExpr;
    bool caseSensitive;
    
    EmptyLine();
    virtual ~EmptyLine();
};

}; // Syntax

#endif // SYNTAXEMPTYLINE_H
