#include "SyntaxModel.h"
#include "SyntaxDocument.h"

#include <QDebug>

// ModelPrivate

class Syntax::ModelPrivate {
public:
    const QHash<QString, Syntax::Document>* constSyntaxes;
    QList<Syntax::Document> syntaxes;
    
    ModelPrivate( Syntax::Model* _model, const QHash<QString, Syntax::Document>* _syntaxes )
        : constSyntaxes( _syntaxes ),
            model( _model )
    {
        Q_ASSERT( model );
        Q_ASSERT( constSyntaxes );
    }
    
    void update() {
        syntaxes = constSyntaxes->values();
        qSort( syntaxes );
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
    
    const Syntax::Document& document = d->syntaxes[ index.row() ];
    
    switch ( role ) {
        case Qt::DecorationRole:
            return QVariant();
        case Qt::DisplayRole:
        case Qt::ToolTipRole:
            return document.localizedName.isEmpty() ? document.name : document.localizedName;
        case Syntax::Model::InternalName:
            return document.name;
    }
    
    return QVariant();
}

QString Syntax::Model::internalName( const QModelIndex& index ) const
{
    return d->syntaxes.value( index.row() ).name;
}

void Syntax::Model::update()
{
    d->update();
}
