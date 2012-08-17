#ifndef SYNTAXINDENTATION_H
#define SYNTAXINDENTATION_H

#include <QExplicitlySharedDataPointer>
#include <QString>

#include "SyntaxHelpers.h"

namespace Syntax {

class IndentationData;

class Indentation
{
private:
    QExplicitlySharedDataPointer<Syntax::IndentationData> d;
    
public:
    // Required
    // Optional
    SYNTAX_DECL_MEMBER( QString, mode );
    
    Indentation();
    Indentation( const Syntax::Indentation& other );
    virtual ~Indentation();
    
    SYNTAX_DECL_OPERATORS( Indentation );
};

}; // Syntax

#endif // SYNTAXINDENTATION_H
