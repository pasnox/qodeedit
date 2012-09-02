#ifndef SYNTAXSPELLCHECKING_H
#define SYNTAXSPELLCHECKING_H

#include <QExplicitlySharedDataPointer>

#include "SyntaxHelpers.h"
#include "SyntaxConfiguration.h"
#include "SyntaxEncoding.h"

namespace Syntax {

class SpellCheckingData;

class SpellChecking
{
private:
    QExplicitlySharedDataPointer<Syntax::SpellCheckingData> d;
    
public:
    QE_DECL_SHARED_CLASS( SpellChecking );
    
    // Required
    // Optional
    QE_DECL_MEMBER( Syntax::Configuration, configuration );
    QE_DECL_MEMBER( Syntax::Encoding::List, encodings );
};

}; // Syntax

#endif // SYNTAXSPELLCHECKING_H
