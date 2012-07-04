#ifndef QODEEDIT_H
#define QODEEDIT_H

#include <QPlainTextEdit>

class QodeEdit : public QPlainTextEdit
{
    Q_OBJECT
    friend class QodeEditPrivate;
    friend class MarginContainerPrivate;

public:
    enum Ruler {
        NoRuler = 0x0,
        LineRuler = 0x1,
        BackgroundRuler = 0x2
    };
    
    QodeEdit( QWidget* parent = 0 );
    virtual ~QodeEdit();
    
    QodeEdit::Ruler rulerMode() const;
    int rulerWidth() const;

public slots:
    void setRulerMode( QodeEdit::Ruler mode );
    void setRulerWidth( int width );

protected:
    class QodeEditPrivate* d;
    
    virtual bool event( QEvent* event );
    virtual void paintEvent( QPaintEvent* event );
};

#endif // QODEEDIT_H
