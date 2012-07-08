#ifndef ABSTRACTMARGIN_H
#define ABSTRACTMARGIN_H

#include <QWidget>

class MarginStacker;
class QodeEdit;

class AbstractMargin : public QWidget
{
    Q_OBJECT
    
public:
    AbstractMargin( MarginStacker* marginStacker );
    virtual ~AbstractMargin();
    
    QodeEdit* editor() const;
    virtual void setEditor( QodeEdit* editor );
    
    MarginStacker* stacker() const;
    
    int lineAt( const QPoint& pos ) const;
    QRect lineRect( int line ) const;
    
    int firstVisibleLine() const;
    int lastVisibleLine() const;

protected:
    virtual bool event( QEvent* event );
    virtual void mousePressEvent( QMouseEvent* event );
    virtual void mouseDoubleClickEvent( QMouseEvent* event );
    virtual void mouseReleaseEvent( QMouseEvent* event );
    virtual void mouseMoveEvent( QMouseEvent* event );
    virtual void enterEvent( QEvent* event );
    virtual void leaveEvent( QEvent* event );

private:
    class Private;
    AbstractMargin::Private* d;

signals:
    void clicked( int line, Qt::MouseButton button, Qt::MouseButtons buttons, Qt::KeyboardModifiers modifiers );
    void doubleClicked( int line, Qt::MouseButton button, Qt::MouseButtons buttons, Qt::KeyboardModifiers modifiers );
    void entered( int line );
    void left( int line );
    void lineCountChanged( int count );
    void fontChanged();
    void resized();
};

#endif // ABSTRACTMARGIN_H
