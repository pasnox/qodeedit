#ifndef MARGINCONTAINER_H
#define MARGINCONTAINER_H

#include <QWidget>

class QodeEdit;

class MarginContainer : public QWidget
{
    Q_OBJECT
    
public:
    // the order is important as it defined the default presentation order of the margins
    enum Type {
        LineNumber = 0,
        CodeFolding = 1,
        Bookmarks = 2,
        LineChange = 3
    };
    
    MarginContainer( QodeEdit* editor );
    virtual ~MarginContainer();
    
    bool isVisible( MarginContainer::Type type ) const;
    void setVisible( MarginContainer::Type type, bool visible );

private:
    class MarginContainerPrivate* d;
};

#endif // MARGINCONTAINER_H
