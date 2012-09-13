/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : AbstractMargin.cpp
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#include "AbstractMargin.h"
#include "MarginStacker.h"
#include "editor/CodeEditor.h"
#include "editor/TextDocument.h"
#include "editor/PlainTextDocumentLayout.h"
#include "editor/TextBlockUserData.h"

#include <QScrollBar>
#include <QApplication>
#include <QDebug>

// AbstractMarginPrivate

class AbstractMarginPrivate {
public:
    AbstractMargin* margin;
    MarginStacker* stacker;
    int line;
    int linePressed;
    
    AbstractMarginPrivate( AbstractMargin* _margin, MarginStacker* marginStacker )
        : margin( _margin ), stacker( marginStacker ),
            line( -1 ), linePressed( -1 )
    {
        Q_ASSERT( margin );
        Q_ASSERT( marginStacker );
    }
    
    int lineAt( const QPoint& pos ) const {
        const CodeEditor* editor = stacker->editor();
        return editor ? editor->cursorForPosition( pos ).blockNumber() : -1;
    }
    
    QRect blockRect( const QTextBlock& block ) const {
        const CodeEditor* editor = stacker->editor();
        QRect rect;
        
        if ( editor ) {
            rect = editor->blockRect( block );
            rect.setWidth( margin->width() );
        }
        
        return rect;
    }
    
    QRect lineRect( int line ) const {
        const CodeEditor* editor = stacker->editor();
        const TextDocument* document = editor ? editor->textDocument() : 0;
        return document ? blockRect( document->findBlockByNumber( line ) ) : QRect();
    }
};

// AbstractMargin

AbstractMargin::AbstractMargin( MarginStacker* marginStacker )
    : QWidget( 0 ),
        d( new AbstractMarginPrivate( this, marginStacker ) )
{
    Q_ASSERT( marginStacker );
    
    setMouseTracking( true );
}

AbstractMargin::~AbstractMargin()
{
    delete d;
}

CodeEditor* AbstractMargin::editor() const
{
    return d->stacker->editor();
}

void AbstractMargin::setEditor( CodeEditor* editor )
{
    CodeEditor* oldEditor = this->editor();
    
    if ( oldEditor ) {
        disconnect( oldEditor->textDocument()->layout(), SIGNAL( update( const QRectF& ) ), this, SLOT( update() ) );
        disconnect( oldEditor, SIGNAL( cursorPositionChanged() ), this, SLOT( update() ) );
        disconnect( oldEditor->verticalScrollBar(), SIGNAL( valueChanged( int ) ), this, SLOT( update() ) );
        disconnect( oldEditor, SIGNAL( blockCountChanged( int ) ), this, SLOT( update() ) );
        disconnect( oldEditor, SIGNAL( blockCountChanged( int ) ), this, SIGNAL( lineCountChanged( int ) ) );
    }
    
    if ( editor ) {
        connect( editor->textDocument()->layout(), SIGNAL( update( const QRectF& ) ), this, SLOT( update() ) );
        connect( editor, SIGNAL( cursorPositionChanged() ), this, SLOT( update() ) );
        connect( editor->verticalScrollBar(), SIGNAL( valueChanged( int ) ), this, SLOT( update() ) );
        connect( editor, SIGNAL( blockCountChanged( int ) ), this, SLOT( update() ) );
        connect( editor, SIGNAL( blockCountChanged( int ) ), this, SIGNAL( lineCountChanged( int ) ) );
    }
    
    updateWidthRequested();
}

MarginStacker* AbstractMargin::stacker() const
{
    return d->stacker;
}

int AbstractMargin::lineAt( const QPoint& pos ) const
{
    return d->lineAt( pos );
}

QRect AbstractMargin::blockRect( const QTextBlock& block ) const
{
    return d->blockRect( block );
}

QRect AbstractMargin::lineRect( int line ) const
{
    return d->lineRect( line );
}

int AbstractMargin::firstVisibleLine( const QRect& rect ) const
{
    const CodeEditor* editor = this->editor();
    const QRect r = rect.isNull() ? ( editor ? editor->viewport()->rect() : rect ) : rect;
    return d->lineAt( r.topLeft() );
}

int AbstractMargin::lastVisibleLine( const QRect& rect ) const
{
    const CodeEditor* editor = this->editor();
    const QRect r = rect.isNull() ? ( editor ? editor->viewport()->rect() : rect ) : rect;
    return d->lineAt( r.bottomLeft() );
}

void AbstractMargin::updateLineRect( int line )
{
    update( lineRect( line ) );
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
        emit mouseDoubleClicked( d->line, event->button(), event->buttons(), event->modifiers() );
    }
}

void AbstractMargin::mouseReleaseEvent( QMouseEvent* event )
{
    QWidget::mouseReleaseEvent( event );
    
    if ( d->linePressed != -1 && d->linePressed == d->lineAt( event->pos() ) ) {
        emit mouseClicked( d->line, event->button(), event->buttons(), event->modifiers() );
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
        emit mouseLeft( d->line );
    }
    
    d->line = line;
    
    if ( d->line != -1 ) {
        emit mouseEntered( d->line );
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
        emit mouseLeft( d->line );
    }
    
    d->line = line;
}
