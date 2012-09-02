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
    QE_DECL_SHARED_CLASS( Indentation );
    
    // Required
    // Optional
    QE_DECL_MEMBER( QString, mode );
};

}; // Syntax

#endif // SYNTAXINDENTATION_H
