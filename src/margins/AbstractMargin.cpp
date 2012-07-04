#include "AbstractMargin.h"
#include "QodeEdit.h"

#include <QTextBlock>

// AbstractMarginPrivate

class AbstractMarginPrivate {
public:
    AbstractMarginPrivate( AbstractMargin* _margin, QodeEdit* _editor )
        : margin( _margin ), editor( _editor ), line( -1 ), linePressed( -1 )
    {
        Q_ASSERT( margin );
        Q_ASSERT( editor );
    }
    
    int lineAt( const QPoint& pos ) const {
        return editor->cursorForPosition( pos ).blockNumber();
    }
    
    QRect lineRect( int line ) const {
        QRect rect = editor->document()->findBlockByNumber( line ).layout()->boundingRect().toRect();
        rect.setWidth( margin->width() );
        return rect;
    }

public:
    AbstractMargin* margin;
    QodeEdit* editor;
    int line;
    int linePressed;
};

// AbstractMargin

AbstractMargin::AbstractMargin( QodeEdit* editor )
    : QWidget( editor ),
        d( new AbstractMarginPrivate( this, editor ) )
{
    setMouseTracking( true );
}

AbstractMargin::~AbstractMargin()
{
}

int AbstractMargin::lineAt( const QPoint& pos ) const
{
    return d->lineAt( pos );
}

QRect AbstractMargin::lineRect( int line ) const
{
    return d->lineRect( line );
}

void AbstractMargin::mousePressEvent( QMouseEvent* event )
{
    QWidget::mousePressEvent( event );
    d->linePressed = d->lineAt( event->pos() );
}

void AbstractMargin::mouseDoubleClickEvent( QMouseEvent* event )
{
    QWidget::mouseDoubleClickEvent( event );
    
    if ( d->line != -1 ) {
        emit doubleClicked( d->line, event->button(), event->buttons(), event->modifiers() );
    }
}

void AbstractMargin::mouseReleaseEvent( QMouseEvent* event )
{
    QWidget::mouseReleaseEvent( event );
    
    if ( d->linePressed != -1 && d->linePressed == d->lineAt( event->pos() ) ) {
        emit clicked( d->line, event->button(), event->buttons(), event->modifiers() );
    }
    
    d->linePressed = -1;
}

void AbstractMargin::mouseMoveEvent( QMouseEvent* event )
{
    QWidget::mouseMoveEvent( event );
    
    const int line = d->lineAt( event->pos() );
    
    if ( line == d->line ) {
        return;
    }
    
    if ( d->line != -1 ) {
        emit left( d->line );
    }
    
    d->line = line;
    
    if ( d->line != -1 ) {
        emit entered( d->line );
    }
}


void AbstractMargin::enterEvent( QEvent* event )
{
    QWidget::enterEvent( event );
}

void AbstractMargin::leaveEvent( QEvent* event )
{
    QWidget::leaveEvent( event );
}
