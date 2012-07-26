#ifndef SYNTAXEMPTYLINE_H
#define SYNTAXEMPTYLINE_H

#include <QString>

namespace Syntax {

class EmptyLine
{
public:
    typedef QList<Syntax::EmptyLine> List;
    
    QString regExpr;
    QString caseSensitive;
    
    EmptyLine();
    virtual ~EmptyLine();
};

}; // Syntax

#endif // SYNTAXEMPTYLINE_H
