#include "LineNumberMargin.h"
#include "CodeEditor.h"
#include "TextDocument.h"

#include <QPainter>
#include <QTextBlock>
#include <QDebug>

#define LineNumberMarginMargins 2

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

void LineNumberMargin::paintEvent( QPaintEvent* event )
{
    AbstractMargin::paintEvent( event );
    
    QPainter painter( this );
	painter.setRenderHint( QPainter::Antialiasing, false );
    
    const int firstLine = firstVisibleLine( event->rect() );
    const int lastLine = lastVisibleLine( event->rect() );
    const int flags = Qt::AlignVCenter | Qt::AlignRight;
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
