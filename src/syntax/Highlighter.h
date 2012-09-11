/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : Highlighter.h
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QSyntaxHighlighter>

class TextDocument;

namespace Syntax {

class HighlighterPrivate;
class Document;
class Theme;

class Highlighter : public QSyntaxHighlighter
{
public:
    Highlighter( const Syntax::Document& syntaxDocument, const Syntax::Theme& syntaxTheme, TextDocument* textDocument );
    Highlighter( TextDocument* textDocument );
    virtual ~Highlighter();
    
    TextDocument* textDocument() const;
    
    Syntax::Document syntaxDocument() const;
    void setSyntaxDocument( const Syntax::Document& syntaxDocument );
    
    Syntax::Theme syntaxTheme() const;
    void setSyntaxTheme( const Syntax::Theme& syntaxTheme );

protected:
    virtual void highlightBlock( const QString& text );

private:
    Syntax::HighlighterPrivate* d;
};

}; // Syntax

#endif // HIGHLIGHTER_H
