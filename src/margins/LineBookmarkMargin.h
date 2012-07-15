#ifndef LINEBOOKMARKMARGIN_H
#define LINEBOOKMARKMARGIN_H

#include "AbstractMargin.h"

class LineBookmarkMarginPrivate;

class LineBookmarkMargin : public AbstractMargin
{
    Q_OBJECT
    friend class LineBookmarkMarginPrivate;
    
public:
    LineBookmarkMargin( MarginStacker* marginStacker );
    virtual ~LineBookmarkMargin();

protected:
    virtual void paintEvent( QPaintEvent* event );

protected slots:
    virtual void updateWidthRequested();

private:
    LineBookmarkMarginPrivate* d;
};

#endif // LINEBOOKMARKMARGIN_H
