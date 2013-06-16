/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : Context.h
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#ifndef CONTEXT_H
#define CONTEXT_H

#include <QExplicitlySharedDataPointer>
#include <QHash>
#include <QString>

#include "Rule.h"

namespace Syntax {

class ContextData;

class Context
{
private:
    QExplicitlySharedDataPointer<Syntax::ContextData> d;

public:
    typedef QHash<QString, Syntax::Context> Hash;
    typedef QList<Syntax::Context> List;

    QE_DECL_SHARED_CLASS( Context, Syntax );

    // Required
    QE_DECL_MEMBER( QString, attribute );
    QE_DECL_MEMBER( QString, lineEndContext );
    // Optional
    QE_DECL_MEMBER( QString, name ); ///< Name of the context
    QE_DECL_MEMBER( QString, lineBeginContext );
    QE_DECL_MEMBER( bool, fallThrough );
    QE_DECL_MEMBER( QString, fallThroughContext );
    QE_DECL_MEMBER( bool, dynamic );
    QE_DECL_MEMBER( bool, noIndentationBasedFolding );
    // Others
    QE_DECL_MEMBER( Syntax::Rule::List, rules ); ///< Rules of the context

    bool isNull() const;
};

} // Syntax

#endif // CONTEXT_H
