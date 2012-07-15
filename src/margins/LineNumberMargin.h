#ifndef LINENUMBERMARGIN_H
#define LINENUMBERMARGIN_H

#include "AbstractMargin.h"

class LineNumberMargin : public AbstractMargin
{
    Q_OBJECT
    
public:
    LineNumberMargin( MarginStacker* marginStacker );
    virtual ~LineNumberMargin();

protected:
    virtual void paintEvent( QPaintEvent* event );
    virtual void setEditor( CodeEditor* editor );

protected slots:
    virtual void updateWidthRequested();
};

#endif // LINENUMBERMARGIN_H
