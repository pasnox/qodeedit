/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : LineRevisionMargin.cpp
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#include "LineRevisionMargin.h"
#include "editor/CodeEditor.h"
#include "editor/TextDocument.h"

#include <QPainter>
#include <QTextBlock>
#include <QDebug>

LineRevisionMargin::LineRevisionMargin( MarginStacker* marginStacker )
    : AbstractMargin( marginStacker )
{
    updateWidthRequested();
    setMouseTracking( false );
}

LineRevisionMargin::~LineRevisionMargin()
{
}

void LineRevisionMargin::setEditor( CodeEditor* editor )
{
    CodeEditor* oldEditor = this->editor();
    
    if ( oldEditor ) {
        disconnect( oldEditor->textDocument(), SIGNAL( contentsChanged() ), this, SLOT( update() ) );
        disconnect( oldEditor->textDocument(), SIGNAL( modificationChanged( bool ) ), this, SLOT( update() ) );
    }
    
    AbstractMargin::setEditor( editor );
    
    if ( editor ) {
        connect( editor->textDocument(), SIGNAL( contentsChanged() ), this, SLOT( update() ) );
        connect( editor->textDocument(), SIGNAL( modificationChanged( bool ) ), this, SLOT( update() ) );
    }
}

void LineRevisionMargin::paintEvent( QPaintEvent* event )
{
    AbstractMargin::paintEvent( event );
    
    QPainter painter( this );
    painter.setRenderHint( QPainter::Antialiasing, false );
    painter.setBrush( Qt::NoBrush );
    
    const int firstLine = firstVisibleLine( event->rect() );
    const int lastLine = lastVisibleLine( event->rect() );
    const TextDocument* document = editor()->textDocument();
    
    for ( QTextBlock block = document->findBlockByNumber( firstLine ); block.isValid() && block.blockNumber() <= lastLine; block = block.next() ) {
        const QRect rect = blockRect( block );
        
        if ( block.revision() != document->lastUnmodifiedRevision() ) {
            if ( block.revision() < 0 ) {
                painter.setPen( QPen( QColor( Qt::darkGreen ), minimumWidth() ) );
            }
            else {
                painter.setPen( QPen( QColor( Qt::red ), minimumWidth() ) );
            }
            
            painter.drawLine( rect.topRight(), rect.bottomRight() );
        }
    }
}

void LineRevisionMargin::updateWidthRequested()
{
    setMinimumWidth( 2 );
}
