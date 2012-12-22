/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : UIMain.h
** Date      : 2012-09-02T23:04:12
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#ifndef UIMAIN_H
#define UIMAIN_H

#include <QtGui>

#include "CodeEditor.h"

class Ui_UIMain;

namespace QodeEdit {
    class Manager;
};

class QodeEditor : public CodeEditor
{
    Q_OBJECT

public:
    QodeEditor( QWidget* parent = 0 );
    
    static QString fileContent( const QString& filePath, const QByteArray& textCodec = QByteArray( "UTF-8" ) );

protected slots:
    void save();
    void test();
};

Q_DECLARE_METATYPE( QodeEditor* )

class UIMain : public QMainWindow
{
    Q_OBJECT

public:
    UIMain( QWidget* parent = 0 );
    virtual ~UIMain();
    
    static void messageHandler( QtMsgType type, const char* msg );
    
public slots:
    void appendDebugMessage( const QString& message );
    void listFilesFinished();
    void openFilesFinished();
    
protected:
    Ui_UIMain* ui;
    QodeEdit::Manager* mManager;
    QHash<QString, QodeEditor*> mEditors;
    QPointer<QFutureWatcher<QStringList> > mListFilesWatcher;
    QPointer<QFutureWatcher<QHash<QString, QPair<QString, QString> > > > mOpenFilesWatcher;
    
    QodeEditor* editor( int row ) const;
    
    void debug();
    
protected slots:
    void on_lwEditors_currentRowChanged( int row );
    void on_swEditors_currentChanged( int row );
    void manager_updated();
};

#endif // UIMAIN_H
