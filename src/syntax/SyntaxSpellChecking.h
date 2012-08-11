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
    SYNTAX_DECL_MEMBER( Syntax::Configuration, configuration );
    SYNTAX_DECL_MEMBER( Syntax::Encoding::List, encodings );
    
    SpellChecking();
    SpellChecking( const Syntax::SpellChecking& other );
    virtual ~SpellChecking();
    
    SYNTAX_DECL_OPERATORS( SpellChecking );
};

}; // Syntax

#endif // SYNTAXSPELLCHECKING_H
