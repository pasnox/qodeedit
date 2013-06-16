/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : SpellChecking.h
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#ifndef SPELLCHECKING_H
#define SPELLCHECKING_H

#include <QExplicitlySharedDataPointer>

#include "Helpers.h"
#include "Configuration.h"
#include "Encoding.h"

namespace Syntax {

class SpellCheckingData;

class SpellChecking
{
private:
    QExplicitlySharedDataPointer<Syntax::SpellCheckingData> d;

public:
    QE_DECL_SHARED_CLASS( SpellChecking, Syntax );

    // Required
    // Optional
    QE_DECL_MEMBER( Syntax::Configuration, configuration );
    QE_DECL_MEMBER( Syntax::Encoding::List, encodings );
};

} // Syntax

#endif // SPELLCHECKING_H
