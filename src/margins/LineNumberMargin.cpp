#include "LineNumberMargin.h"
#include "QodeEdit.h"
#include "MarginContainer.h"

#include <QPainter>

#define LineNumberMarginMargins 4

LineNumberMargin::LineNumberMargin( QodeEdit* editor )
    : AbstractMargin( editor )
{
	connect( editor, SIGNAL( cursorPositionChanged() ), this, SLOT( update() ) );
    connect( this, SIGNAL( entered( int ) ), this, SLOT( update() ) );
    connect( this, SIGNAL( left( int ) ), this, SLOT( update() ) );
    connect( this, SIGNAL( countChanged( int ) ), this, SLOT( q_countChanged( int ) ) );
}

LineNumberMargin::~LineNumberMargin()
{
}

void LineNumberMargin::paintEvent( QPaintEvent* event )
{
    AbstractMargin::paintEvent( event );
    
    QPainter painter( this );
    
    const int firstLine = firstVisibleLine();
    const int lastLine = lastVisibleLine();
    const int flags = Qt::AlignVCenter | Qt::AlignRight;
	const QFont painterFont = painter.font();
	const QColor color = palette().color( QPalette::WindowText );
	const QColor lightColor = QColor( color.red(), color.green(), color.blue(), 120 );
	const QPoint cursorPos = editor()->cursorPosition();
	const QPoint mousePos = mapFromGlobal( QCursor::pos() );
	const int mouseLine = rect().contains( mousePos ) ? lineAt( mousePos ) : -1;
    
	for ( int i = firstLine; i < lastLine; i++ ) {
        const QRect rect = lineRect( i ).adjusted( 0, 0, -LineNumberMarginMargins, 0 );
		const bool isCurrentLine = cursorPos.y() == i;
		bool isHoveredLine = mouseLine == i && !isCurrentLine;
		
		if ( !isHoveredLine && ( ( i +1 ) %10 ) == 0 ) {
			isHoveredLine = true;
		}
		
		QFont font = painterFont;
		font.setBold( isCurrentLine || isHoveredLine );
		
		painter.setFont( font );
		painter.setPen( isCurrentLine ? color : lightColor );
		painter.drawText( rect, flags, QString::number( i +1 ) );
    }
}

void LineNumberMargin::q_countChanged( int count )
{
    setMinimumWidth( fontMetrics().width( QString::number( count ) ) +( LineNumberMarginMargins *2 ) );
    editor()->marginContainer()->updateLayout();
}
