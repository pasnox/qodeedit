#include "MarginStacker.h"
#include "CodeEditor.h"
#include "AbstractMargin.h"
#include "LineBookmarkMargin.h"
#include "LineNumberMargin.h"
#include "LineRevisionMargin.h"
#include "LineSpacingMargin.h"

#include <QHBoxLayout>
#include <QMap>
#include <QTimer>
#include <QDebug>

// MarginStackerPrivate

class MarginStackerPrivate : public QObject {
    Q_OBJECT

public:
    QMap<MarginStacker::Type, AbstractMargin*> margins;
    MarginStacker* stacker;
    QHBoxLayout* layout;
    CodeEditor* editor;
    QTimer* updateLayoutTimer;
    
    MarginStackerPrivate( MarginStacker* _stacker )
        : QObject( _stacker ),
            stacker( _stacker ),
            layout( new QHBoxLayout( stacker ) ),
            editor( 0 ),
            updateLayoutTimer( new QTimer( this ) )
    {
        Q_ASSERT( stacker );
        
        layout->setMargin( 0 );
        layout->setSpacing( 0 );
        
        updateLayoutTimer->setInterval( 20 );
        updateLayoutTimer->setSingleShot( true );
        
        connect( updateLayoutTimer, SIGNAL( timeout() ), this, SLOT( updateLayoutTimeout() ) );
    }
    
    int indexOfNewMargin( MarginStacker::Type type ) const {
        QSet<MarginStacker::Type> types = margins.keys().toSet();
        
        if ( types.isEmpty() ) {
            return 0;
        }
        
        if ( type < *types.begin() ) {
            return 0;
        }
        
        if ( type > *( types.end() -1 ) ) {
            return types.count();
        }
        
        for ( int i = 0; i < types.count(); i++ ) {
            const MarginStacker::Type current = *( types.begin() +i );
            
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
                case MarginStacker::LineNumbering:
                    margin = new LineNumberMargin( stacker );
                    break;
                case MarginStacker::LineFolding:
                    //margin = new LineFoldMargin( stacker );
                    break;
                case MarginStacker::LineBookmarking:
                    margin = new LineBookmarkMargin( stacker );
                    break;
                case MarginStacker::LineRevisioning:
                    margin = new LineRevisionMargin( stacker );
                    break;
                case MarginStacker::LineSpacing:
                    margin = new LineSpacingMargin( stacker );
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

public slots:
    void updateLayout() {
        updateLayoutTimer->start();
    }
    
    void updateLayoutTimeout() {
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
};

// MarginStacker

MarginStacker::MarginStacker( CodeEditor* editor )
    : QWidget( editor ),
        d( new MarginStackerPrivate( this ) )
{
    setSizePolicy( QSizePolicy::Maximum, QSizePolicy::Expanding );
    
    if ( editor ) {
        editor->setMarginStacker( this );
    }
}

MarginStacker::~MarginStacker()
{
}

AbstractMargin* MarginStacker::margin( MarginStacker::Type type ) const
{
    return d->margins.value( type );
}

CodeEditor* MarginStacker::editor() const
{
    return d->editor;
}

void MarginStacker::setEditor( CodeEditor* editor )
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

#include "MarginStacker.moc"
