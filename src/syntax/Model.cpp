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
#include "Manager.h"
#include "Document.h"
#include "QodeEdit.h"
#include "Tools.h"
#include "Threading.h"

#include <QStringList>
#include <QIcon>
#include <QPointer>
#include <QFutureWatcher>
#include <QDebug>

// QIcon::hasThemeIcon is not thread safe :(
#if !defined( IS_HAS_THEME_ICON_THREAD_SAFE )
    #define IS_HAS_THEME_ICON_THREAD_SAFE false
#endif

// ModelPrivate

class Syntax::ModelPrivate : public QObject {
    Q_OBJECT
    
public:
    Syntax::Model* model;
    QodeEdit::Manager* manager;
    QStringList syntaxes;
    QHash<QString, QString> icons; // name, icon name
    QPointer<QFutureWatcher<QHash<QString, QString> > > mimeTypesIconNamesWatcher;
    
    ModelPrivate( Syntax::Model* _model, QodeEdit::Manager* _manager )
        : model( _model ),
            manager( _manager )
    {
        Q_ASSERT( model );
        Q_ASSERT( manager );
        connect( manager, SIGNAL( syntaxesUpdated() ), this, SLOT( updateSyntaxes() ) );
        updateSyntaxes();
    }
    
public slots:
    void updateIcons( const QHash<QString, QStringList>& mimeTypes = QHash<QString, QStringList>() ) {
        if ( mimeTypesIconNamesWatcher ) {
            icons = mimeTypesIconNamesWatcher->result();
            mimeTypesIconNamesWatcher->deleteLater();
        }
        else {
            icons = QodeEdit::Tools::bestMatchingMimeTypesIcons( mimeTypes, "text/plain", true );
        }
        
        emit model->dataChanged( model->index( 0, 0 ), model->index( model->rowCount() -1, 0 ) );
    }
    
    void updateSyntaxes() {
        const QHash<QString, Syntax::Document> availableSyntaxes = manager->availableSyntaxes();
        const QStringList oldSyntaxes = syntaxes;
        QHash<QString, QStringList> mimeTypes;
        QStringList newSyntaxes;
        
        foreach ( const Syntax::Document& syntax, availableSyntaxes.values() ) {
            mimeTypes[ syntax.name() ] = syntax.mimeType().toList();
            newSyntaxes << ( syntax.localizedName().isEmpty() ? syntax.name() : syntax.localizedName() );
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
            const Syntax::Document& syntax = availableSyntaxes[ newSyntaxes[ i ] ];
            newPositions[ syntax.name() ] = i;
        }
        
        for ( int i = 0; i < oldSyntaxes.count(); i++ ) {
            const Syntax::Document& syntax = availableSyntaxes[ oldSyntaxes[ i ] ];
            const int row = newPositions.value( syntax.name(), -1 );
            
            if ( row == -1 ) {
                newIndexes[ i ] = QModelIndex();
            }
            else {
                newIndexes[ i ] = model->index( row, 0, QModelIndex() );
            }
        }
        
        model->changePersistentIndexList( oldIndexes, newIndexes );
        emit model->layoutChanged();
        
        if ( IS_HAS_THEME_ICON_THREAD_SAFE ) {
            if ( !mimeTypesIconNamesWatcher ) {
                mimeTypesIconNamesWatcher = new QFutureWatcher<QHash<QString, QString> >( this );
                connect( mimeTypesIconNamesWatcher, SIGNAL( finished() ), this, SLOT( updateIcons() ) );
                mimeTypesIconNamesWatcher->setFuture( QodeEdit::Threading::bestMatchingMimeTypesIcons( mimeTypes, "text/plain" ) );
            }
        }
        else {
            updateIcons( mimeTypes );
        }
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
    
    const Syntax::Document syntax = d->manager->syntax( d->syntaxes.at( index.row() ) );
    
    switch ( role ) {
        case Qt::DecorationRole:
            return QIcon::fromTheme( d->icons.value( syntax.name() ) );
        case Qt::DisplayRole:
        case Qt::ToolTipRole:
        case Syntax::Model::DisplayName:
            return syntax.localizedName().isEmpty() ? syntax.name() : syntax.localizedName();    
        case Syntax::Model::InternalName:
            return syntax.name();
    }
    
    return QVariant();
}

#include "Model.moc"
