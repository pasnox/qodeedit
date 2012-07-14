#ifndef LINEREVISIONMARGIN_H
#define LINEREVISIONMARGIN_H

#include "AbstractMargin.h"

class LineRevisionMargin : public AbstractMargin
{
    Q_OBJECT
    
public:
    LineRevisionMargin( MarginStacker* marginStacker );
    virtual ~LineRevisionMargin();

    virtual void setEditor( QodeEdit* editor );

protected:
    virtual void paintEvent( QPaintEvent* event );

protected slots:
    virtual void updateWidthRequested();
};

#endif // LINEREVISIONMARGIN_H
