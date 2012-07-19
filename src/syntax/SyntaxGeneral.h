#ifndef SYNTAXGENERAL_H
#define SYNTAXGENERAL_H

#include "SyntaxComment.h"
#include "SyntaxKeywords.h"

namespace Syntax {

class General
{
public:
    Syntax::Comment::Hash comments;
    Syntax::Keywords keywords;
    
    General();
    virtual ~General();
};

}; // Syntax

#endif // SYNTAXGENERAL_H
