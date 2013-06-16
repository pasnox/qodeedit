/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : ItemData.h
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#ifndef ITEMDATA_H
#define ITEMDATA_H

#include <QExplicitlySharedDataPointer>
#include <QHash>
#include <QString>
#include <QColor>

#include "Helpers.h"

namespace Syntax {

class ItemDataData;

class ItemData
{
private:
    QExplicitlySharedDataPointer<Syntax::ItemDataData> d;

public:
    typedef QHash<QString, Syntax::ItemData> Hash;

    QE_DECL_SHARED_CLASS( ItemData, Syntax );

    // Required
    QE_DECL_MEMBER( QString, name ); ///< Name of the item data
    QE_DECL_MEMBER( QString, defStyleNum );
    // optional
    QE_DECL_MEMBER( QColor, color );
    QE_DECL_MEMBER( QColor, selColor );
    QE_DECL_MEMBER( bool, italic );
    QE_DECL_MEMBER( bool, bold );
    QE_DECL_MEMBER( bool, underline );
    QE_DECL_MEMBER( bool, strikeOut );
    QE_DECL_MEMBER( QColor, backgroundColor );
    QE_DECL_MEMBER( QColor, selBackgroundColor );
    QE_DECL_MEMBER( bool, spellChecking );
};

} // Syntax

#endif // ITEMDATA_H
