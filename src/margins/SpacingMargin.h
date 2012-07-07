#ifndef SPACINGMARGIN_H
#define SPACINGMARGIN_H

#include "AbstractMargin.h"

class SpacingMargin : public AbstractMargin
{
    Q_OBJECT
    
public:
    SpacingMargin( MarginStacker* marginStacker );
    virtual ~SpacingMargin();
    
protected:
    virtual void paintEvent( QPaintEvent* event );
};

#endif // SPACINGMARGIN_H
