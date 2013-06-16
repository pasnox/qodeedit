/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : Model.h
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#ifndef MODEL_H
#define MODEL_H

#include <QAbstractListModel>

namespace QodeEdit {
    class Manager;
}

namespace Syntax {

class ModelPrivate;

class Model : public QAbstractListModel
{
    Q_OBJECT
    friend class Syntax::ModelPrivate;

public:
    enum ExtendedRole {
        InternalName = Qt::UserRole,
        DisplayName
    };

    Model( QodeEdit::Manager* manager, QObject* parent = 0 );
    virtual ~Model();

    virtual int rowCount( const QModelIndex& parent = QModelIndex() ) const;
    virtual QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const;

private:
    Syntax::ModelPrivate* d;
};

} //Syntax

#endif // MODEL_H
