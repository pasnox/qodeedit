#include "SyntaxModel.h"
#include "SyntaxDocument.h"
#include "QodeEdit.h"

#include <QStringList>
#include <QIcon>
#include <QDebug>

// ModelPrivate

class Syntax::ModelPrivate {
public:
    const QHash<QString, Syntax::Document>* constSyntaxes;
    QStringList syntaxes;
    QHash<QString, QIcon> icons; // name, icon
    
    ModelPrivate( Syntax::Model* _model, const QHash<QString, Syntax::Document>* _syntaxes )
        : constSyntaxes( _syntaxes ),
            model( _model )
    {
        Q_ASSERT( model );
        Q_ASSERT( constSyntaxes );
    }
    
    void updateIcons() {
        foreach ( const QString& syntax, syntaxes ) {
            const Syntax::Document& document = (*constSyntaxes)[ syntax ];
            
            if ( icons.contains( document.name() ) ) {
                continue;
            }
            
            QString iconName;
            QIcon icon;
            
            foreach ( QString key, document.mimeType() ) {
                key = key.replace( "/", "-" );
                
                if ( !QIcon::hasThemeIcon( key ) ) {
                    continue;
                }
                
                iconName = key;
            }
            
            if ( iconName.isEmpty() ) {
                iconName = "text-plain";
            }
            
            icon = icons.value( document.name(), QIcon() );
            
            if ( icon.isNull() ) {
                icon = QIcon::fromTheme( iconName );
                icons[ document.name() ] = icon;
            }
        }
    }
    
    void update() {
        const QStringList oldSyntaxes;
        QStringList newSyntaxes;
        
        foreach ( const Syntax::Document& document, constSyntaxes->values() ) {
            newSyntaxes << ( document.localizedName().isEmpty() ? document.name() : document.localizedName() );
        }
        
        qSort( newSyntaxes.begin(), newSyntaxes.end(), QodeEdit::localeAwareStringLessThan );
        
        if ( oldSyntaxes == newSyntaxes ) {
            return;
        }
        
        const QModelIndexList oldIndexes = model->persistentIndexList();
        QModelIndexList newIndexes = oldIndexes;
        QHash<QString, int> newPositions;
        
        emit model->layoutAboutToBeChanged();
        
        syntaxes = newSyntaxes;
        updateIcons();
        
        for ( int i = 0; i < newSyntaxes.count(); i++ ) {
            const Syntax::Document& document = (*constSyntaxes)[ newSyntaxes[ i ] ];
            newPositions[ document.name() ] = i;
        }
        
        for ( int i = 0; i < oldSyntaxes.count(); i++ ) {
            const Syntax::Document& document = (*constSyntaxes)[ oldSyntaxes[ i ] ];
            const int row = newPositions.value( document.name(), -1 );
            
            if ( row == -1 ) {
                newIndexes[ i ] = QModelIndex();
            }
            else {
                newIndexes[ i ] = model->index( row, 0, QModelIndex() );
            }
        }
        
        model->changePersistentIndexList( oldIndexes, newIndexes );
        
        emit model->layoutChanged();
    }

private:
    Syntax::Model* model;
};

// Model

Syntax::Model::Model( const QHash<QString, Syntax::Document>* syntaxes, QObject* parent )
    : QAbstractListModel( parent ),
        d( new Syntax::ModelPrivate( this, syntaxes ) )
{
}

Syntax::Model::~Model()
{
    delete d;
}

int Syntax::Model::rowCount( const QModelIndex& parent ) const
{
    return parent == QModelIndex() ? d->syntaxes.count() : 0;
}

QVariant Syntax::Model::data( const QModelIndex& index, int role ) const
{
    if ( !index.isValid() || index.row() < 0 || index.row() >= d->syntaxes.count() || index.column() != 0 ) {
        return QVariant();
    }
    
    const Syntax::Document& document = (*d->constSyntaxes)[ d->syntaxes[ index.row() ] ];
    
    switch ( role ) {
        case Qt::DecorationRole:
            return d->icons.value( document.name() );
        case Qt::DisplayRole:
        case Qt::ToolTipRole:
            return document.localizedName().isEmpty() ? document.name() : document.localizedName();
        case Syntax::Model::InternalName:
            return document.name();
    }
    
    return QVariant();
}

void Syntax::Model::update()
{
    d->update();
}
