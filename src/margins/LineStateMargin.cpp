#include "LineStateMargin.h"
#include "QodeEdit.h"
#include "QodeEditUserData.h"

#include <QPainter>
#include <QTextDocument>
#include <QTextBlock>
#include <QDebug>

LineStateMargin::LineStateMargin( MarginStacker* marginStacker )
    : AbstractMargin( marginStacker )
{
    setMinimumWidth( 2 );
    setMouseTracking( false );
    
    //
    //QAbstractTextDocumentLayout::updateBlock ( const QTextBlock & block )
    //QTextBlock QTextDocument::findBlock ( int pos ) const
    //QTextBlock::setUserState ( int state )
    //QTextBlock::setUserData ( QTextBlockUserData * data )
    //QTextBlockUserData
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
    
    const int firstLine = firstVisibleLine();
    const int lastLine = lastVisibleLine();
    
    painter.setPen( Qt::NoPen );
    
	for ( int i = firstLine; i <= lastLine; i++ ) {
        const QRect rect = lineRect( i );
        const QTextBlock block = editor()->document()->findBlockByNumber( i );
		QodeEditUserData* data = static_cast<QodeEditUserData*>( block.userData() );
		
		if ( !data ) {
			continue;
		}
		
		if ( data->savedRevision.contains( block.revision() ) ) {
			painter.setBrush( QColor( 0, 255, 0 ) );
		}
		else if ( data->modified ) {
			painter.setBrush( QColor( 255, 0, 0 ) );
		}
		else {
			continue;
		}
		
        painter.drawRect( rect );
    }
}

void LineStateMargin::updateWidthRequested()
{
}
