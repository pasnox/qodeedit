/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : LineBookmarkMargin.cpp
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#include "LineBookmarkMargin.h"
#include "editor/CodeEditor.h"
#include "editor/TextDocument.h"
#include "editor/TextBlockUserData.h"

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
        
        connect( margin, SIGNAL( mouseClicked( int, Qt::MouseButton, Qt::MouseButtons, Qt::KeyboardModifiers ) ), this, SLOT( mouseClicked( int, Qt::MouseButton, Qt::MouseButtons, Qt::KeyboardModifiers ) ) );
    }

public slots:
    void mouseClicked( int line, Qt::MouseButton button, Qt::MouseButtons buttons, Qt::KeyboardModifiers modifiers ) {
        Q_UNUSED( buttons );
        
        if ( button != Qt::LeftButton || modifiers != Qt::NoModifier ) {
            return;
        }
        
        margin->editor()->toggleBookmark( line );
    }
};

// LineBookmarkMargin

LineBookmarkMargin::LineBookmarkMargin( MarginStacker* marginStacker )
    : AbstractMargin( marginStacker ),
        d( new LineBookmarkMarginPrivate( this ) )
{
    updateWidthRequested();
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
    const TextDocument* document = editor()->textDocument();
    const QString iconKey = "bookmarks";
    
    for ( QTextBlock block = document->findBlockByNumber( firstLine ); block.isValid() && block.blockNumber() <= lastLine; block = block.next() ) {
        const QRect rect = blockRect( block ).adjusted( LineBookmarkMarginMargins, 0, -( LineBookmarkMarginMargins +1 ), 0 ); // +1 for the 1pixel border
        const TextBlockUserData* data = document->testUserData( block );
        
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
    
    if ( event->rect().right() < rect().right() ) {
        return;
    }
    
    painter.setPen( QPen( QColor( palette().color( backgroundRole() ).darker() ), 1 ) );
    painter.drawLine( event->rect().topRight(), event->rect().bottomRight() );
}

void LineBookmarkMargin::updateWidthRequested()
{
    setMinimumWidth( 10 +( LineBookmarkMarginMargins *2 ) +1 ); // +1 for the 1 pixel border
}

#include "LineBookmarkMargin.moc"
