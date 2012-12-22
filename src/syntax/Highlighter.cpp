/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : Highlighter.cpp
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#include "Highlighter.h"
#include "Document.h"
#include "theme/Theme.h"
#include "editor/TextDocument.h"

// HighlighterPrivate

class Syntax::HighlighterPrivate {
public:
    Syntax::Document syntaxDocument;
    Theme::Schema themeSchema;
    
    HighlighterPrivate( Syntax::Highlighter* _highlighter )
        : highlighter( _highlighter )
    {
        Q_ASSERT( highlighter );
        
        if ( highlighter->textDocument() ) {
            highlighter->textDocument()->setSyntaxHighlighter( highlighter );
        }
    }
    
    TextBlockUserData* testBlockUserData( const QTextBlock& block ) const {
        return highlighter->textDocument()->testUserData( block );
    }

    TextBlockUserData* blockUserData( QTextBlock& block ) const {
        return highlighter->textDocument()->userData( block );
    }
    
    TextBlockUserData* previousblockData() {
        const QTextBlock block = highlighter->currentBlock().previous();
        return testBlockUserData( block );
    }

private:
    Syntax::Highlighter* highlighter;
};

// Highlighter

Syntax::Highlighter::Highlighter( const Syntax::Document& syntaxDocument, const Theme::Schema& themeSchema, TextDocument* textDocument )
    : QSyntaxHighlighter( textDocument ),
        d( new Syntax::HighlighterPrivate( this ) )
{
    d->syntaxDocument = syntaxDocument;
    d->themeSchema = themeSchema;
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

Theme::Schema Syntax::Highlighter::themeSchema() const
{
    return d->themeSchema;
}

void Syntax::Highlighter::setSyntaxTheme( const Theme::Schema& themeSchema )
{
    d->themeSchema = themeSchema;
    rehighlight();
}

void Syntax::Highlighter::highlightBlock( const QString& text )
{
    TextBlockUserData* previousData = d->previousblockData();
    
    
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
