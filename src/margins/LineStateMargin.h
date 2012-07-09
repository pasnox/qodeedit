#ifndef LINESTATEMARGIN_H
#define LINESTATEMARGIN_H

#include "AbstractMargin.h"

class LineStateMargin : public AbstractMargin
{
    Q_OBJECT
    
public:
    enum State {
        Normal = 0,
        Modified = 1,
        ModifiedAndSaved = 2
    };
    
    LineStateMargin( MarginStacker* marginStacker );
    virtual ~LineStateMargin();

    virtual void setEditor( QodeEdit* editor );

protected:
    virtual void paintEvent( QPaintEvent* event );

protected slots:
    virtual void updateWidthRequested();

private:
    class Private;
    LineStateMargin::Private* d;
};

#endif // LINESTATEMARGIN_H
