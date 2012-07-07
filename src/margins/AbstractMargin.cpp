#include "AbstractMargin.h"
#include "MarginStacker.h"
#include "QodeEdit.h"

#include <QScrollBar>
#include <QApplication>
#include <QDebug>

// AbstractMargin::Private

class AbstractMargin::Private {
public:
    Private( AbstractMargin* _margin, MarginStacker* marginStacker )
        : margin( _margin ), stacker( marginStacker ),
			line( -1 ), linePressed( -1 )
    {
        Q_ASSERT( margin );
		Q_ASSERT( marginStacker );
    }
    
    int lineAt( const QPoint& pos ) const {
		const QodeEdit* editor = stacker->editor();
        return editor ? editor->cursorForPosition( pos ).blockNumber() : -1;
    }
    
    QRect lineRect( int line ) const {
		const QodeEdit* editor = stacker->editor();
        QRect rect;
		
		if ( editor ) {
			rect = editor->lineRect( line );
			rect.setWidth( margin->width() );
		}
		
        return rect;
    }

public:
    AbstractMargin* margin;
	MarginStacker* stacker;
    int line;
    int linePressed;
};

// AbstractMargin

AbstractMargin::AbstractMargin( MarginStacker* marginStacker )
    : QWidget( 0 ),
        d( new AbstractMargin::Private( this, marginStacker ) )
{
	Q_ASSERT( marginStacker );
	
    setMouseTracking( true );
}

AbstractMargin::~AbstractMargin()
{
	delete d;
}

QodeEdit* AbstractMargin::editor() const
{
	return d->stacker->editor();
}

void AbstractMargin::setEditor( QodeEdit* editor )
{
	QodeEdit* oldEditor = this->editor();
	
	if ( oldEditor ) {
		disconnect( oldEditor->document()->documentLayout(), SIGNAL( update( const QRectF& ) ), this, SLOT( update() ) );
		disconnect( oldEditor->verticalScrollBar(), SIGNAL( valueChanged( int ) ), this, SLOT( update() ) );
		disconnect( oldEditor, SIGNAL( blockCountChanged( int ) ), this, SLOT( update() ) );
		disconnect( oldEditor, SIGNAL( blockCountChanged( int ) ), this, SIGNAL( countChanged( int ) ) );
	}
	
	if ( editor ) {
		connect( editor->document()->documentLayout(), SIGNAL( update( const QRectF& ) ), this, SLOT( update() ) );
		connect( editor->verticalScrollBar(), SIGNAL( valueChanged( int ) ), this, SLOT( update() ) );
		connect( editor, SIGNAL( blockCountChanged( int ) ), this, SLOT( update() ) );
		connect( editor, SIGNAL( blockCountChanged( int ) ), this, SIGNAL( countChanged( int ) ) );
	}
}

MarginStacker* AbstractMargin::stacker() const
{
	return d->stacker;
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
	const QodeEdit* editor = this->editor();
    return editor ? d->lineAt( editor->viewport()->rect().topLeft() ) : -1;
}

int AbstractMargin::lastVisibleLine() const
{
	const QodeEdit* editor = this->editor();
    return editor ? d->lineAt( editor->viewport()->rect().bottomLeft() ) : -1;
}

bool AbstractMargin::event( QEvent* event )
{
	const bool result = QWidget::event( event );
	
	switch ( event->type() ) {
		case QEvent::FontChange:
			emit fontChanged();
			break;
		case QEvent::Resize:
			emit resized();
			break;
		default:
			break;
	}
	
	return result;
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
