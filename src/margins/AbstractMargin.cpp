#include "AbstractMargin.h"
#include "QodeEdit.h"

#include <QTextBlock>
#include <QScrollBar>
#include <QApplication>
#include <QDebug>

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
        const QTextBlock block = editor->document()->findBlockByNumber( line );
        QRect rect = editor->blockBoundingGeometry( block ).toRect();
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
    connect( editor->document()->documentLayout(), SIGNAL( update( const QRectF& ) ), this, SLOT( update() ) );
	connect( editor->verticalScrollBar(), SIGNAL( valueChanged( int ) ), this, SLOT( update() ) );
	connect( editor, SIGNAL( blockCountChanged( int ) ), this, SLOT( update() ) );
    connect( editor, SIGNAL( blockCountChanged( int ) ), this, SIGNAL( countChanged( int ) ) );
}

AbstractMargin::~AbstractMargin()
{
}

QodeEdit* AbstractMargin::editor() const
{
    return d->editor;
}

int AbstractMargin::lineAt( const QPoint& pos ) const
{
    return d->lineAt( pos );
}

QRect AbstractMargin::lineRect( int line ) const
{
    return d->lineRect( line );
}

int AbstractMargin::firstVisibleLine() const
{
    return d->lineAt( d->editor->viewport()->rect().topLeft() );
}

int AbstractMargin::lastVisibleLine() const
{
    return d->lineAt( d->editor->viewport()->rect().bottomLeft() );
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
    
    const QPoint pos = QCursor::pos();
    QMouseEvent me( QEvent::MouseMove, mapFromGlobal( pos ), pos, Qt::NoButton, QApplication::mouseButtons(), QApplication::keyboardModifiers() );
    
    mouseMoveEvent( &me );
}

void AbstractMargin::leaveEvent( QEvent* event )
{
    QWidget::leaveEvent( event );
    
    const int line = -1;
    
    if ( line == d->line ) {
        return;
    }
    
    if ( d->line != -1 ) {
        emit left( d->line );
    }
    
    d->line = line;
}
