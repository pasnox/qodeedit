/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : AbstractMargin.h
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#ifndef ABSTRACTMARGIN_H
#define ABSTRACTMARGIN_H

#include <QWidget>

class AbstractMarginPrivate;
class MarginStacker;
class CodeEditor;

class QTextBlock;

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
    QRect blockRect( const QTextBlock& block ) const;
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
    
    virtual void setEditor( CodeEditor* editor );

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
