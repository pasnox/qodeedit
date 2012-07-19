#ifndef SYNTAXDOCUMENTREADER_H
#define SYNTAXDOCUMENTREADER_H

#include <QXmlSimpleReader>

class SyntaxDocumentReader : public QXmlSimpleReader
{
public:
    SyntaxDocumentReader();
    virtual ~SyntaxDocumentReader();
};

#endif // SYNTAXDOCUMENTREADER_H
