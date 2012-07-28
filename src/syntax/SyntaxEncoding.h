#ifndef SYNTAXENCODING_H
#define SYNTAXENCODING_H

#include <QList>
#include <QString>

namespace Syntax {

class Encoding
{
public:
    typedef QList<Syntax::Encoding> List;
    
    QString char_;
    QString string;
    bool ignored;
    
    Encoding();
    virtual ~Encoding();
    
    virtual bool operator==( const Syntax::Encoding& other ) const;
    virtual bool operator!=( const Syntax::Encoding& other ) const;
};

}; // Syntax

#endif // SYNTAXENCODING_H
