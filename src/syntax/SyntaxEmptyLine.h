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
    
    virtual bool operator==( const Syntax::EmptyLine& other ) const;
    virtual bool operator!=( const Syntax::EmptyLine& other ) const;
};

}; // Syntax

#endif // SYNTAXEMPTYLINE_H
