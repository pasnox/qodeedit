#ifndef QODEEDIT_H
#define QODEEDIT_H

#include <QPlainTextEdit>

class MarginStacker;

class QodeEdit : public QPlainTextEdit
{
    Q_OBJECT
    friend class MarginStacker;

public:
    enum Ruler {
        NoRuler = 0x0,
        LineRuler = 0x1,
        BackgroundRuler = 0x2
    };
    
    QodeEdit( QWidget* parent = 0 );
    virtual ~QodeEdit();
    
    MarginStacker* marginStacker() const;
    void setMarginStacker( MarginStacker* marginStacker );
    
    QString text() const;
    
    QPoint cursorPosition() const;
    int currentLine() const;
    int currentColumn() const;
    QodeEdit::Ruler rulerMode() const;
    int rulerWidth() const;
    
    QBrush paper() const;
    QBrush pen() const;
    QBrush selectionBackground() const;
    QBrush selectionForeground() const;
    QBrush caretLineBackground() const;
    QBrush caretLineForeground() const;
    
    QRect lineRect( int line ) const;

public slots:
    void setInitialText( const QString& text );
    void setText( const QString& text );
    
    void setCursorPosition( const QPoint& pos );
    void setCurrentLine( int line );
    void setCurrentColumn( int column );
    void setRulerMode( QodeEdit::Ruler mode );
    void setRulerWidth( int width );
    
    void setPaper( const QBrush& brush );
    void setPen( const QBrush& brush );
    void setSelectionBackground( const QBrush& brush );
    void setSelectionForeground( const QBrush& brush );
    void setCaretLineBackground( const QBrush& brush );
    void setCaretLineForeground( const QBrush& brush );

protected:
    class Private;
    QodeEdit::Private* d;
    
    virtual bool event( QEvent* event );
    virtual void paintEvent( QPaintEvent* event );
};

#endif // QODEEDIT_H
