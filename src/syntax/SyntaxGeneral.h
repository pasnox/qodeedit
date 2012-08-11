#ifndef SYNTAXGENERAL_H
#define SYNTAXGENERAL_H

#include <QExplicitlySharedDataPointer>

#include "SyntaxHelpers.h"
#include "SyntaxComment.h"
#include "SyntaxKeywords.h"
#include "SyntaxFolding.h"
#include "SyntaxEmptyLine.h"
#include "SyntaxIndentation.h"

namespace Syntax {

class GeneralData;

class General
{
private:
    QExplicitlySharedDataPointer<Syntax::GeneralData> d;
    
public:
    SYNTAX_DECL_MEMBER( Syntax::Comment::List, comments );
    SYNTAX_DECL_MEMBER( Syntax::Keywords, keywords );
    SYNTAX_DECL_MEMBER( Syntax::Folding, folding );
    SYNTAX_DECL_MEMBER( Syntax::Indentation, indentation );
    SYNTAX_DECL_MEMBER( Syntax::EmptyLine::List, emptyLines );
    
    General();
    General( const Syntax::General& other );
    virtual ~General();
    
    SYNTAX_DECL_OPERATORS( General );
};

}; // Syntax

#endif // SYNTAXGENERAL_H
