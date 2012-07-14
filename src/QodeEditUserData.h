#ifndef QODEEDITUSERDATA_H
#define QODEEDITUSERDATA_H

#include <QTextBlockUserData>
#include <QSet>

class QodeEditUserData : public QTextBlockUserData
{
public:
    QodeEditUserData();
    virtual ~QodeEditUserData();

public:
    bool hasBookmark;
};

#endif // QODEEDITUSERDATA_H
