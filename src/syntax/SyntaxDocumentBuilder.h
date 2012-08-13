#ifndef SYNTAXDOCUMENTBUILDER_H
#define SYNTAXDOCUMENTBUILDER_H

#include <QExplicitlySharedDataPointer>
#include <QHash>

#include "SyntaxHelpers.h"

namespace Syntax {

class DocumentBuilderData;
class Document;

class DocumentBuilder
{
private:
    QExplicitlySharedDataPointer<Syntax::DocumentBuilderData> d;
    
public:
    DocumentBuilder( const QHash<QString, Syntax::Document>& documents );
    DocumentBuilder( const Syntax::DocumentBuilder& other );
    virtual ~DocumentBuilder();
    
    SYNTAX_DECL_OPERATORS( DocumentBuilder );
    
    void buildDocuments();
};

}; //Syntax

#endif // SYNTAXDOCUMENTBUILDER_H
