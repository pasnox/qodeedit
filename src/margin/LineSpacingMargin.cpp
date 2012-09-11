/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : LineSpacingMargin.cpp
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#include "LineSpacingMargin.h"
#include "editor/CodeEditor.h"

#include <QPainter>

LineSpacingMargin::LineSpacingMargin( MarginStacker* marginStacker )
    : AbstractMargin( marginStacker )
{
    updateWidthRequested();
    setMouseTracking( false );
}

LineSpacingMargin::~LineSpacingMargin()
{
}

void LineSpacingMargin::paintEvent( QPaintEvent* event )
{
    QWidget::paintEvent( event );
    
    const CodeEditor* editor = this->editor();
    const QColor color = editor ? editor->palette().color( editor->viewport()->backgroundRole() ) : palette().color( backgroundRole() );
    QPainter painter( this );
    painter.setRenderHint( QPainter::Antialiasing, false );
    painter.fillRect( event->rect(), color );
}

void LineSpacingMargin::updateWidthRequested()
{
    setMinimumWidth( 2 );
}
