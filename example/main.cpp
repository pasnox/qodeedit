/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : main.cpp
** Date      : 2012-09-02T23:04:12
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#include <QtGui>
#include <QDesktopWidget>
#include "QodeEditExampleConfig.h"
#include "UIMain.h"

int main( int argc, char** argv )
{
    QApplication app( argc, argv );
    
#if defined( Q_OS_MAC ) || defined( Q_OS_WIN )
    const QFileInfo themes( QString::fromUtf8( QICON_THEMES_PATH ) );
    
    if ( themes.exists() ) {
        QStringList paths = QIcon::themeSearchPaths();
        paths << themes.absoluteFilePath();
        QIcon::setThemeSearchPaths( paths );
        QIcon::setThemeName( "oxygen" );
    }
#endif
    
    QRect rect = QRect( QPoint(), QSize( 640, 480 ) );
    rect.moveCenter( QApplication::desktop()->availableGeometry().center() );
    
    UIMain window;
    window.setGeometry( rect );
    window.showMaximized();
    window.raise();
    
    return app.exec();
}
