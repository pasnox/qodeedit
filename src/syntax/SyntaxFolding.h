#ifndef SYNTAXFOLDING_H
#define SYNTAXFOLDING_H

#include <QExplicitlySharedDataPointer>
#include <QString>

#include "SyntaxHelpers.h"

namespace Syntax {

class FoldingData;

class Folding
{
private:
    QExplicitlySharedDataPointer<Syntax::FoldingData> d;
    
public:
    // Required
    // optional
    SYNTAX_DECL_MEMBER( bool, indentationSensitive );
    
    Folding();
    Folding( const Syntax::Folding& other );
    virtual ~Folding();
    
    SYNTAX_DECL_OPERATORS( Folding );
};

}; // Syntax

#endif // SYNTAXFOLDING_H
