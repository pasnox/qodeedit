#ifndef TEXTBLOCKUSERDATA_H
#define TEXTBLOCKUSERDATA_H

#include <QTextBlockUserData>

class TextBlockUserData : public QTextBlockUserData
{
public:
    bool hasBookmark;
    
    TextBlockUserData();
    virtual ~TextBlockUserData();
};

#endif // TEXTBLOCKUSERDATA_H
