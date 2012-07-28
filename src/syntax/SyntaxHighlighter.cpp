#include "SyntaxHighlighter.h"
#include "TextDocument.h"

// HighlighterPrivate

class Syntax::HighlighterPrivate {
public:
    Syntax::Document syntaxDocument;
    
    HighlighterPrivate( Syntax::Highlighter* _highlighter, const Syntax::Document& _syntaxDocument )
        : syntaxDocument( _syntaxDocument ),
            highlighter( _highlighter )
    {
        Q_ASSERT( highlighter );
    }

private:
    Syntax::Highlighter* highlighter;
};

// Highlighter

Syntax::Highlighter::Highlighter( const Syntax::Document& syntaxDocument, TextDocument* textDocument )
    : QSyntaxHighlighter( textDocument ),
        d( new Syntax::HighlighterPrivate( this, syntaxDocument ) )
{
}

Syntax::Highlighter::~Highlighter()
{
    delete d;
}

Syntax::Document Syntax::Highlighter::syntaxDocument() const
{
    return d->syntaxDocument;
}

void Syntax::Highlighter::setSyntaxDocument( const Syntax::Document& syntaxDocument )
{
    d->syntaxDocument = syntaxDocument;
    rehighlight();
}

void Syntax::Highlighter::highlightBlock( const QString& text )
{
    Q_UNUSED( text );
}
