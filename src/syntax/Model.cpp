/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : Model.cpp
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#include "Model.h"
#include "Document.h"
#include "QodeEdit.h"
#include "Tools.h"

#include <QStringList>
#include <QIcon>
#include <QApplication>
#include <QDebug>

// ModelPrivate

class Syntax::ModelPrivate : public QObject {
    Q_OBJECT
    
public:
    Syntax::Model* model;
    QodeEdit::Manager* manager;
    QStringList syntaxes;
    QHash<QString, QIcon> icons; // name, icon
    bool updatingIcons;
    
    ModelPrivate( Syntax::Model* _model, QodeEdit::Manager* _manager )
        : model( _model ),
            manager( _manager ),
            updatingIcons( false )
    {
        Q_ASSERT( model );
        Q_ASSERT( manager );
        updateSyntaxes();
        connect( manager, SIGNAL( syntaxesChanged() ), this, SLOT( updateSyntaxes() ) );
    }
    
public slots:
    void updateIcons() {
        if ( updatingIcons ) {
            return;
        }
        
        updatingIcons = true;
        const QHash<QString, Syntax::Document> availableDocuments = manager->availableDocuments();
        
        foreach ( const QString& syntax, syntaxes ) {
            const Syntax::Document& document = availableDocuments[ syntax ];
            
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
            
            //QApplication::processEvents(); // avoid possible freeze/lag
        }
        
        updatingIcons = false;
    }
    
    void updateSyntaxes() {
        const QHash<QString, Syntax::Document> availableDocuments = manager->availableDocuments();
        const QStringList oldSyntaxes = syntaxes;
        QStringList newSyntaxes;
        
        foreach ( const Syntax::Document& document, availableDocuments.values() ) {
            newSyntaxes << ( document.localizedName().isEmpty() ? document.name() : document.localizedName() );
        }
        
        qSort( newSyntaxes.begin(), newSyntaxes.end(), QodeEdit::Tools::localeAwareStringLessThan );
        
        if ( oldSyntaxes == newSyntaxes ) {
            return;
        }
        
        const QModelIndexList oldIndexes = model->persistentIndexList();
        QModelIndexList newIndexes = oldIndexes;
        QHash<QString, int> newPositions;
        
        emit model->layoutAboutToBeChanged();
        
        syntaxes = newSyntaxes;
        
        for ( int i = 0; i < newSyntaxes.count(); i++ ) {
            const Syntax::Document& document = availableDocuments[ newSyntaxes[ i ] ];
            newPositions[ document.name() ] = i;
        }
        
        for ( int i = 0; i < oldSyntaxes.count(); i++ ) {
            const Syntax::Document& document = availableDocuments[ oldSyntaxes[ i ] ];
            const int row = newPositions.value( document.name(), -1 );
            
            if ( row == -1 ) {
                newIndexes[ i ] = QModelIndex();
            }
            else {
                newIndexes[ i ] = model->index( row, 0, QModelIndex() );
            }
        }
        
        model->changePersistentIndexList( oldIndexes, newIndexes );
        
        updateIcons();
        
        emit model->layoutChanged();
    }
};

// Model

Syntax::Model::Model( QodeEdit::Manager* manager, QObject* parent )
    : QAbstractListModel( parent ),
        d( new Syntax::ModelPrivate( this, manager ) )
{
}

Syntax::Model::~Model()
{
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
    
    const Syntax::Document document = d->manager->document( d->syntaxes.at( index.row() ) );
    
    switch ( role ) {
        case Qt::DecorationRole:
            return d->icons.value( document.name() );
        case Qt::DisplayRole:
        case Qt::ToolTipRole:
        case Syntax::Model::DisplayName:
            return document.localizedName().isEmpty() ? document.name() : document.localizedName();    
        case Syntax::Model::InternalName:
            return document.name();
    }
    
    return QVariant();
}

#include "Model.moc"
