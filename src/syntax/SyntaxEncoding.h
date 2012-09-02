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
    
    QE_DECL_SHARED_CLASS( Encoding );
    
    // Required
    QE_DECL_MEMBER( QString, string );
    // Optional
    QE_DECL_MEMBER( QString, char_ );
    QE_DECL_MEMBER( bool, ignored );
};

}; // Syntax

#endif // SYNTAXENCODING_H
