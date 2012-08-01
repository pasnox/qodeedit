#include <QtGui>

#include "UIMain.h"

int main( int argc, char** argv )
{
    QApplication app( argc, argv );
    
    QRect rect = QRect( QPoint(), QSize( 640, 480 ) );
    rect.moveCenter( QApplication::desktop()->availableGeometry().center() );
    
    UIMain window;
    window.setGeometry( rect );
    window.showMaximized();
    
    return app.exec();
}
