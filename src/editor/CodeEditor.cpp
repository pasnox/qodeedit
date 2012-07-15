#include "CodeEditor.h"
#include "TextDocument.h"
#include "MarginStacker.h"

#include <QStyleOptionFrameV3>
#include <QTextBlock>
#include <QPainter>
#include <QDebug>

// CodeEditorPrivate

class CodeEditorPrivate {
public:
    CodeEditor* editor;
    MarginStacker* stacker;
    QPalette originalPalette;
    CodeEditor::Ruler rulerMode;
    int rulerWidth;
    
    CodeEditorPrivate( CodeEditor* _editor )
            : editor( _editor ),
            stacker( 0 ),
            originalPalette( _editor->palette() ),
            rulerMode( CodeEditor::NoRuler ),
            rulerWidth( 80 )
    {
        Q_ASSERT( editor );
    }

    QLine rulerLine() const {
        const QPoint offset = editor->contentOffset().toPoint();
        const int x = rulerWidth *QFontMetrics( editor->font() ).averageCharWidth();
        return QLine( QPoint( x +offset.x(), 0 ), QPoint( x +offset.x(), editor->viewport()->height() ) );
    }
    
    QRect rulerRect() const {
        const QPoint offset = editor->contentOffset().toPoint();
        const int x = rulerWidth *QFontMetrics( editor->font() ).averageCharWidth();
        QRect rect( QPoint( x +offset.x(), 0 ), QSize( editor->viewport()->size() -QSize( x +offset.x(), 0 ) ) );
        return rect;
    }
    
    QRect caretLineRect() const {
        QRect rect = editor->cursorRect().adjusted( 0, -1, 0, 1 );
        rect.setX( 0 );
        rect.setWidth( editor->viewport()->width() );
        return rect;
    }
    
    void paintFrame() {
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

// CodeEditor

CodeEditor::CodeEditor( QWidget* parent )
    : QPlainTextEdit( parent ),
        d( new CodeEditorPrivate( this ) )
{
    setTextDocument( new TextDocument( this ) );
    setAutoFillBackground( true );
    setCaretLineBackground( caretLineBackground().color().lighter( 200 ) );
    
    connect( this, SIGNAL( cursorPositionChanged() ), viewport(), SLOT( update() ) );
}

CodeEditor::~CodeEditor()
{
    delete d;
}

TextDocument* CodeEditor::textDocument() const
{
    return qobject_cast<TextDocument*>( document() );
}

void CodeEditor::setTextDocument( TextDocument* document )
{
    setDocument( document );
}

MarginStacker* CodeEditor::marginStacker() const
{
    return d->stacker;
}

void CodeEditor::setMarginStacker( MarginStacker* marginStacker )
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

QString CodeEditor::text() const
{
    return textDocument()->text();
}

void CodeEditor::setText( const QString& text )
{
    textDocument()->setText( text );
    moveCursor( QTextCursor::Start, QTextCursor::MoveAnchor );
}

void CodeEditor::setInitialText( const QString& text )
{
    textDocument()->setInitialText( text );
    moveCursor( QTextCursor::Start, QTextCursor::MoveAnchor );
}

QPoint CodeEditor::cursorPosition() const
{
    const QTextCursor cursor = textCursor();
    return cursor.isNull() ? QPoint() : QPoint( cursor.positionInBlock(), cursor.blockNumber() );
}

void CodeEditor::setCursorPosition( const QPoint& pos )
{
    const QTextBlock block = textDocument()->findBlockByLineNumber( pos.y() );
    const int position = block.position() +( pos.x() < block.length() ? pos.x() : 0 );
    QTextCursor cursor = textCursor();
    cursor.setPosition( position, QTextCursor::MoveAnchor );
    setTextCursor( cursor );
}

int CodeEditor::currentLine() const
{
    return cursorPosition().y();
}

void CodeEditor::setCurrentLine( int line )
{
    setCursorPosition( QPoint( currentColumn(), line ) );
}

int CodeEditor::currentColumn() const
{
    return cursorPosition().x();
}

void CodeEditor::setCurrentColumn( int column )
{
    setCursorPosition( QPoint( column, currentLine() ) );
}

CodeEditor::Ruler CodeEditor::rulerMode() const
{
    return d->rulerMode;
}

void CodeEditor::setRulerMode( CodeEditor::Ruler mode )
{
    d->rulerMode = mode;
    viewport()->update();
}

int CodeEditor::rulerWidth() const
{
    return d->rulerWidth;
}

void CodeEditor::setRulerWidth( int width )
{
    d->rulerWidth = width;
    viewport()->update();
}

QBrush CodeEditor::paper() const
{
    return palette().brush( viewport()->backgroundRole() );
}

void CodeEditor::setPaper( const QBrush& brush )
{
    QPalette pal = palette();
    pal.setBrush( viewport()->backgroundRole(), brush );
    setPalette( pal );
}

QBrush CodeEditor::pen() const
{
    return palette().brush( viewport()->foregroundRole() );
}

void CodeEditor::setPen( const QBrush& brush )
{
    QPalette pal = palette();
    pal.setBrush( viewport()->foregroundRole(), brush );
    setPalette( pal );
}

QBrush CodeEditor::selectionBackground() const
{
    return palette().brush( QPalette::Highlight );
}

void CodeEditor::setSelectionBackground( const QBrush& brush )
{
    QPalette pal = palette();
    pal.setBrush( QPalette::Highlight, brush );
    setPalette( pal );
}

QBrush CodeEditor::selectionForeground() const
{
    return palette().brush( QPalette::HighlightedText );
}

void CodeEditor::setSelectionForeground( const QBrush& brush )
{
    QPalette pal = palette();
    pal.setBrush( QPalette::HighlightedText, brush );
    setPalette( pal );
}

QBrush CodeEditor::caretLineBackground() const
{
    return palette().brush( QPalette::Link );
}

void CodeEditor::setCaretLineBackground( const QBrush& brush )
{
    QPalette pal = palette();
    pal.setBrush( QPalette::Link, brush );
    setPalette( pal );
}

QBrush CodeEditor::caretLineForeground() const
{
    return palette().brush( QPalette::LinkVisited );
}

void CodeEditor::setCaretLineForeground( const QBrush& brush )
{
    QPalette pal = palette();
    pal.setBrush( QPalette::LinkVisited, brush );
    setPalette( pal );
}

QRect CodeEditor::blockRect( const QTextBlock& block ) const
{
    QRectF rect = blockBoundingGeometry( block );
    rect.moveTopLeft( rect.topLeft() +QPointF( 0, contentOffset().y() ) );
    return rect.toRect();
}

QRect CodeEditor::lineRect( int line ) const
{
    return blockRect( textDocument()->findBlockByNumber( line ) );
}

bool CodeEditor::event( QEvent* event )
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

void CodeEditor::paintEvent( QPaintEvent* event )
{
    QPainter painter( viewport() );
    painter.setRenderHint( QPainter::Antialiasing, false );
    
    // draw ruler
    switch ( d->rulerMode ) {
        case CodeEditor::NoRuler:
            break;
        case CodeEditor::LineRuler:
            painter.setPen( QPen( caretLineForeground(), painter.pen().widthF() ) );
            painter.drawLine( d->rulerLine() );
            break;
        case CodeEditor::BackgroundRuler:
            painter.setPen( Qt::NoPen );
            painter.setBrush( caretLineForeground() );
            painter.drawRect( d->rulerRect() );
            break;
    }
    
    // draw caret line
    painter.fillRect( d->caretLineRect(), caretLineBackground() );
    painter.end();
    
    // normal editor painting
    QPlainTextEdit::paintEvent( event );
}
