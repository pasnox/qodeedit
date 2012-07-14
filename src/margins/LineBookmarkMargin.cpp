#include "LineBookmarkMargin.h"
#include "QodeEdit.h"
#include "QodeEditTextDocument.h"
#include "QodeEditUserData.h"

#include <QPainter>
#include <QTextBlock>
#include <QPixmapCache>
#include <QIcon>
#include <QDebug>

#define LineBookmarkMarginMargins 1

LineBookmarkMargin::LineBookmarkMargin( MarginStacker* marginStacker )
    : AbstractMargin( marginStacker )
{
    setMinimumWidth( 10 +( LineBookmarkMarginMargins *2 ) );
    
    connect( this, SIGNAL( doubleClicked( int, Qt::MouseButton, Qt::MouseButtons, Qt::KeyboardModifiers ) ), this, SLOT( mouseDoubleClicked( int, Qt::MouseButton, Qt::MouseButtons, Qt::KeyboardModifiers ) ) );
}

LineBookmarkMargin::~LineBookmarkMargin()
{
}

void LineBookmarkMargin::paintEvent( QPaintEvent* event )
{
    AbstractMargin::paintEvent( event );
    
    QPainter painter( this );
	painter.setRenderHint( QPainter::Antialiasing, false );
    painter.setRenderHint( QPainter::SmoothPixmapTransform, true );
    
    const int firstLine = firstVisibleLine( event->rect() );
    const int lastLine = lastVisibleLine( event->rect() );
    const QodeEditTextDocument* document = qobject_cast<QodeEditTextDocument*>( editor()->document() );
    const QString iconKey = "bookmarks";
    
	#warning TODO: iterate blocks from firstLine until lastLine encounter to avoid recursive call to findBlockByNumber
	for ( int i = firstLine; i <= lastLine; i++ ) {
        const QRect rect = lineRect( i ).adjusted( LineBookmarkMarginMargins, LineBookmarkMarginMargins, -LineBookmarkMarginMargins, -LineBookmarkMarginMargins );
        const QTextBlock block = document->findBlockByNumber( i );
        const QodeEditUserData* data = document->userData( block );
        
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
}

void LineBookmarkMargin::mouseDoubleClicked( int line, Qt::MouseButton button, Qt::MouseButtons buttons, Qt::KeyboardModifiers modifiers )
{
    Q_UNUSED( buttons );
    
    if ( button != Qt::LeftButton || modifiers != Qt::NoModifier ) {
        return;
    }
    
    #warning TODO: Create bookmark api in QodeEdit and use it.
    const QodeEditTextDocument* document = qobject_cast<QodeEditTextDocument*>( editor()->document() );
    QTextBlock block = document->findBlockByNumber( line );
    QodeEditUserData* data = document->userData( block );
    data->hasBookmark = !data->hasBookmark;
    updateLineRect( line );
}
