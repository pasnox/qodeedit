/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : Keywords.h
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#ifndef KEYWORDS_H
#define KEYWORDS_H

#include <QExplicitlySharedDataPointer>
#include <QString>

#include "Helpers.h"

namespace Syntax {

class KeywordsData;

class Keywords
{
private:
    QExplicitlySharedDataPointer<Syntax::KeywordsData> d;

public:
    QE_DECL_SHARED_CLASS( Keywords, Syntax );

    // Required
    // Optional
    QE_DECL_MEMBER( bool, caseSensitive );
    QE_DECL_MEMBER( QString, weakDeliminator );
    QE_DECL_MEMBER( QString, additionalDeliminator );
    QE_DECL_MEMBER( QString, wordWrapDeliminator );
};

} // Syntax

#endif // KEYWORDS_H
