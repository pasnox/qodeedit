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
    
    // Required
    SYNTAX_DECL_MEMBER( QString, attribute );
    SYNTAX_DECL_MEMBER( QString, lineEndContext );
    // Optional
    SYNTAX_DECL_MEMBER( QString, name ); ///< Name of the context
    SYNTAX_DECL_MEMBER( QString, lineBeginContext );
    SYNTAX_DECL_MEMBER( bool, fallThrough );
    SYNTAX_DECL_MEMBER( QString, fallThroughContext );
    SYNTAX_DECL_MEMBER( bool, dynamic );
    SYNTAX_DECL_MEMBER( bool, noIndentationBasedFolding );
    // Others
    SYNTAX_DECL_MEMBER( Syntax::Rule::List, rules ); ///< Rules of the context
    
    Context();
    Context( const Syntax::Context& other );
    virtual ~Context();
    
    SYNTAX_DECL_OPERATORS( Context );
};

}; // Syntax

#endif // SYNTAXCONTEXT_H
