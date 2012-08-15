#include "SyntaxHighlighter.h"
#include "SyntaxDocument.h"
#include "SyntaxTheme.h"
#include "TextDocument.h"

// HighlighterPrivate

class Syntax::HighlighterPrivate {
public:
    Syntax::Document syntaxDocument;
    Syntax::Theme syntaxTheme;
    
    HighlighterPrivate( Syntax::Highlighter* _highlighter )
        : highlighter( _highlighter )
    {
        Q_ASSERT( highlighter );
    }
    
    TextBlockUserData* testBlockUserData( const QTextBlock& block ) const {
        return highlighter->textDocument()->testUserData( block );
    }

    TextBlockUserData* blockUserData( QTextBlock& block ) const {
        return highlighter->textDocument()->userData( block );
    }

private:
    Syntax::Highlighter* highlighter;
};

// Highlighter

Syntax::Highlighter::Highlighter( const Syntax::Document& syntaxDocument, const Syntax::Theme& syntaxTheme, TextDocument* textDocument )
    : QSyntaxHighlighter( textDocument ),
        d( new Syntax::HighlighterPrivate( this ) )
{
    d->syntaxDocument = syntaxDocument;
    d->syntaxTheme = syntaxTheme;
}

Syntax::Highlighter::Highlighter( TextDocument* textDocument )
    : QSyntaxHighlighter( textDocument ),
        d( new Syntax::HighlighterPrivate( this ) )
{
}

Syntax::Highlighter::~Highlighter()
{
    delete d;
}

TextDocument* Syntax::Highlighter::textDocument() const
{
    return qobject_cast<TextDocument*>( document() );
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

Syntax::Theme Syntax::Highlighter::syntaxTheme() const
{
    return d->syntaxTheme;
}

void Syntax::Highlighter::setSyntaxTheme( const Syntax::Theme& syntaxTheme )
{
    d->syntaxTheme = syntaxTheme;
    rehighlight();
}

void Syntax::Highlighter::highlightBlock( const QString& text )
{
    /*lineData, matchedContexts = self._syntax.parseBlock(text, self._prevData())
    print self._syntax.parseBlockTextualResults(text, self._prevData())
    contextAreaStartPos = 0
    for context, contextLength, matchedRules in matchedContexts:
        self.setFormat(contextAreaStartPos, contextLength, self._theme.getFormat(context.attribute))
        for rule, pos, ruleLength in matchedRules:
            if rule.attribute is not None:
                self.setFormat(pos, ruleLength, self._theme.getFormat(rule.attribute))
        contextAreaStartPos += contextLength
    
    self.setCurrentBlockUserData(_TextBlockUserData(lineData))*/
}

/*TextBlockUserData* testUserData( const QTextBlock& block ) const;
    TextBlockUserData* userData( QTextBlock& block ) const;*/



/*def _prevData(self):
        prevBlock = self.currentBlock().previous()
        if prevBlock.isValid():
            dataObject = prevBlock.userData()
            if dataObject is not None:
                return dataObject.data
        return None*/
