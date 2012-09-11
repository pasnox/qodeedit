/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : SyntaxFolding.h
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#ifndef SYNTAXFOLDING_H
#define SYNTAXFOLDING_H

#include <QExplicitlySharedDataPointer>
#include <QString>

#include "SyntaxHelpers.h"

namespace Syntax {

class FoldingData;

class Folding
{
private:
    QExplicitlySharedDataPointer<Syntax::FoldingData> d;
    
public:
    QE_DECL_SHARED_CLASS( Folding );
    
    // Required
    // optional
    QE_DECL_MEMBER( bool, indentationSensitive );
};

}; // Syntax

#endif // SYNTAXFOLDING_H
