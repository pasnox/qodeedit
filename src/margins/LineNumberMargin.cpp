#include "LineNumberMargin.h"

#include <QPainter>
#include <QDebug>

LineNumberMargin::LineNumberMargin( QodeEdit* editor )
    : AbstractMargin( editor )
{
    connect( this, SIGNAL( clicked( int, Qt::MouseButton, Qt::MouseButtons, Qt::KeyboardModifiers ) ), this, SLOT( q_clicked( int, Qt::MouseButton, Qt::MouseButtons, Qt::KeyboardModifiers ) ) );
    connect( this, SIGNAL( doubleClicked( int, Qt::MouseButton, Qt::MouseButtons, Qt::KeyboardModifiers ) ), this, SLOT( q_doubleClicked( int, Qt::MouseButton, Qt::MouseButtons, Qt::KeyboardModifiers ) ) );
    connect( this, SIGNAL( entered( int ) ), this, SLOT( q_entered( int ) ) );
    connect( this, SIGNAL( left( int ) ), this, SLOT( q_left( int ) ) );
}

LineNumberMargin::~LineNumberMargin()
{
}

QSize LineNumberMargin::minimumSizeHint() const
{
    QSize s = AbstractMargin::minimumSizeHint();
    s.setWidth( 30 );
    return s;
}

void LineNumberMargin::paintEvent( QPaintEvent* event )
{
    AbstractMargin::paintEvent( event );
    
    QPainter painter( this );
    painter.setBrush( QColor( Qt::red ) );
    painter.drawRect( rect().adjusted( 0, 0, -1, -1 ) );
}

void LineNumberMargin::q_clicked( int line, Qt::MouseButton button, Qt::MouseButtons buttons, Qt::KeyboardModifiers modifiers )
{
    qWarning() << Q_FUNC_INFO << line << button << buttons << modifiers;
}

void LineNumberMargin::q_doubleClicked( int line, Qt::MouseButton button, Qt::MouseButtons buttons, Qt::KeyboardModifiers modifiers )
{
    qWarning() << Q_FUNC_INFO << line << button << buttons << modifiers;
}

void LineNumberMargin::q_entered( int line )
{
    qWarning() << Q_FUNC_INFO << line;
}

void LineNumberMargin::q_left( int line )
{
    qWarning() << Q_FUNC_INFO << line;
}
