/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : Highlighting.h
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#ifndef HIGHLIGHTING_H
#define HIGHLIGHTING_H

#include <QExplicitlySharedDataPointer>

#include "Helpers.h"
#include "List.h"
#include "Context.h"
#include "ItemData.h"

namespace Syntax {

class HighlightingData;

class Highlighting
{
private:
    QExplicitlySharedDataPointer<Syntax::HighlightingData> d;

public:
    QE_DECL_SHARED_CLASS( Highlighting, Syntax );

    // Required
    // Optional
    QE_DECL_MEMBER( Syntax::HashList, lists );
    QE_DECL_MEMBER( Syntax::Context::Hash, contexts );
    QE_DECL_MEMBER( Syntax::ItemData::Hash, itemDatas );
    // Others
    QE_DECL_MEMBER( QString, defaultContextName );

    Syntax::List list( const QString& name ) const;
    Syntax::Context context( const QString& name ) const;
    Syntax::Context defaultContext() const;
};

} // Syntax

#endif // HIGHLIGHTING_H
