#ifndef UIMAIN_H
#define UIMAIN_H

#include <QtGui>

#include "CodeEditor.h"

class Ui_UIMain;

namespace Syntax {
    class Model;
};

class QodeEditor : public CodeEditor
{
    Q_OBJECT

public:
    QodeEditor( QWidget* parent = 0 );

protected slots:
    void save();
};

class UIMain : public QMainWindow
{
    Q_OBJECT

public:
    UIMain( QWidget* parent = 0 );
    virtual ~UIMain();
    
protected:
    Ui_UIMain* ui;
    Syntax::Model* mSyntaxModel;
};

#endif // UIMAIN_H
