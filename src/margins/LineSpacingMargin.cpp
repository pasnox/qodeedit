#include "LineSpacingMargin.h"
#include "CodeEditor.h"

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
