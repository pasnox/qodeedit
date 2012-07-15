#ifndef LINESPACINGMARGIN_H
#define LINESPACINGMARGIN_H

#include "AbstractMargin.h"

class LineSpacingMargin : public AbstractMargin
{
    Q_OBJECT
    
public:
    LineSpacingMargin( MarginStacker* marginStacker );
    virtual ~LineSpacingMargin();
    
protected:
    virtual void paintEvent( QPaintEvent* event );

protected slots:
    virtual void updateWidthRequested();
};

#endif // LINESPACINGMARGIN_H
