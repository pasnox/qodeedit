#ifndef SYNTAXDOCUMENT_H
#define SYNTAXDOCUMENT_H

#include <QSet>
#include <QString>

namespace Syntax {

class Language;
class DocumentPrivate;

typedef QSet<QString> List;

class Document
{
public:
    Document( const QString& filePath );
    virtual ~Document();
    
    bool parse() { return false; }

private:
    DocumentPrivate* d;
};

}; // Syntax

#endif // SYNTAXDOCUMENT_H
