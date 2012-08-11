#ifndef SYNTAXCOMMENT_H
#define SYNTAXCOMMENT_H

#include <QExplicitlySharedDataPointer>
#include <QList>
#include <QString>

#include "SyntaxHelpers.h"

namespace Syntax {

class CommentData;

class Comment
{
private:
    QExplicitlySharedDataPointer<Syntax::CommentData> d;
    
public:
    typedef QList<Syntax::Comment> List;
    
    SYNTAX_DECL_MEMBER( QString, name ); ///< Name of the item data
    SYNTAX_DECL_MEMBER( QString, start ); ///< Comment start string
    SYNTAX_DECL_MEMBER( QString, end ); ///< Comment end string
    SYNTAX_DECL_MEMBER( QString, region ); ///< ?
    SYNTAX_DECL_MEMBER( QString, weakDeliminator );
    SYNTAX_DECL_MEMBER( QString, position );
    
    Comment();
    Comment( const Syntax::Comment& other );
    virtual ~Comment();
    
    SYNTAX_DECL_OPERATORS( Comment );
};

}; // Syntax

#endif // SYNTAXCOMMENT_H
