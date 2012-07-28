#ifndef SYNTAXCOMMENT_H
#define SYNTAXCOMMENT_H

#include <QList>
#include <QString>

namespace Syntax {

class Comment
{
public:
    typedef QList<Syntax::Comment> List;
    
    QString name; ///< Name of the item data
    QString start; ///< Comment start string
    QString end; ///< Comment end string
    QString region; ///< ?
    QString weakDeliminator;
    QString position;
    
    Comment();
    virtual ~Comment();
    
    virtual bool operator==( const Syntax::Comment& other ) const;
    virtual bool operator!=( const Syntax::Comment& other ) const;
};

}; // Syntax

#endif // SYNTAXCOMMENT_H
