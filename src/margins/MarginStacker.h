#ifndef MARGINSTACKER_H
#define MARGINSTACKER_H

#include <QWidget>

class MarginStackerPrivate;
class AbstractMargin;
class CodeEditor;

class MarginStacker : public QWidget
{
    Q_OBJECT
    friend class MarginStackerPrivate;
    
public:
    // the order is important as it defined the presentation order of the margins
    enum Type {
        Invalid = -1,
        LineBookmarking = 0, // done
        LineNumbering = 1, // done
        LineFolding = 2,
        LineRevisioning = 3, // done
        LineSpacing = 4, // done
    };
    
    MarginStacker( CodeEditor* editor = 0 );
    virtual ~MarginStacker();
    
    AbstractMargin* margin( MarginStacker::Type type ) const;
    
    CodeEditor* editor() const;
    void setEditor( CodeEditor* editor );
    
    bool isVisible( MarginStacker::Type type ) const;
    void setVisible( MarginStacker::Type type, bool visible = true );
    
public slots:
    void updateLayout();

protected:
    virtual bool eventFilter( QObject* object, QEvent* event );

private:
    MarginStackerPrivate* d;
};

#endif // MARGINSTACKER_H
