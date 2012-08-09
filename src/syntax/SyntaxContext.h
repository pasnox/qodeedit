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
    
    QString& name; ///< Name of the context
    QString& attribute;
    QString& lineEndContext;
    bool& fallThrough;
    QString& fallThroughContext;
    bool& dynamic;
    bool& noIndentationBasedFolding;
    bool& caseSensitive;
    Syntax::Rule::List& rules; ///< Rules of the context
    
    Context();
    Context( const Syntax::Context& other );
    virtual ~Context();
    
    SYNTAX_OPERATORS( Context )
    virtual Syntax::Context& operator=( const Syntax::Context& other );
};

}; // Syntax

#endif // SYNTAXCONTEXT_H
