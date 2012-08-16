#ifndef SYNTAXLIST_H
#define SYNTAXLIST_H

#include <QSet>
#include <QHash>
#include <QString>

namespace Syntax {

typedef QSet<QString> List;
typedef QHash<QString, Syntax::List> HashList;

}; // Syntax

#endif // SYNTAXLIST_H
