#ifndef SYNTAXITEMDATA_H
#define SYNTAXITEMDATA_H

#include <QHash>
#include <QString>

namespace Syntax {

class ItemData
{
public:
    typedef QHash<QString, Syntax::ItemData> Hash;
    
    QString name; ///< Name of the item data
    QString defStyleNum;
    QString spellChecking;
    QString color;
    QString selColor;
    QString bold;
    QString italic;
    
    ItemData();
    virtual ~ItemData();
};

}; // Syntax

#endif // SYNTAXITEMDATA_H
