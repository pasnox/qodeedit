#ifndef SYNTAXGENERAL_H
#define SYNTAXGENERAL_H

#include "SyntaxComment.h"
#include "SyntaxKeywords.h"
#include "SyntaxFolding.h"

namespace Syntax {

class General
{
public:
    Syntax::Comment::Hash comments;
    Syntax::Keywords keywords;
    Syntax::Folding folding;
    
    General();
    virtual ~General();
};

}; // Syntax

#endif // SYNTAXGENERAL_H
