#ifndef SYNTAXKEYWORDS_H
#define SYNTAXKEYWORDS_H

#include <QString>

namespace Syntax {

class Keywords
{
public:
    QString caseSensitive;
    
    Keywords();
    virtual ~Keywords();
};

}; // Syntax

#endif // SYNTAXKEYWORDS_H
