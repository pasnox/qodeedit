#include "LineRevisionMargin.h"
#include "QodeEdit.h"
#include "QodeEditUserData.h"
#include "QodeEditTextDocument.h"

#include <QPainter>
#include <QTextDocument>
#include <QTextBlock>
#include <QDebug>

LineRevisionMargin::LineRevisionMargin( MarginStacker* marginStacker )
    : AbstractMargin( marginStacker )
{
    setMinimumWidth( 2 );
    setMouseTracking( false );
}

LineRevisionMargin::~LineRevisionMargin()
{
}

void LineRevisionMargin::setEditor( QodeEdit* editor )
{
	QodeEdit* oldEditor = this->editor();
	
	if ( oldEditor ) {
        disconnect( oldEditor->document(), SIGNAL( contentsChanged() ), this, SLOT( update() ) );
		disconnect( oldEditor->document(), SIGNAL( modificationChanged( bool ) ), this, SLOT( update() ) );
	}
	
	AbstractMargin::setEditor( editor );
	
	if ( editor ) {
		connect( oldEditor->document(), SIGNAL( contentsChanged() ), this, SLOT( update() ) );
		connect( oldEditor->document(), SIGNAL( modificationChanged( bool ) ), this, SLOT( update() ) );
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
	const QodeEditTextDocument* document = qobject_cast<QodeEditTextDocument*>( editor()->document() );
    
	for ( int i = firstLine; i <= lastLine; i++ ) {
        const QRect rect = lineRect( i );
        const QTextBlock block = document->findBlockByNumber( i );
		
		if ( block.revision() != document->lastSavedRevision() ) {
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
}
