#include "QodeEdit.h"
#include "QodeEditTextDocument.h"
#include "MarginStacker.h"

#include <QStyleOptionFrameV3>
#include <QTextBlock>
#include <QPainter>

// QodeEdit::Private

class QodeEdit::Private
{
public:
    Private( QodeEdit* _editor )
            : editor( _editor ),
            stacker( 0 ),
            originalPalette( _editor->palette() ),
            rulerMode( QodeEdit::NoRuler ),
            rulerWidth( 80 )
    {
    }
    
    QodeEdit* editor;
    MarginStacker* stacker;
    QPalette originalPalette;
    QodeEdit::Ruler rulerMode;
    int rulerWidth;

    QLine rulerLine() const
    {
        const QPoint offset = editor->contentOffset().toPoint();
        const int x = rulerWidth *QFontMetrics( editor->font() ).averageCharWidth();
        return QLine( QPoint( x +offset.x(), 0 ), QPoint( x +offset.x(), editor->viewport()->height() ) );
    }
    
    QRect rulerRect() const
    {
        const QPoint offset = editor->contentOffset().toPoint();
        const int x = rulerWidth *QFontMetrics( editor->font() ).averageCharWidth();
        QRect rect( QPoint( x +offset.x(), 0 ), QSize( editor->viewport()->size() -QSize( x +offset.x(), 0 ) ) );
        return rect;
    }
    
    QRect caretLineRect() const
    {
        QRect rect = editor->cursorRect().adjusted( 0, -1, 0, 1 );
        rect.setX( 0 );
        rect.setWidth( editor->viewport()->width() );
        return rect;
    }
    
    void paintFrame()
    {
        QPainter painter( editor );
        QStyleOptionFrameV3 option;
        
        option.initFrom( editor );
        option.palette = originalPalette;
        option.rect = editor->frameRect();
        option.frameShape = editor->frameShape();
        
        switch ( option.frameShape ) {
            case QFrame::Box:
            case QFrame::HLine:
            case QFrame::VLine:
            case QFrame::StyledPanel:
            case QFrame::Panel:
                option.lineWidth = editor->lineWidth();
                option.midLineWidth = editor->midLineWidth();
                break;
            default:
                // most frame styles do not handle customized line and midline widths
                // (see updateFrameWidth()).
                option.lineWidth = editor->frameWidth();
                break;
        }

        if ( editor->frameShadow() == QFrame::Sunken ) {
            option.state |= QStyle::State_Sunken;
        }
        else if ( editor->frameShadow() == QFrame::Raised ) {
            option.state |= QStyle::State_Raised;
        }

        editor->style()->drawControl( QStyle::CE_ShapedFrame, &option, &painter, editor );
    }
};

// QodeEdit

QodeEdit::QodeEdit( QWidget* parent )
    : QPlainTextEdit( parent ),
        d( new QodeEdit::Private( this ) )
{
    setAutoFillBackground( true );
    setCaretLineBackground( caretLineBackground().color().lighter( 200 ) );
    setDocument( new QodeEditTextDocument( this ) );
    
    connect( this, SIGNAL( cursorPositionChanged() ), viewport(), SLOT( update() ) );
}

QodeEdit::~QodeEdit()
{
    delete d;
}

MarginStacker* QodeEdit::marginStacker() const
{
    return d->stacker;
}

void QodeEdit::setMarginStacker( MarginStacker* marginStacker )
{
    if ( d->stacker == marginStacker ) {
        return;
    }
    
    if ( d->stacker ) {
        d->stacker->deleteLater();
    }
    
    d->stacker = marginStacker;
    
    if ( d->stacker ) {
        d->stacker->setEditor( this );
    }
}

QPoint QodeEdit::cursorPosition() const
{
    const QTextCursor cursor = textCursor();
    return cursor.isNull() ? QPoint() : QPoint( cursor.positionInBlock(), cursor.blockNumber() );
}

void QodeEdit::setCursorPosition( const QPoint& pos )
{
    const QTextBlock block = document()->findBlockByLineNumber( pos.y() );
    const int position = block.position() +( pos.x() < block.length() ? pos.x() : 0 );
    QTextCursor cursor = textCursor();
    cursor.setPosition( position, QTextCursor::MoveAnchor );
    setTextCursor( cursor );
}

