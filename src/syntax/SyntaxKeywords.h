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
    QE_DECL_SHARED_CLASS( Keywords );
    
    // Required
    // Optional
    QE_DECL_MEMBER( bool, caseSensitive );
    QE_DECL_MEMBER( QString, weakDeliminator );
    QE_DECL_MEMBER( QString, additionalDeliminator );
    QE_DECL_MEMBER( QString, wordWrapDeliminator );
};

}; // Syntax

#endif // SYNTAXKEYWORDS_H
