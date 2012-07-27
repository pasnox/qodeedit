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
    QString ignored;
    
    Encoding();
    virtual ~Encoding();
};

}; // Syntax

#endif // SYNTAXENCODING_H
