#ifndef SYNTAXHIGHLIGHTING_H
#define SYNTAXHIGHLIGHTING_H

#include "SyntaxList.h"
#include "SyntaxContext.h"
#include "SyntaxItemData.h"

namespace Syntax {

class Highlighting
{
public:
    typedef QHash<QString, Syntax::List> ListHash;
    
    Syntax::Highlighting::ListHash lists;
    Syntax::Context::Hash contexts;
    Syntax::ItemData::Hash itemDatas;
    
    Highlighting();
    virtual ~Highlighting();
    
    Syntax::List list( const QString& name ) const;
};

}; // Syntax

#endif // SYNTAXHIGHLIGHTING_H
