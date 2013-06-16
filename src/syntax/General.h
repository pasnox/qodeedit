/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : General.h
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#ifndef GENERAL_H
#define GENERAL_H

#include <QExplicitlySharedDataPointer>

#include "Helpers.h"
#include "Comment.h"
#include "Keywords.h"
#include "Folding.h"
#include "EmptyLine.h"
#include "Indentation.h"

namespace Syntax {

class GeneralData;

class General
{
private:
    QExplicitlySharedDataPointer<Syntax::GeneralData> d;

public:
    QE_DECL_SHARED_CLASS( General, Syntax );

    QE_DECL_MEMBER( Syntax::Folding, folding );
    QE_DECL_MEMBER( Syntax::Comment::List, comments );
    QE_DECL_MEMBER( Syntax::Keywords, keywords );
    QE_DECL_MEMBER( Syntax::Indentation, indentation );
    QE_DECL_MEMBER( Syntax::EmptyLine::List, emptyLines );
};

} // Syntax

#endif // GENERAL_H
