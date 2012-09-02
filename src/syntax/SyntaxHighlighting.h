#ifndef SYNTAXHIGHLIGHTING_H
#define SYNTAXHIGHLIGHTING_H

#include <QExplicitlySharedDataPointer>

#include "SyntaxHelpers.h"
#include "SyntaxList.h"
#include "SyntaxContext.h"
#include "SyntaxItemData.h"

namespace Syntax {

class HighlightingData;

class Highlighting
{
private:
    QExplicitlySharedDataPointer<Syntax::HighlightingData> d;
    
public:
    QE_DECL_SHARED_CLASS( Highlighting );
    
    // Required
    // Optional
    QE_DECL_MEMBER( Syntax::HashList, lists );
    QE_DECL_MEMBER( Syntax::Context::Hash, contexts );
    QE_DECL_MEMBER( Syntax::ItemData::Hash, itemDatas );
    // Others
    QE_DECL_MEMBER( QString, defaultContext );
    
    Syntax::List list( const QString& name ) const;
};

}; // Syntax

#endif // SYNTAXHIGHLIGHTING_H
