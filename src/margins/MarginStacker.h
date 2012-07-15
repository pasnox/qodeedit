#ifndef MARGINSTACKER_H
#define MARGINSTACKER_H

#include <QWidget>

class MarginStackerPrivate;
class CodeEditor;

class MarginStacker : public QWidget
{
    Q_OBJECT
    friend class MarginStackerPrivate;
    
public:
    // the order is important as it defined the presentation order of the margins
    enum Type {
        Invalid = -1,
        LineBookmark = 0, // done
        LineNumber = 1, // done
        LineFold = 2,
        LineRevision = 3, // done
        LineSpacing = 4, // done
    };
    
    MarginStacker( CodeEditor* editor = 0 );
    virtual ~MarginStacker();
    
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
