/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : Indentation.cpp
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#include "Indentation.h"

class Syntax::IndentationData : public QSharedData
{
public:
    QString mode;

    IndentationData()
        : QSharedData()
    {
    }

    IndentationData( const Syntax::IndentationData& other )
        : QSharedData( other ),
            QE_OTHER_INIT( mode )
    {
    }

    virtual ~IndentationData() {
    }
};

QE_IMPL_SHARED_CLASS( Indentation, Syntax )

Syntax::Indentation::~Indentation()
{
}

QE_IMPL_MEMBER( QString, mode, Indentation, Syntax )
