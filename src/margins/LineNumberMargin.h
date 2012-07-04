#ifndef LINENUMBERMARGIN_H
#define LINENUMBERMARGIN_H

#include "AbstractMargin.h"

class LineNumberMargin : public AbstractMargin
{
    Q_OBJECT
    
public:
    LineNumberMargin( QodeEdit* editor );
    virtual ~LineNumberMargin();
    
    virtual QSize minimumSizeHint() const;

protected:
    virtual void paintEvent( QPaintEvent* event );

protected slots:
    void q_clicked( int line, Qt::MouseButton button, Qt::MouseButtons buttons, Qt::KeyboardModifiers modifiers );
    void q_doubleClicked( int line, Qt::MouseButton button, Qt::MouseButtons buttons, Qt::KeyboardModifiers modifiers );
    void q_entered( int line );
    void q_left( int line );
};

#endif // LINENUMBERMARGIN_H
