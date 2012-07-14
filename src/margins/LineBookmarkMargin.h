#ifndef LINEBOOKMARKMARGIN_H
#define LINEBOOKMARKMARGIN_H

#include "AbstractMargin.h"

class LineBookmarkMargin : public AbstractMargin
{
    Q_OBJECT
    
public:
    LineBookmarkMargin( MarginStacker* marginStacker );
    virtual ~LineBookmarkMargin();

protected:
    virtual void paintEvent( QPaintEvent* event );

protected slots:
    virtual void updateWidthRequested();
    void mouseDoubleClicked( int line, Qt::MouseButton button, Qt::MouseButtons buttons, Qt::KeyboardModifiers modifiers );
};

#endif // LINEBOOKMARKMARGIN_H
