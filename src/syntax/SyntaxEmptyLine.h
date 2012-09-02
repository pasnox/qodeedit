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
    
    QE_DECL_SHARED_CLASS( EmptyLine );
    
    // Required
    QE_DECL_MEMBER( QString, regExpr );
    // Optional
    QE_DECL_MEMBER( bool, caseSensitive );
};

}; // Syntax

#endif // SYNTAXEMPTYLINE_H
