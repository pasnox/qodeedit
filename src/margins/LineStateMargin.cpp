#include "LineStateMargin.h"
#include "QodeEdit.h"

#include <QPainter>
#include <QTextDocument>
#include <QTextBlock>
#include <QDebug>

class LineStateMargin::Private : public QObject {
    Q_OBJECT
    
public:
    Private( AbstractMargin* _margin, MarginStacker* marginStacker )
        : QObject( _margin ),
            margin( _margin ), stacker( marginStacker )
    {
        Q_ASSERT( margin );
		Q_ASSERT( marginStacker );
    }
    
public slots:
    void contentsChange( int position, int charsRemoved, int charsAdded ) {
        const bool modified = charsRemoved || charsAdded;
        
        if ( modified ) {
            QTextBlock block = margin->editor()->document()->findBlock( position );
            block.setUserState( LineStateMargin::Modified );
            margin->update();
        }
    }

public:
    AbstractMargin* margin;
	MarginStacker* stacker;
};

LineStateMargin::LineStateMargin( MarginStacker* marginStacker )
    : AbstractMargin( marginStacker ),
        d( new LineStateMargin::Private( this, marginStacker ) )
{
    setMinimumWidth( 8 );
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
        disconnect( oldEditor->document(), SIGNAL( contentsChange( int, int, int ) ), d, SLOT( contentsChange( int, int, int ) ) );
	}
	
	AbstractMargin::setEditor( editor );
	
	if ( editor ) {
		connect( editor->document(), SIGNAL( contentsChange( int, int, int ) ), d, SLOT( contentsChange( int, int, int ) ) );
	}
}

void LineStateMargin::paintEvent( QPaintEvent* event )
{
    AbstractMargin::paintEvent( event );
    
    QPainter painter( this );
    
    const int firstLine = firstVisibleLine();
    const int lastLine = lastVisibleLine();
    
    // debug
    /*painter.setPen( Qt::red );
    painter.drawRect( rect().adjusted( 0, 0, -1, -1 ) );*/
    
    painter.setPen( Qt::NoPen );
    
	for ( int i = firstLine; i <= lastLine; i++ ) {
        const QRect rect = lineRect( i );
        const QTextBlock block = editor()->document()->findBlockByNumber( i );
        const bool modified = block.userState() == LineStateMargin::Modified;
		
        if ( modified ) {
            painter.setBrush( QColor( 0, 255, 0 ) );
            painter.drawRect( rect );
        }
    }
}

void LineStateMargin::updateWidthRequested()
{
}

#include "LineStateMargin.moc"
