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
    
    QString& name; ///< Name of the item data
    QString& start; ///< Comment start string
    QString& end; ///< Comment end string
    QString& region; ///< ?
    QString& weakDeliminator;
    QString& position;
    
    Comment();
    Comment( const Syntax::Comment& other );
    virtual ~Comment();
    
    SYNTAX_OPERATORS( Comment )
    virtual Syntax::Comment& operator=( const Syntax::Comment& other );
};

}; // Syntax

#endif // SYNTAXCOMMENT_H