int QodeEdit::currentLine() const
{
    return cursorPosition().y();
}

void QodeEdit::setCurrentLine( int line )
{
    setCursorPosition( QPoint( currentColumn(), line ) );
}

int QodeEdit::currentColumn() const
{
    return cursorPosition().x();
}

void QodeEdit::setCurrentColumn( int column )
{
    setCursorPosition( QPoint( column, currentLine() ) );
}

QodeEdit::Ruler QodeEdit::rulerMode() const
{
    return d->rulerMode;
}

void QodeEdit::setRulerMode( QodeEdit::Ruler mode )
{
    d->rulerMode = mode;
    viewport()->update();
}

int QodeEdit::rulerWidth() const
{
    return d->rulerWidth;
}

void QodeEdit::setRulerWidth( int width )
{
    d->rulerWidth = width;
    viewport()->update();
}

QBrush QodeEdit::paper() const
{
    return palette().brush( viewport()->backgroundRole() );
}

void QodeEdit::setPaper( const QBrush& brush )
{
    QPalette pal = palette();
    pal.setBrush( viewport()->backgroundRole(), brush );
    setPalette( pal );
}

QBrush QodeEdit::pen() const
{
    return palette().brush( viewport()->foregroundRole() );
}

void QodeEdit::setPen( const QBrush& brush )
{
    QPalette pal = palette();
    pal.setBrush( viewport()->foregroundRole(), brush );
    setPalette( pal );
}

QBrush QodeEdit::selectionBackground() const
{
    return palette().brush( QPalette::Highlight );
}

void QodeEdit::setSelectionBackground( const QBrush& brush )
{
    QPalette pal = palette();
    pal.setBrush( QPalette::Highlight, brush );
    setPalette( pal );
}

QBrush QodeEdit::selectionForeground() const
{
    return palette().brush( QPalette::HighlightedText );
}

void QodeEdit::setSelectionForeground( const QBrush& brush )
{
    QPalette pal = palette();
    pal.setBrush( QPalette::HighlightedText, brush );
    setPalette( pal );
}

QBrush QodeEdit::caretLineBackground() const
{
    return palette().brush( QPalette::Link );
}

void QodeEdit::setCaretLineBackground( const QBrush& brush )
{
    QPalette pal = palette();
    pal.setBrush( QPalette::Link, brush );
    setPalette( pal );
}

QBrush QodeEdit::caretLineForeground() const
{
    return palette().brush( QPalette::LinkVisited );
}

void QodeEdit::setCaretLineForeground( const QBrush& brush )
{
    QPalette pal = palette();
    pal.setBrush( QPalette::LinkVisited, brush );
    setPalette( pal );
}

QRect QodeEdit::lineRect( int line ) const
{
    const QTextBlock block = document()->findBlockByNumber( line );
    QRectF rect = blockBoundingGeometry( block );
    rect.moveTopLeft( rect.topLeft() +QPointF( 0, contentOffset().y() ) );
    return rect.toRect();
}

bool QodeEdit::event( QEvent* event )
{
    switch ( event->type() ) {
        case QEvent::QEvent::Paint:
            d->paintFrame();
            return true;
        default:
            break;
    }
    
    return QPlainTextEdit::event( event );
}

void QodeEdit::paintEvent( QPaintEvent* event )
{
    QPainter painter( viewport() );
    
    // draw ruler
    switch ( d->rulerMode ) {
        case QodeEdit::NoRuler:
            break;
        case QodeEdit::LineRuler:
            painter.setPen( QPen( caretLineForeground(), painter.pen().widthF() ) );
            painter.drawLine( d->rulerLine() );
            break;
        case QodeEdit::BackgroundRuler:
            painter.setPen( Qt::NoPen );
            painter.setBrush( caretLineForeground() );
            painter.drawRect( d->rulerRect() );
            break;
    }
    
    // draw caret line
    painter.fillRect( d->caretLineRect(), caretLineBackground() );
    
    // finished
    painter.end();
    
    // normal editor painting
    QPlainTextEdit::paintEvent( event );
}
