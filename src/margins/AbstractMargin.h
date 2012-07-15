#ifndef ABSTRACTMARGIN_H
#define ABSTRACTMARGIN_H

#include <QWidget>

class AbstractMarginPrivate;
class MarginStacker;
class CodeEditor;

class AbstractMargin : public QWidget
{
    Q_OBJECT
    friend class AbstractMarginPrivate;
    friend class MarginStacker;
    friend class MarginStackerPrivate;
    
public:
    AbstractMargin( MarginStacker* marginStacker );
    virtual ~AbstractMargin();
    
    CodeEditor* editor() const;
    MarginStacker* stacker() const;
    
    int lineAt( const QPoint& pos ) const;
    QRect lineRect( int line ) const;
    
    int firstVisibleLine( const QRect& rect = QRect() ) const;
    int lastVisibleLine( const QRect& rect = QRect() ) const;

public slots:
    void updateLineRect( int line );

protected:
    virtual bool event( QEvent* event );
    virtual void mousePressEvent( QMouseEvent* event );
    virtual void mouseDoubleClickEvent( QMouseEvent* event );
    virtual void mouseReleaseEvent( QMouseEvent* event );
    virtual void mouseMoveEvent( QMouseEvent* event );
    virtual void enterEvent( QEvent* event );
    virtual void leaveEvent( QEvent* event );
    
    void setEditor( CodeEditor* editor );

protected slots:
    virtual void updateWidthRequested() = 0;

private:
    AbstractMarginPrivate* d;

signals:
    void mouseClicked( int line, Qt::MouseButton button, Qt::MouseButtons buttons, Qt::KeyboardModifiers modifiers );
    void mouseDoubleClicked( int line, Qt::MouseButton button, Qt::MouseButtons buttons, Qt::KeyboardModifiers modifiers );
    void mouseEntered( int line );
    void mouseLeft( int line );
    void lineCountChanged( int count );
    void fontChanged();
    void resized();
};

#endif // ABSTRACTMARGIN_H
