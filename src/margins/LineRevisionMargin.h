/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : LineRevisionMargin.h
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#ifndef LINEREVISIONMARGIN_H
#define LINEREVISIONMARGIN_H

#include "AbstractMargin.h"

class LineRevisionMargin : public AbstractMargin
{
    Q_OBJECT
    
public:
    LineRevisionMargin( MarginStacker* marginStacker );
    virtual ~LineRevisionMargin();

protected:
    virtual void paintEvent( QPaintEvent* event );
    virtual void setEditor( CodeEditor* editor );

protected slots:
    virtual void updateWidthRequested();
};

#endif // LINEREVISIONMARGIN_H
