/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : Comment.h
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#ifndef COMMENT_H
#define COMMENT_H

#include <QExplicitlySharedDataPointer>
#include <QList>
#include <QString>

#include "Helpers.h"

namespace Syntax {

class CommentData;

class Comment
{
private:
    QExplicitlySharedDataPointer<Syntax::CommentData> d;

public:
    typedef QList<Syntax::Comment> List;

    QE_DECL_SHARED_CLASS( Comment, Syntax );

    // Required
    QE_DECL_MEMBER( QString, name ); ///< Name of the item data
    QE_DECL_MEMBER( QString, start ); ///< Comment start string
    // Optional
    QE_DECL_MEMBER( QString, end ); ///< Comment end string
    QE_DECL_MEMBER( QString, region ); ///< ?
    QE_DECL_MEMBER( QString, position ); // enum: afterwhitespace
};

} // Syntax

#endif // COMMENT_H
