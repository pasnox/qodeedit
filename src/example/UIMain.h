#ifndef UIMAIN_H
#define UIMAIN_H

#include <QtGui>

#include "CodeEditor.h"

class Ui_UIMain;

class QodeEditor : public CodeEditor
{
    Q_OBJECT

public:
    QodeEditor( QWidget* parent = 0 );
    
    static QString fileContent( const QString& filePath, const QByteArray& textCodec = QByteArray( "UTF-8" ) );

protected slots:
    void save();
};

Q_DECLARE_METATYPE( QodeEditor* )

class UIMain : public QMainWindow
{
    Q_OBJECT

public:
    UIMain( QWidget* parent = 0 );
    virtual ~UIMain();
    
protected:
    Ui_UIMain* ui;
    QHash<QString, QodeEditor*> mEditors;
    
    QodeEditor* editor( int row ) const;
    
protected slots:
    void on_lwEditors_currentRowChanged( int row );
    void on_swEditors_currentChanged( int row );
};

#endif // UIMAIN_H
