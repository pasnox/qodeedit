#include "LineStateMargin.h"
#include "QodeEdit.h"
#include "QodeEditUserData.h"
#include "QodeEditTextDocument.h"

#include <QPainter>
#include <QTextDocument>
#include <QTextBlock>
#include <QDebug>

LineStateMargin::LineStateMargin( MarginStacker* marginStacker )
    : AbstractMargin( marginStacker )
{
    setMinimumWidth( 2 );
    setMouseTracking( false );
}

LineStateMargin::~LineStateMargin()
{
}

void LineStateMargin::setEditor( QodeEdit* editor )
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

void LineStateMargin::paintEvent( QPaintEvent* event )
{
    AbstractMargin::paintEvent( event );
    
    QPainter painter( this );
    painter.setRenderHint( QPainter::Antialiasing, false );
    painter.setPen( Qt::NoPen );
	
    const int firstLine = firstVisibleLine();
    const int lastLine = lastVisibleLine();
	const QodeEditTextDocument* document = qobject_cast<QodeEditTextDocument*>( editor()->document() );
    
	for ( int i = firstLine; i <= lastLine; i++ ) {
        const QRect rect = lineRect( i );
        const QTextBlock block = document->findBlockByNumber( i );
		
		if ( block.revision() != document->lastSavedRevision() ) {
			if ( block.revision() < 0 ) {
				painter.setBrush( QColor( Qt::darkGreen ) );
			}
			else {
				painter.setBrush( QColor( Qt::red ) );
			}
			
			painter.drawRect( rect );
		}
    }
}

void LineStateMargin::updateWidthRequested()
{
}
