#include "MarginStacker.h"
#include "QodeEdit.h"
#include "AbstractMargin.h"
#include "LineNumberMargin.h"
#include "LineStateMargin.h"
#include "SpacingMargin.h"

#include <QHBoxLayout>
#include <QMap>
#include <QDebug>

// MarginStacker::Private

class MarginStacker::Private {
public:
    Private( MarginStacker* _stacker )
            : stacker( _stacker ),
            layout( new QHBoxLayout( stacker ) ),
            editor( 0 )
    {
        Q_ASSERT( stacker );
        
        layout->setMargin( 0 );
        layout->setSpacing( 0 );
    }
    
    int indexOfNewMargin( MarginStacker::Type type ) const {
        QList<MarginStacker::Type> types = margins.keys();
        
        if ( types.isEmpty() ) {
            return 0;
        }
        
        qSort( types );
        
        if ( type < types.first() ) {
            return 0;
        }
        
        if ( type > types.last() ) {
            return types.count();
        }
        
        for ( int i = 0; i < types.count(); i++ ) {
            const MarginStacker::Type current = MarginStacker::Type( types[ i ] );
            
            if ( type < current +1 ) {
                return i;
            }
        }
        
        qFatal( "%s: You can't be there (%i)!!!", Q_FUNC_INFO, type );
        return -1;
    }
    
    void setVisible( MarginStacker::Type type, bool visible ) {
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
            if ( margin ) {
                return;
            }
            
            const int index = indexOfNewMargin( type );
            
            switch ( type ) {
                case MarginStacker::LineNumber:
                    margin = new LineNumberMargin( stacker );
                    break;
                case MarginStacker::CodeFolding:
                    //margin = new CodeFoldingMargin( stacker );
                    break;
                case MarginStacker::Bookmarks:
                    //margin = new BookmarkMargin( stacker );
                    break;
                case MarginStacker::LineState:
                    margin = new LineStateMargin( stacker );
                    break;
                case MarginStacker::Spacing:
                    margin = new SpacingMargin( stacker );
                    break;
                default:
                    Q_ASSERT( 0 );
                    break;
            }
            
            if ( !margin ) {
                //Q_ASSERT( margin );
                return;
            }
            
            margins[ type ] = margin;
            
            connect( margin, SIGNAL( resized() ), stacker, SLOT( updateLayout() ) );
            
            layout->insertWidget( index, margin );
            margin->setVisible( true );
            margin->setEditor( editor );
        }
    }
    
    void updateLayout() {
        if ( !editor ) {
            return;
        }
        
        const int margin = editor->frameWidth();
        int width = 0;
        
        foreach ( AbstractMargin* margin, margins.values() ) {
            width += margin->minimumWidth();
        }
        
        editor->setViewportMargins( width, 0, 0, 0 );
        stacker->setGeometry( QRect( QPoint( margin, margin ), QSize( width, editor->viewport()->height() ) ) );
    }

public:
    QMap<MarginStacker::Type, AbstractMargin*> margins;
    MarginStacker* stacker;
    QHBoxLayout* layout;
    QodeEdit* editor;
};

// MarginStacker

MarginStacker::MarginStacker( QodeEdit* editor )
    : QWidget( editor ),
        d( new MarginStacker::Private( this ) )
{
    setSizePolicy( QSizePolicy::Maximum, QSizePolicy::Expanding );
    
    if ( editor ) {
        editor->setMarginStacker( this );
    }
}

MarginStacker::~MarginStacker()
{
    delete d;
}

QodeEdit* MarginStacker::editor() const
{
    return d->editor;
}

void MarginStacker::setEditor( QodeEdit* editor )
{
    if ( d->editor ) {
        d->editor->removeEventFilter( this );
    }
    
    d->editor = editor;
    
    foreach ( AbstractMargin* margin, d->margins ) {
        margin->setEditor( editor );
    }
    
    if ( d->editor ) {
        d->editor->installEventFilter( this );
        setParent( d->editor );
        QWidget::setVisible( true );
        updateLayout();
    }
}

bool MarginStacker::isVisible( MarginStacker::Type type ) const
{
    return d->margins.value( type ) != 0;
}

void MarginStacker::setVisible( MarginStacker::Type type, bool visible )
{
    d->setVisible( type, visible );
}

void MarginStacker::updateLayout()
{
    d->updateLayout();
}

bool MarginStacker::eventFilter( QObject* object, QEvent* event )
{
    if ( object == d->editor ) {
        if ( event->type() == QEvent::Resize ) {
            d->updateLayout();
            return true;
        }
    }
    
    return QWidget::eventFilter( object, event );
}
