#include "QodeEdit.h"
#include "MarginContainer.h"

#include <QStyleOptionFrameV3>
#include <QPainter>

// QodeEditPrivate

class QodeEditPrivate : QObject
{
    Q_OBJECT

public:
    QodeEditPrivate( QodeEdit* _editor )
        : QObject( _editor ),
            editor( _editor ),
            margins( new MarginContainer( _editor ) ),
            originalPalette( _editor->palette() ),
            rulerMode( QodeEdit::NoRuler ),
            rulerWidth( 80 )
    {
        margins->setVisible( MarginContainer::LineNumber, true );
    }
    
    QodeEdit* editor;
    MarginContainer* margins;
    QPalette originalPalette;
    QodeEdit::Ruler rulerMode;
    int rulerWidth;

    QLine rulerLine() const
    {
        const QPoint offset = editor->contentOffset().toPoint();
        const int x = rulerWidth *QFontMetrics( editor->font() ).averageCharWidth();
        return QLine( QPoint( x, -4 ) +offset, QPoint( x, editor->viewport()->height() +4 ) +offset );
    }
    
    QRect rulerRect() const
    {
        const QPoint offset = editor->contentOffset().toPoint();
        const int x = rulerWidth *QFontMetrics( editor->font() ).averageCharWidth();
        QRect rect( QPoint( x +offset.x(), offset.y() -4 ), QSize( editor->viewport()->size() +QSize( 0, 4 ) ) );
        return rect;
    }
    
    QRect caretLineRect() const
    {
        QRect rect = editor->cursorRect().adjusted( 0, -1, 0, 2 );
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
        d( new QodeEditPrivate( this ) )
{
    setAutoFillBackground( true );
    
#if defined( HAS_QT_5 )
    connect( this, &QodeEdit::cursorPositionChanged, viewport(), &QWidget::update );
#else
    connect( this, SIGNAL( cursorPositionChanged() ), viewport(), SLOT( update() ) );
#endif
}

QodeEdit::~QodeEdit()
{
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
            painter.setPen( palette().color( QPalette::LinkVisited ) );
            painter.drawLine( d->rulerLine() );
            break;
        case QodeEdit::BackgroundRuler:
            painter.setPen( Qt::NoPen );
            painter.setBrush( palette().color( QPalette::LinkVisited ) );
            painter.drawRect( d->rulerRect() );
            break;
    }
    
    // draw caret line
    painter.fillRect( d->caretLineRect(), palette().color( QPalette::Link ) );
    
    // finished
    painter.end();
    
    // normal editor painting
    QPlainTextEdit::paintEvent( event );
}

#include "QodeEdit.moc"
