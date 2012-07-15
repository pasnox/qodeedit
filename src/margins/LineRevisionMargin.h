#ifndef LINEREVISIONMARGIN_H
#define LINEREVISIONMARGIN_H

#include "AbstractMargin.h"

class LineRevisionMargin : public AbstractMargin
{
    Q_OBJECT
    
public:
    LineRevisionMargin( MarginStacker* marginStacker );
    virtual ~LineRevisionMargin();

protected:
    virtual void paintEvent( QPaintEvent* event );
    virtual void setEditor( CodeEditor* editor );

protected slots:
    virtual void updateWidthRequested();
};

#endif // LINEREVISIONMARGIN_H
