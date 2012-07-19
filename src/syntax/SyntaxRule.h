#ifndef SYNTAXRULE_H
#define SYNTAXRULE_H

#include <QList>
#include <QHash>
#include <QString>

namespace Syntax {

class Rule
{
public:
    typedef QList<Rule> List;
    
    QString name; ///< Name of the rule
    QHash<QString, QString> attributes; ///< Attributes of the rule
    Syntax::Rule::List rules;
    
    Rule();
    virtual ~Rule();
};

}; // Syntax

#endif // SYNTAXRULE_H
