#ifndef SYNTAXITEMDATA_H
#define SYNTAXITEMDATA_H

#include <QHash>
#include <QString>

namespace Syntax {

class ItemData
{
public:
    typedef QHash<QString, ItemData> Hash;
    
    QString name; ///< Name of the item data
    QHash<QString, QString> attributes; ///< Attributes of the item data
    
    ItemData();
    virtual ~ItemData();
};

}; // Syntax

#endif // SYNTAXITEMDATA_H
