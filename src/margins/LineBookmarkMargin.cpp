#include "LineBookmarkMargin.h"
#include "CodeEditor.h"
#include "TextDocument.h"
#include "TextBlockUserData.h"

#include <QPainter>
#include <QTextBlock>
#include <QPixmapCache>
#include <QIcon>
#include <QDebug>

#define LineBookmarkMarginMargins 1

// LineBookmarkMarginPrivate

class LineBookmarkMarginPrivate : public QObject {
	Q_OBJECT

public:
	LineBookmarkMargin* margin;
	
	LineBookmarkMarginPrivate( LineBookmarkMargin* _margin )
		: QObject( _margin ),
			margin( _margin )
	{
		Q_ASSERT( margin );
		
		connect( margin, SIGNAL( mouseDoubleClicked( int, Qt::MouseButton, Qt::MouseButtons, Qt::KeyboardModifiers ) ), this, SLOT( mouseDoubleClicked( int, Qt::MouseButton, Qt::MouseButtons, Qt::KeyboardModifiers ) ) );
	}

public slots:
	void mouseDoubleClicked( int line, Qt::MouseButton button, Qt::MouseButtons buttons, Qt::KeyboardModifiers modifiers ) {
		Q_UNUSED( buttons );
		
		if ( button != Qt::LeftButton || modifiers != Qt::NoModifier ) {
			return;
		}
		
		#warning TODO: Create bookmark api in CodeEditor and use it.
		const TextDocument* document = margin->editor()->textDocument();
		QTextBlock block = document->findBlockByNumber( line );
		TextBlockUserData* data = document->userData( block );
		data->hasBookmark = !data->hasBookmark;
		margin->updateLineRect( line );
	}
};

// LineBookmarkMargin

LineBookmarkMargin::LineBookmarkMargin( MarginStacker* marginStacker )
    : AbstractMargin( marginStacker )
{
	updateWidthRequested();
}

LineBookmarkMargin::~LineBookmarkMargin()
{
	delete d;
}

void LineBookmarkMargin::paintEvent( QPaintEvent* event )
{
    AbstractMargin::paintEvent( event );
    
    QPainter painter( this );
	painter.setRenderHint( QPainter::Antialiasing, false );
    painter.setRenderHint( QPainter::SmoothPixmapTransform, true );
    
    const int firstLine = firstVisibleLine( event->rect() );
    const int lastLine = lastVisibleLine( event->rect() );
    const TextDocument* document = editor()->textDocument();
    const QString iconKey = "bookmarks";
    
	#warning TODO: iterate blocks from firstLine until lastLine encounter to avoid recursive call to findBlockByNumber
	for ( int i = firstLine; i <= lastLine; i++ ) {
        const QRect rect = lineRect( i ).adjusted( LineBookmarkMarginMargins, LineBookmarkMarginMargins, -LineBookmarkMarginMargins, -LineBookmarkMarginMargins );
        const QTextBlock block = document->findBlockByNumber( i );
        const TextBlockUserData* data = document->userData( block );
        
        if ( data && data->hasBookmark ) {
            const int size = qMin( rect.width(), rect.height() );
            const QSize pixmapSize( size, size );
            const QString key = QString( "%1-%2-%3" ).arg( size ).arg( size ).arg( iconKey );
            QPixmap pixmap;
            
            if ( !QPixmapCache::find( key, &pixmap ) ) {
                const QIcon icon = QIcon::fromTheme( iconKey );
                pixmap = icon.pixmap( pixmapSize );
                
                if ( !QPixmapCache::insert( key, pixmap ) ) {
                    qWarning( "%s: Can't cache pixmap %s", Q_FUNC_INFO, qPrintable( key ) );
                    continue;
                }
            }
            
            QRect pixmapRect( QPoint(), pixmapSize );
            pixmapRect.moveCenter( rect.center() );
            
            painter.drawPixmap( pixmapRect, pixmap );
        }
    }
}

void LineBookmarkMargin::updateWidthRequested()
{
	setMinimumWidth( 10 +( LineBookmarkMarginMargins *2 ) );
}
