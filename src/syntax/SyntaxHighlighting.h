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
    SYNTAX_DECL_MEMBER( Syntax::HashList, lists );
    SYNTAX_DECL_MEMBER( Syntax::Context::Hash, contexts );
    SYNTAX_DECL_MEMBER( Syntax::ItemData::Hash, itemDatas );
    // Others
    SYNTAX_DECL_MEMBER( QString, defaultContext );
    
    Highlighting();
    Highlighting( const Syntax::Highlighting& other );
    virtual ~Highlighting();
    
    SYNTAX_DECL_OPERATORS( Highlighting );
    
    Syntax::List list( const QString& name ) const;
};

}; // Syntax

#endif // SYNTAXHIGHLIGHTING_H
