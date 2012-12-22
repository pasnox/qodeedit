/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : TextDocument.cpp
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#include "TextDocument.h"
#include "PlainTextDocumentLayout.h"
#include "TextBlockUserData.h"
#include "syntax/Highlighter.h"

#include <QTextBlock>
#include <QDebug>

// TextDocumentPrivate

class TextDocumentPrivate : public QObject {
    Q_OBJECT

public:
    Syntax::Highlighter* highlighter;
    int lastUnmodifiedRevision;
    
    TextDocumentPrivate( TextDocument* _document )
        : QObject( _document ),
            highlighter( 0 ),
            lastUnmodifiedRevision( 0 ),
            document( _document )
    {
        Q_ASSERT( document );
        
        connect( document, SIGNAL( modificationChanged( bool ) ), this, SLOT( modificationChanged( bool ) ) );
        connect( document, SIGNAL( contentsChange( int, int, int ) ), this, SLOT( contentsChange( int, int, int ) ) );
    }

public slots:
    void contentsChange( int position, int charsRemoved, int charsAdded ) {
        const bool modified = charsRemoved || charsAdded;
        
        if ( !modified ) {
            return;
        }
        
        QTextBlock block = document->findBlock( position );

        if ( block.isValid() ) {
            if ( block.revision() < 0 ) {
                block.setRevision( -block.revision() -1 );
            }
        }
    }

    void modificationChanged( bool changed ) {
        if ( changed ) {
            return;
        }

        const int oldLastUnmodifiedRevision = lastUnmodifiedRevision;
        lastUnmodifiedRevision = document->revision();

        if ( oldLastUnmodifiedRevision != lastUnmodifiedRevision ) {
            QTextBlock block = document->begin();
            
            while ( block.isValid() ) {
                if ( block.revision() < 0 || block.revision() != oldLastUnmodifiedRevision ) {
                    block.setRevision( -lastUnmodifiedRevision -1 );
                }
                else {
                    block.setRevision( lastUnmodifiedRevision );
                }
                
                block = block.next();
            }
        }
    }

private:
    TextDocument* document;
};

// TextDocument

TextDocument::TextDocument( QObject* parent )
    : QTextDocument( parent ),
        d( new TextDocumentPrivate( this ) )
{
    setLayout( new PlainTextDocumentLayout( this ) );
    setDocumentMargin( 0 );
    setDefaultFont( QFont( "Courier New", 10 ) );
}

TextDocument::~TextDocument()
{
}

QTextBlock TextDocument::findBlockByContainsPosition(int position)
{
    int counter = 0;
    for(int k = 0; k != this->blockCount(); k++) {
        QTextBlock current = findBlockByNumber(k);
        counter += current.length();
        if(counter > position)
            return current;
    }
    return firstBlock();
}

PlainTextDocumentLayout* TextDocument::layout() const
{
    return qobject_cast<PlainTextDocumentLayout*>( documentLayout() );
}

void TextDocument::setLayout( PlainTextDocumentLayout* layout )
{
    setDocumentLayout( layout );
}

Syntax::Highlighter* TextDocument::syntaxHighlighter() const
{
    return d->highlighter;
}

void TextDocument::setSyntaxHighlighter( Syntax::Highlighter* highlighter )
{
    if ( d->highlighter == highlighter ) {
        return;
    }
    
    if ( d->highlighter ) {
        d->highlighter->deleteLater();
    }
    
    d->highlighter = highlighter;
    
    if ( d->highlighter ) {
        d->highlighter->setDocument( this );
    }
}

TextBlockUserData* TextDocument::testUserData( const QTextBlock& block ) const
{
    return static_cast<TextBlockUserData*>( block.isValid() ? block.userData() : 0 );
}

TextBlockUserData* TextDocument::userData( QTextBlock& block ) const
{
    TextBlockUserData* data = static_cast<TextBlockUserData*>( block.isValid() ? block.userData() : 0 );
    
    if ( !data && block.isValid() ) {
        data = new TextBlockUserData;
        block.setUserData( data );
    }
    
    return data;
}

QString TextDocument::text() const
{
    return toPlainText();
}

void TextDocument::setText( const QString& text )
{
    //#warning TODO: Do asynchrone document loading
    QTextCursor cursor( this );
    
    cursor.beginEditBlock();
    cursor.select( QTextCursor::Document );
    cursor.insertText( text );
    cursor.endEditBlock();
}

void TextDocument::setInitialText( const QString& text )
{
    //#warning TODO: Do asynchrone document loading
    setPlainText( text );
    
    d->lastUnmodifiedRevision = revision();
    QTextBlock block = begin();
    
    while ( block.isValid() ) {
        block.setRevision( d->lastUnmodifiedRevision );
        block = block.next();
    }
}

int TextDocument::lastUnmodifiedRevision() const
{
    return d->lastUnmodifiedRevision;
}

#include "TextDocument.moc"
