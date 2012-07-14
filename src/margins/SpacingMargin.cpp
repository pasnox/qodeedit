#include "SpacingMargin.h"
#include "QodeEdit.h"

#include <QPainter>

SpacingMargin::SpacingMargin( MarginStacker* marginStacker )
    : AbstractMargin( marginStacker )
{
    setMinimumWidth( 2 );
    setMouseTracking( false );
}

SpacingMargin::~SpacingMargin()
{
}

void SpacingMargin::paintEvent( QPaintEvent* event )
{
    QWidget::paintEvent( event );
    
    const QodeEdit* editor = this->editor();
    const QColor color = editor ? editor->palette().color( editor->viewport()->backgroundRole() ) : palette().color( backgroundRole() );
    QPainter painter( this );
    painter.setRenderHint( QPainter::Antialiasing, false );
    painter.fillRect( event->rect(), color );
}

void SpacingMargin::updateWidthRequested()
{
}
