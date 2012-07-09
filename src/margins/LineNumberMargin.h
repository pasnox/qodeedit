#ifndef LINENUMBERMARGIN_H
#define LINENUMBERMARGIN_H

#include "AbstractMargin.h"

class LineNumberMargin : public AbstractMargin
{
    Q_OBJECT
    
public:
    LineNumberMargin( MarginStacker* marginStacker );
    virtual ~LineNumberMargin();
    
    virtual void setEditor( QodeEdit* editor );

protected:
    virtual void paintEvent( QPaintEvent* event );

protected slots:
    virtual void updateWidthRequested();
};

#endif // LINENUMBERMARGIN_H
