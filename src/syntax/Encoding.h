/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : Encoding.h
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#ifndef ENCODING_H
#define ENCODING_H

#include <QExplicitlySharedDataPointer>
#include <QList>
#include <QString>

#include "Helpers.h"

namespace Syntax {

class EncodingData;

class Encoding
{
private:
    QExplicitlySharedDataPointer<Syntax::EncodingData> d;

public:
    typedef QList<Syntax::Encoding> List;

    QE_DECL_SHARED_CLASS( Encoding, Syntax );

    // Required
    QE_DECL_MEMBER( QString, string );
    // Optional
    QE_DECL_MEMBER( QString, char_ );
    QE_DECL_MEMBER( bool, ignored );
};

} // Syntax

#endif // ENCODING_H
