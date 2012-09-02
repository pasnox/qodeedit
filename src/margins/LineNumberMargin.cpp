/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : LineNumberMargin.cpp
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#include "LineNumberMargin.h"
#include "CodeEditor.h"
#include "TextDocument.h"

#include <QPainter>
#include <QTextBlock>
#include <QApplication>
#include <QDebug>

#define LineNumberMarginMargins 2

static QMouseEvent transformedMouseEvent( QMouseEvent* event, QWidget* to )
{
    return QMouseEvent(
        event->type(),
        event->type() == QEvent::MouseMove ? QPoint( to->width(), event->pos().y() ) : QPoint( 0, event->pos().y() ),
        to->mapToGlobal( event->pos() ),
        event->button(),
        event->buttons(),
        event->modifiers()
    );
}

static QWheelEvent transformedWheelEvent( QWheelEvent* event, QWidget* to )
{
    return QWheelEvent(
        event->pos(),
        to->mapToGlobal( event->pos() ),
        event->delta(),
        event->buttons(),
        event->modifiers(),
        event->orientation()
    );
}

LineNumberMargin::LineNumberMargin( MarginStacker* marginStacker )
    : AbstractMargin( marginStacker )
{
    updateWidthRequested();
    
    connect( this, SIGNAL( mouseEntered( int ) ), this, SLOT( updateLineRect( int ) ) );
    connect( this, SIGNAL( mouseLeft( int ) ), this, SLOT( updateLineRect( int ) ) );
    connect( this, SIGNAL( fontChanged() ), this, SLOT( updateWidthRequested() ) );
    connect( this, SIGNAL( lineCountChanged( int ) ), this, SLOT( updateWidthRequested() ) );
}

LineNumberMargin::~LineNumberMargin()
{
}

void LineNumberMargin::mousePressEvent( QMouseEvent* event )
{
    QWidget* viewport = editor()->viewport();
    QMouseEvent me = transformedMouseEvent( event, viewport );
    QApplication::sendEvent( viewport, &me );
    AbstractMargin::mousePressEvent( event );
}

void LineNumberMargin::mouseDoubleClickEvent( QMouseEvent* event )
{
    QWidget* viewport = editor()->viewport();
    QMouseEvent me = transformedMouseEvent( event, viewport );
    QApplication::sendEvent( viewport, &me );
    AbstractMargin::mouseDoubleClickEvent( event );
}

void LineNumberMargin::mouseReleaseEvent( QMouseEvent* event )
{
    QWidget* viewport = editor()->viewport();
    QMouseEvent me = transformedMouseEvent( event, viewport );
    QApplication::sendEvent( viewport, &me );
    AbstractMargin::mouseReleaseEvent( event );
}

void LineNumberMargin::mouseMoveEvent( QMouseEvent* event )
{
    if ( !editor()->textCursor().hasSelection() ) {
        QWidget* viewport = editor()->viewport();
        QMouseEvent me = transformedMouseEvent( event, viewport );
        QApplication::sendEvent( viewport, &me );
    }
    
    AbstractMargin::mouseMoveEvent( event );
}

void LineNumberMargin::wheelEvent( QWheelEvent* event )
{
    QWidget* viewport = editor()->viewport();
    QWheelEvent we = transformedWheelEvent( event, viewport );
    QApplication::sendEvent( viewport, &we );
    AbstractMargin::wheelEvent( event );
}

void LineNumberMargin::paintEvent( QPaintEvent* event )
{
    AbstractMargin::paintEvent( event );
    
    QPainter painter( this );
    painter.setRenderHint( QPainter::Antialiasing, false );
    
    const int firstLine = firstVisibleLine( event->rect() );
    const int lastLine = lastVisibleLine( event->rect() );
    const int flags = Qt::AlignVCenter | Qt::AlignRight;
    const int defaultPointSize = editor()->textDocument()->defaultFont().pointSize();
    const QFont painterFont = painter.font();
    const QColor color = palette().color( QPalette::WindowText );
    const QColor lightColor = QColor( color.red(), color.green(), color.blue(), 120 );
    const QPoint cursorPos = editor()->cursorPosition();
    const QPoint mousePos = mapFromGlobal( QCursor::pos() );
    const int mouseLine = rect().contains( mousePos ) ? lineAt( mousePos ) : -1;
    const TextDocument* document = editor()->textDocument();
    
    for ( QTextBlock block = document->findBlockByNumber( firstLine ); block.isValid() && block.blockNumber() <= lastLine; block = block.next() ) {
        const QRect rect = blockRect( block ).adjusted( LineNumberMarginMargins, 0, -LineNumberMarginMargins, 0 );
        const int i = block.blockNumber();
        const bool isCurrentLine = cursorPos.y() == i;
        bool isHoveredLine = mouseLine == i && !isCurrentLine;
        QFont font = painterFont;
        
        if ( !isHoveredLine && ( ( i +1 ) %10 ) == 0 ) {
            isHoveredLine = true;
        }
        
        font.setBold( isCurrentLine || isHoveredLine );
        font.setPointSize( qMin( font.pointSize(), qMax( block.blockFormat().property( QTextFormat::FontPointSize ).toInt(), defaultPointSize ) ) );
        
        painter.setFont( font );
        painter.setPen( isCurrentLine ? color : lightColor );
        painter.drawText( rect, flags, QString::number( i +1 ) );
    }
}

void LineNumberMargin::updateWidthRequested()
{
    const CodeEditor* editor = this->editor();
    const int count = editor ? editor->blockCount() : 0;
    setMinimumWidth( fontMetrics().width( QString::number( count ) ) +( LineNumberMarginMargins *2 ) );
}
