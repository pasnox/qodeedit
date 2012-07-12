#ifndef QODEEDITUSERDATA_H
#define QODEEDITUSERDATA_H

#include <QTextBlockUserData>
#include <QSet>

class QodeEditUserData : public QTextBlockUserData
{
public:
    enum State {
        Default = 0, // White/transparent
        Modified = 1, // red
        Saved = 2 // green
    };
    
    QodeEditUserData();
    virtual ~QodeEditUserData();

public:
    bool modified;
    QSet<int> savedRevision;
};

#endif // QODEEDITUSERDATA_H
