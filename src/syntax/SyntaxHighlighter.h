#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

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

#endif // SYNTAXHIGHLIGHTER_H
