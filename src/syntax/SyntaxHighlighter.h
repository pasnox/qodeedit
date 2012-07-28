#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>

#include "SyntaxDocument.h"

class TextDocument;

namespace Syntax {

class HighlighterPrivate;

class Highlighter : public QSyntaxHighlighter
{
public:
    Highlighter( const Syntax::Document& syntaxDocument, TextDocument* textDocument );
    virtual ~Highlighter();
    
    Syntax::Document syntaxDocument() const;
    void setSyntaxDocument( const Syntax::Document& syntaxDocument );

protected:
    virtual void highlightBlock( const QString& text );

private:
    Syntax::HighlighterPrivate* d;
};

}; // Syntax

#endif // SYNTAXHIGHLIGHTER_H
