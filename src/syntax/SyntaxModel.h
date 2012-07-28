#ifndef SYNTAXMODEL_H
#define SYNTAXMODEL_H

#include <QAbstractListModel>

namespace Syntax {

class ModelPrivate;
class Document;

class Model : public QAbstractListModel
{
    Q_OBJECT
    
public:
    enum ExtendedRole {
        InternalName = Qt::UserRole
    };
    
    Model( const QHash<QString, Syntax::Document>* syntaxes, QObject* parent = 0 );
    virtual ~Model();
    
    virtual int rowCount( const QModelIndex& parent = QModelIndex() ) const;
    virtual QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const;
    
    QString internalName( const QModelIndex& index ) const;

public slots:
    void update();

private:
    Syntax::ModelPrivate* d;
};

}; //Syntax

#endif // SYNTAXMODEL_H
