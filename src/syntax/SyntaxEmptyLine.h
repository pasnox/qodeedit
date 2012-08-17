#ifndef SYNTAXEMPTYLINE_H
#define SYNTAXEMPTYLINE_H

#include <QExplicitlySharedDataPointer>
#include <QString>

#include "SyntaxHelpers.h"

namespace Syntax {

class EmptyLineData;

class EmptyLine
{
private:
    QExplicitlySharedDataPointer<Syntax::EmptyLineData> d;
    
public:
    typedef QList<Syntax::EmptyLine> List;
    
    // Required
    SYNTAX_DECL_MEMBER( QString, regExpr );
    // Optional
    SYNTAX_DECL_MEMBER( bool, caseSensitive );
    
    EmptyLine();
    EmptyLine( const Syntax::EmptyLine& other );
    virtual ~EmptyLine();
    
    SYNTAX_DECL_OPERATORS( EmptyLine );
};

}; // Syntax

#endif // SYNTAXEMPTYLINE_H
