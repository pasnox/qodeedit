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
    
    QE_DECL_SHARED_CLASS( Comment );
    
    // Required
    QE_DECL_MEMBER( QString, name ); ///< Name of the item data
    QE_DECL_MEMBER( QString, start ); ///< Comment start string
    // Optional
    QE_DECL_MEMBER( QString, end ); ///< Comment end string
    QE_DECL_MEMBER( QString, region ); ///< ?
    QE_DECL_MEMBER( QString, position ); // enum: afterwhitespace
};

}; // Syntax

#endif // SYNTAXCOMMENT_H
