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
    QE_DECL_SHARED_CLASS( DocumentBuilder );
    
    void buildDocuments( const QHash<QString, Syntax::Document>& documents );
};

}; //Syntax

#endif // SYNTAXDOCUMENTBUILDER_H
