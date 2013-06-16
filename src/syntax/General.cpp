/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : General.cpp
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#include "General.h"

class Syntax::GeneralData : public QSharedData
{
public:
    Syntax::Comment::List comments;
    Syntax::Keywords keywords;
    Syntax::Folding folding;
    Syntax::Indentation indentation;
    Syntax::EmptyLine::List emptyLines;

    GeneralData()
        : QSharedData()
    {
    }

    GeneralData( const Syntax::GeneralData& other )
        : QSharedData( other ),
            QE_OTHER_INIT( comments ),
            QE_OTHER_INIT( keywords ),
            QE_OTHER_INIT( folding ),
            QE_OTHER_INIT( indentation ),
            QE_OTHER_INIT( emptyLines )
    {
    }

    virtual ~GeneralData() {
    }
};

QE_IMPL_SHARED_CLASS( General, Syntax )

Syntax::General::~General()
{
}

QE_IMPL_MEMBER( Syntax::Comment::List, comments, General, Syntax )
QE_IMPL_MEMBER( Syntax::Keywords, keywords, General, Syntax )
QE_IMPL_MEMBER( Syntax::Folding, folding, General, Syntax )
QE_IMPL_MEMBER( Syntax::Indentation, indentation, General, Syntax )
QE_IMPL_MEMBER( Syntax::EmptyLine::List, emptyLines, General, Syntax )
