#ifndef SYNTAXCONTEXT_H
#define SYNTAXCONTEXT_H

#include <QExplicitlySharedDataPointer>
#include <QHash>
#include <QString>

#include "SyntaxHelpers.h"
#include "SyntaxRule.h"

namespace Syntax {

class ContextData;

class Context
{
private:
    QExplicitlySharedDataPointer<Syntax::ContextData> d;
    
public:
    typedef QHash<QString, Syntax::Context> Hash;
    
    QE_DECL_SHARED_CLASS( Context );
    
    // Required
    QE_DECL_MEMBER( QString, attribute );
    QE_DECL_MEMBER( QString, lineEndContext );
    // Optional
    QE_DECL_MEMBER( QString, name ); ///< Name of the context
    QE_DECL_MEMBER( QString, lineBeginContext );
    QE_DECL_MEMBER( bool, fallThrough );
    QE_DECL_MEMBER( QString, fallThroughContext );
    QE_DECL_MEMBER( bool, dynamic );
    QE_DECL_MEMBER( bool, noIndentationBasedFolding );
    // Others
    QE_DECL_MEMBER( Syntax::Rule::List, rules ); ///< Rules of the context
};

}; // Syntax

#endif // SYNTAXCONTEXT_H
