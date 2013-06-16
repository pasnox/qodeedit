/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : Indentation.h
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#ifndef INDENTATION_H
#define INDENTATION_H

#include <QExplicitlySharedDataPointer>
#include <QString>

#include "Helpers.h"

namespace Syntax {

class IndentationData;

class Indentation
{
private:
    QExplicitlySharedDataPointer<Syntax::IndentationData> d;

public:
    QE_DECL_SHARED_CLASS( Indentation, Syntax );

    // Required
    // Optional
    QE_DECL_MEMBER( QString, mode );
};

} // Syntax

#endif // INDENTATION_H
