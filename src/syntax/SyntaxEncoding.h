#ifndef SYNTAXENCODING_H
#define SYNTAXENCODING_H

#include <QExplicitlySharedDataPointer>
#include <QList>
#include <QString>

#include "SyntaxHelpers.h"

namespace Syntax {

class EncodingData;

class Encoding
{
private:
    QExplicitlySharedDataPointer<Syntax::EncodingData> d;
    
public:
    typedef QList<Syntax::Encoding> List;
    
    SYNTAX_DECL_MEMBER( QString, char_ );
    SYNTAX_DECL_MEMBER( QString, string );
    SYNTAX_DECL_MEMBER( bool, ignored );
    
    Encoding();
    Encoding( const Syntax::Encoding& other );
    virtual ~Encoding();
    
    SYNTAX_DECL_OPERATORS( Encoding );
};

}; // Syntax

#endif // SYNTAXENCODING_H
