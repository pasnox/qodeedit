#ifndef SYNTAXRULE_H
#define SYNTAXRULE_H

#include <QList>
#include <QHash>
#include <QString>

namespace Syntax {

class Rule
{
public:
    typedef QList<Syntax::Rule> List;
    
    QString type; ///< Type of the rule
    QString attribute;
    QString context;
    QString string;
    QString beginRegion;
    QString firstNonSpace;
    QString char_;
    QString lookAhead;
    QString endRegion;
    QString insensitive;
    QString char1;
    QString column;
    Syntax::Rule::List rules;
    
    Rule();
    virtual ~Rule();
};

}; // Syntax

#endif // SYNTAXRULE_H
