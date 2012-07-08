#ifndef QODEEDITTEXTDOCUMENT_H
#define QODEEDITTEXTDOCUMENT_H

#include <QTextDocument>

class QodeEditTextDocument : public QTextDocument
{
    Q_OBJECT
    
public:
    QodeEditTextDocument( QObject* parent = 0 );
    virtual ~QodeEditTextDocument();
};

#endif // QODEEDITTEXTDOCUMENT_H
