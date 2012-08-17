#ifndef SYNTAXKEYWORDS_H
#define SYNTAXKEYWORDS_H

#include <QExplicitlySharedDataPointer>
#include <QString>

#include "SyntaxHelpers.h"

namespace Syntax {

class KeywordsData;

class Keywords
{
private:
    QExplicitlySharedDataPointer<Syntax::KeywordsData> d;
    
public:
    // Required
    // Optional
    SYNTAX_DECL_MEMBER( bool, caseSensitive );
    SYNTAX_DECL_MEMBER( QString, weakDeliminator );
    SYNTAX_DECL_MEMBER( QString, additionalDeliminator );
    SYNTAX_DECL_MEMBER( QString, wordWrapDeliminator );
    
    Keywords();
    Keywords( const Syntax::Keywords& other );
    virtual ~Keywords();
    
    SYNTAX_DECL_OPERATORS( Keywords );
};

}; // Syntax

#endif // SYNTAXKEYWORDS_H
