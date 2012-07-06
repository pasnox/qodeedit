#ifndef QODEEDIT_H
#define QODEEDIT_H

#include <QPlainTextEdit>

class MarginContainer;

class QodeEdit : public QPlainTextEdit
{
    Q_OBJECT
    friend class QodeEditPrivate;
    friend class MarginContainerPrivate;
    friend class AbstractMarginPrivate;
    friend class AbstractMargin;

public:
    enum Ruler {
        NoRuler = 0x0,
        LineRuler = 0x1,
        BackgroundRuler = 0x2
    };
    
    QodeEdit( QWidget* parent = 0 );
    virtual ~QodeEdit();
    
    MarginContainer* marginContainer() const;
    
    QodeEdit::Ruler rulerMode() const;
    int rulerWidth() const;
    
    QPoint cursorPosition() const;

public slots:
    void setRulerMode( QodeEdit::Ruler mode );
    void setRulerWidth( int width );

protected:
    class QodeEditPrivate* d;
    
    virtual bool event( QEvent* event );
    virtual void paintEvent( QPaintEvent* event );
};

#endif // QODEEDIT_H
