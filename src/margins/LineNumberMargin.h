#ifndef LINENUMBERMARGIN_H
#define LINENUMBERMARGIN_H

#include "AbstractMargin.h"

class LineNumberMargin : public AbstractMargin
{
    Q_OBJECT
    
public:
    LineNumberMargin( QodeEdit* editor );
    virtual ~LineNumberMargin();

protected:
    virtual void paintEvent( QPaintEvent* event );

protected slots:
    void q_countChanged( int count );
};

#endif // LINENUMBERMARGIN_H
