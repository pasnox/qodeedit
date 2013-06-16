/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : Comment.cpp
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#include "Comment.h"

class Syntax::CommentData : public QSharedData
{
public:
    QString name;
    QString start;
    QString end;
    QString region;
    QString position;

    CommentData()
        : QSharedData()
    {
    }

    CommentData( const Syntax::CommentData& other )
        : QSharedData( other ),
            QE_OTHER_INIT( name ),
            QE_OTHER_INIT( start ),
            QE_OTHER_INIT( end ),
            QE_OTHER_INIT( region ),
            QE_OTHER_INIT( position )
    {
    }

    virtual ~CommentData() {
    }
};

QE_IMPL_SHARED_CLASS( Comment, Syntax )

Syntax::Comment::~Comment()
{
}

QE_IMPL_MEMBER( QString, name, Comment, Syntax )
QE_IMPL_MEMBER( QString, start, Comment, Syntax )
QE_IMPL_MEMBER( QString, end, Comment, Syntax )
QE_IMPL_MEMBER( QString, region, Comment, Syntax )
QE_IMPL_MEMBER( QString, position, Comment, Syntax )
