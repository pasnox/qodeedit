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
    QE_DECL_SHARED_CLASS( Folding );
    
    // Required
    // optional
    QE_DECL_MEMBER( bool, indentationSensitive );
};

}; // Syntax

#endif // SYNTAXFOLDING_H
