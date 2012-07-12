#ifndef LINESTATEMARGIN_H
#define LINESTATEMARGIN_H

#include "AbstractMargin.h"

class LineStateMargin : public AbstractMargin
{
    Q_OBJECT
    
public:
    LineStateMargin( MarginStacker* marginStacker );
    virtual ~LineStateMargin();

    virtual void setEditor( QodeEdit* editor );

protected:
    virtual void paintEvent( QPaintEvent* event );

protected slots:
    virtual void updateWidthRequested();
};

#endif // LINESTATEMARGIN_H
