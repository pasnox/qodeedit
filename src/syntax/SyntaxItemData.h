#ifndef SYNTAXITEMDATA_H
#define SYNTAXITEMDATA_H

#include <QHash>
#include <QString>
#include <QColor>

namespace Syntax {

class ItemData
{
public:
    typedef QHash<QString, Syntax::ItemData> Hash;
    
    QString name; ///< Name of the item data
    QString defStyleNum;
    bool spellChecking;
    QColor color;
    QColor selColor;
    bool bold;
    bool italic;
    bool strikeOut;
    bool underline;
    QColor backgroundColor;
    
    ItemData();
    virtual ~ItemData();
};

}; // Syntax

#endif // SYNTAXITEMDATA_H
