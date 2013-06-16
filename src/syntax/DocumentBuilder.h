/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : DocumentBuilder.h
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#ifndef DOCUMENTBUILDER_H
#define DOCUMENTBUILDER_H

#include <QExplicitlySharedDataPointer>
#include <QHash>

#include "Helpers.h"

namespace Syntax {

class DocumentBuilderData;
class Document;

class DocumentBuilder
{
private:
    QExplicitlySharedDataPointer<Syntax::DocumentBuilderData> d;

public:
    QE_DECL_SHARED_CLASS( DocumentBuilder, Syntax );

    void buildDocuments( const QHash<QString, Syntax::Document>& documents );
};

} //Syntax

#endif // DOCUMENTBUILDER_H
