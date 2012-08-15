#ifndef MARGINSTACKER_H
#define MARGINSTACKER_H

#include <QWidget>

#include "QodeEdit.h"

class MarginStackerPrivate;
class AbstractMargin;
class CodeEditor;

class MarginStacker : public QWidget
{
    Q_OBJECT
    friend class MarginStackerPrivate;
    
public:
    MarginStacker( CodeEditor* editor = 0 );
    virtual ~MarginStacker();
    
    AbstractMargin* margin( QodeEdit::Margin type ) const;
    
    CodeEditor* editor() const;
    void setEditor( CodeEditor* editor );
    
    bool isVisible( QodeEdit::Margin type ) const;
    void setVisible( QodeEdit::Margin type, bool visible = true );
    
public slots:
    void updateLayout();

protected:
    virtual bool eventFilter( QObject* object, QEvent* event );

private:
    MarginStackerPrivate* d;
};

#endif // MARGINSTACKER_H
