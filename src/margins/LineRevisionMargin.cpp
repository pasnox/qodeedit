#include "LineRevisionMargin.h"
#include "CodeEditor.h"
#include "TextDocument.h"

#include <QPainter>
#include <QTextBlock>
#include <QDebug>

LineRevisionMargin::LineRevisionMargin( MarginStacker* marginStacker )
    : AbstractMargin( marginStacker )
{
    updateWidthRequested();
    setMouseTracking( false );
}

LineRevisionMargin::~LineRevisionMargin()
{
}

void LineRevisionMargin::setEditor( CodeEditor* editor )
{
	CodeEditor* oldEditor = this->editor();
	
	if ( oldEditor ) {
        disconnect( oldEditor->textDocument(), SIGNAL( contentsChanged() ), this, SLOT( update() ) );
		disconnect( oldEditor->textDocument(), SIGNAL( modificationChanged( bool ) ), this, SLOT( update() ) );
	}
	
	AbstractMargin::setEditor( editor );
	
	if ( editor ) {
		connect( editor->textDocument(), SIGNAL( contentsChanged() ), this, SLOT( update() ) );
		connect( editor->textDocument(), SIGNAL( modificationChanged( bool ) ), this, SLOT( update() ) );
	}
}

void LineRevisionMargin::paintEvent( QPaintEvent* event )
{
    AbstractMargin::paintEvent( event );
    
    QPainter painter( this );
    painter.setRenderHint( QPainter::Antialiasing, false );
    painter.setBrush( Qt::NoBrush );
	
    const int firstLine = firstVisibleLine( event->rect() );
    const int lastLine = lastVisibleLine( event->rect() );
	const TextDocument* document = editor()->textDocument();
    
	#warning TODO: iterate blocks from firstLine until lastLine encounter to avoid recursive call to findBlockByNumber
	for ( int i = firstLine; i <= lastLine; i++ ) {
        const QRect rect = lineRect( i );
        const QTextBlock block = document->findBlockByNumber( i );
		
		if ( block.revision() != document->lastUnmodifiedRevision() ) {
			if ( block.revision() < 0 ) {
				painter.setPen( QPen( QColor( Qt::darkGreen ), minimumWidth() ) );
			}
			else {
				painter.setPen( QPen( QColor( Qt::red ), minimumWidth() ) );
			}
			
			painter.drawLine( rect.topRight(), rect.bottomRight() );
		}
    }
}

void LineRevisionMargin::updateWidthRequested()
{
	setMinimumWidth( 2 );
}
