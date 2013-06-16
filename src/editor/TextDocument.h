/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : TextDocument.h
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#ifndef TEXTDOCUMENT_H
#define TEXTDOCUMENT_H

#include <QTextDocument>

class TextDocumentPrivate;
class PlainTextDocumentLayout;
class TextBlockUserData;

namespace Syntax {
    class Highlighter;
}

class TextDocument : public QTextDocument
{
    Q_OBJECT
    friend class TextDocumentPrivate;

public:
    TextDocument( QObject* parent = 0 );
    virtual ~TextDocument();

    QTextBlock findBlockByContainsPosition(int position);

    PlainTextDocumentLayout* layout() const;
    void setLayout( PlainTextDocumentLayout* layout );

    Syntax::Highlighter* syntaxHighlighter() const;
    void setSyntaxHighlighter( Syntax::Highlighter* highlighter );

    TextBlockUserData* testUserData( const QTextBlock& block ) const;
    TextBlockUserData* userData( QTextBlock& block ) const;

    QString text() const;
    void setText( const QString& text );

    void setInitialText( const QString& text );

    int lastUnmodifiedRevision() const;

private:
    TextDocumentPrivate* d;
};

#endif // TEXTDOCUMENT_H
