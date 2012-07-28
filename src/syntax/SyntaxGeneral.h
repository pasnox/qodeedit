#ifndef SYNTAXGENERAL_H
#define SYNTAXGENERAL_H

#include "SyntaxComment.h"
#include "SyntaxKeywords.h"
#include "SyntaxFolding.h"
#include "SyntaxEmptyLine.h"
#include "SyntaxIndentation.h"

namespace Syntax {

class General
{
public:
    Syntax::Comment::List comments;
    Syntax::Keywords keywords;
    Syntax::Folding folding;
    Syntax::Indentation indentation;
    Syntax::EmptyLine::List emptyLines;
    
    General();
    virtual ~General();
    
    virtual bool operator==( const Syntax::General& other ) const;
    virtual bool operator!=( const Syntax::General& other ) const;
};

}; // Syntax

#endif // SYNTAXGENERAL_H
