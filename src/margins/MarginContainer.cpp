#include "MarginContainer.h"
#include "QodeEdit.h"
#include "AbstractMargin.h"
#include "LineNumberMargin.h"

#include <QHBoxLayout>
#include <QMap>
#include <QDebug>

// MarginContainerPrivate

class MarginContainerPrivate : public QObject {
    Q_OBJECT

public:
    MarginContainerPrivate( MarginContainer* _container, QodeEdit* _editor )
        : QObject( _container ),
            container( _container ),
            editor( _editor ),
            layout( new QHBoxLayout( container ) )
    {
        Q_ASSERT( container );
        Q_ASSERT( editor );
        
        editor->installEventFilter( this );
        
        layout->setMargin( 0 );
        layout->setSpacing( 0 );
    }
    
    int indexOfNewMargin( MarginContainer::Type type ) const {
        QList<MarginContainer::Type> types = margins.keys();
        
        if ( types.isEmpty() ) {
            return 0;
        }
        
        qSort( types );
        
        if ( type > types.last() ) {
            return types.count();
        }
        
        for ( int i = 0; i < types.count(); i++ ) {
            const MarginContainer::Type current = MarginContainer::Type( types[ i ] );
            
            if ( type > current ) {
                return i;
            }
        }
        
        qFatal( "%s: You can't be there!", Q_FUNC_INFO );
        return -1;
    }
    
    void setVisible( MarginContainer::Type type, bool visible ) {
        AbstractMargin* margin = margins.value( type );
        
        if ( !margin && !visible ) {
            return;
        }
        
        if ( !visible ) {
            Q_ASSERT( margin );
            margin->deleteLater();
            margins.remove( type );
        }
        else {
            switch ( type ) {
                case MarginContainer::LineNumber:
                    margin = new LineNumberMargin( editor );
                    break;
                case MarginContainer::CodeFolding:
                    //margin = new CodeFoldingMargin( editor );
                    break;
                case MarginContainer::Bookmarks:
                    //margin = new BookmarkMargin( editor );
                    break;
                case MarginContainer::LineChange:
                    //margin = new LineChangeMargin( editor );
                    break;
            }
            
            layout->insertWidget( indexOfNewMargin( type ), margin );
        }
    }

protected:
    virtual bool eventFilter( QObject* object, QEvent* event ) {
        if ( object == editor ) {
            if ( event->type() == QEvent::Resize ) {
                const int margin = editor->frameWidth();
                const int width = container->minimumSizeHint().width();
                editor->setViewportMargins( width, 0, 0, 0 );
                container->setGeometry( QRect( QPoint( margin, margin ), QSize( width, editor->viewport()->height() ) ) );
                return true;
            }
        }
        
        return QObject::eventFilter( object, event );
    }

public:
    MarginContainer* container;
    QodeEdit* editor;
    QHBoxLayout* layout;
    QMap<MarginContainer::Type, AbstractMargin*> margins;
};

// MarginContainer

MarginContainer::MarginContainer( QodeEdit* editor )
    : QWidget( editor ),
        d( new MarginContainerPrivate( this, editor ) )
{
    setSizePolicy( QSizePolicy::Maximum, QSizePolicy::Expanding );
}

MarginContainer::~MarginContainer()
{
}

bool MarginContainer::isVisible( MarginContainer::Type type ) const
{
    return d->margins.value( type ) != 0;
}

void MarginContainer::setVisible( MarginContainer::Type type, bool visible )
{
    d->setVisible( type, visible );
}

#include "MarginContainer.moc"
