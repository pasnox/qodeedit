/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : EmptyLine.cpp
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#include "EmptyLine.h"

class Syntax::EmptyLineData : public QSharedData
{
public:
    QString regExpr;
    bool caseSensitive;

    EmptyLineData()
        : QSharedData(),
            caseSensitive( false )
    {
    }

    EmptyLineData( const Syntax::EmptyLineData& other )
        : QSharedData( other ),
            QE_OTHER_INIT( regExpr ),
            QE_OTHER_INIT( caseSensitive )
    {
    }

    virtual ~EmptyLineData() {
    }
};

QE_IMPL_SHARED_CLASS( EmptyLine, Syntax )

Syntax::EmptyLine::~EmptyLine()
{
}

QE_IMPL_MEMBER( QString, regExpr, EmptyLine, Syntax )
QE_IMPL_MEMBER( bool, caseSensitive, EmptyLine, Syntax )
