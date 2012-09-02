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
    QE_DECL_SHARED_CLASS( General );
    
    QE_DECL_MEMBER( Syntax::Folding, folding );
    QE_DECL_MEMBER( Syntax::Comment::List, comments );
    QE_DECL_MEMBER( Syntax::Keywords, keywords );
    QE_DECL_MEMBER( Syntax::Indentation, indentation );
    QE_DECL_MEMBER( Syntax::EmptyLine::List, emptyLines );
};

}; // Syntax

#endif // SYNTAXGENERAL_H
