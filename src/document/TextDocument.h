#ifndef TEXTDOCUMENT_H
#define TEXTDOCUMENT_H

#include <QTextDocument>

class TextDocumentPrivate;
class PlainTextDocumentLayout;
class TextBlockUserData;

class TextDocument : public QTextDocument
{
    Q_OBJECT
    friend class TextDocumentPrivate;
    
public:
    TextDocument( QObject* parent = 0 );
    virtual ~TextDocument();
    
    PlainTextDocumentLayout* layout() const;
    void setLayout( PlainTextDocumentLayout* layout );
    
    TextBlockUserData* userData( const QTextBlock& block ) const;
    TextBlockUserData* userData( QTextBlock& block ) const;
    
    QString text() const;
    void setText( const QString& text );
    
    void setInitialText( const QString& text );
    
    int lastUnmodifiedRevision() const;

private:
    TextDocumentPrivate* d;
};

#endif // TEXTDOCUMENT_H
