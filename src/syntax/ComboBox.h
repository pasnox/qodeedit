/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : ComboBox.h
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <QComboBox>

namespace Syntax {

class ComboBox : public QComboBox
{
    Q_OBJECT

public:
    ComboBox( QWidget* parent = 0 );
    virtual ~ComboBox();

    QString currentSyntax() const;

public slots:
    void setCurrentSyntax( const QString& name );
};

} // Syntax

#endif // COMBOBOX_H
