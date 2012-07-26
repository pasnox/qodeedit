#ifndef SYNTAXCOMMENT_H
#define SYNTAXCOMMENT_H

#include <QHash>
#include <QString>

namespace Syntax {

class Comment
{
public:
    typedef QHash<QString, Syntax::Comment> Hash;
    
    QString name; ///< Name of the item data
    QString start; ///< Comment start string
    QString end; ///< Comment end string
    QString region; ///< ?
    QString weakDeliminator;
    
    Comment();
    virtual ~Comment();
};

}; // Syntax

#endif // SYNTAXCOMMENT_H
