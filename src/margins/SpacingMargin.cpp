#include "SpacingMargin.h"
#include "QodeEdit.h"

#include <QPainter>

SpacingMargin::SpacingMargin( QodeEdit* editor )
    : AbstractMargin( editor )
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
    QPainter painter( this );
    painter.fillRect( event->rect(), editor()->palette().color( editor()->viewport()->backgroundRole() ) );
}
