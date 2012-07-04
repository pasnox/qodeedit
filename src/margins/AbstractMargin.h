#ifndef ABSTRACTMARGIN_H
#define ABSTRACTMARGIN_H

#include <QWidget>

class QodeEdit;

class AbstractMargin : public QWidget
{
    Q_OBJECT
    
public:
    AbstractMargin( QodeEdit* editor );
    virtual ~AbstractMargin();
    
    int lineAt( const QPoint& pos ) const;
    QRect lineRect( int line ) const;

protected:
    virtual void mousePressEvent( QMouseEvent* event );
    virtual void mouseDoubleClickEvent( QMouseEvent* event );
    virtual void mouseReleaseEvent( QMouseEvent* event );
    virtual void mouseMoveEvent( QMouseEvent* event );
    virtual void enterEvent( QEvent* event );
    virtual void leaveEvent( QEvent* event );

private:
    class AbstractMarginPrivate* d;

signals:
    void clicked( int line, Qt::MouseButton button, Qt::MouseButtons buttons, Qt::KeyboardModifiers modifiers );
    void doubleClicked( int line, Qt::MouseButton button, Qt::MouseButtons buttons, Qt::KeyboardModifiers modifiers );
    void entered( int line );
    void left( int line );
};

#endif // ABSTRACTMARGIN_H
