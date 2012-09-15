/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : ComboBox.cpp
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#include "ComboBox.h"
#include "Model.h"

Syntax::ComboBox::ComboBox( QWidget* parent )
    : QComboBox( parent )
{
    setSizeAdjustPolicy( QComboBox::AdjustToContents );
}

Syntax::ComboBox::~ComboBox()
{
}

QString Syntax::ComboBox::currentSyntax() const
{
    return itemData( currentIndex(), Syntax::Model::InternalName ).toString();
}

void Syntax::ComboBox::setCurrentSyntax( const QString& name )
{
    setCurrentIndex( findData( name, Syntax::Model::InternalName ) );
}
