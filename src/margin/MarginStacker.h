/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : MarginStacker.h
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
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
