#ifndef PLAINTEXTDOCUMENTLAYOUT_H
#define PLAINTEXTDOCUMENTLAYOUT_H

#include <QPlainTextDocumentLayout>

class TextDocument;

class PlainTextDocumentLayout : public QPlainTextDocumentLayout
{
    Q_OBJECT
    
public:
    PlainTextDocumentLayout( TextDocument* document );
    virtual ~PlainTextDocumentLayout();
};

#endif // PLAINTEXTDOCUMENTLAYOUT_H
