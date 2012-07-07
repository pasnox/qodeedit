#include <QtGui>

#include "QodeEdit.h"
#include "MarginStacker.h"

int main( int argc, char** argv )
{
    QApplication app( argc, argv );
    
    QodeEdit* editor = new QodeEdit;
    MarginStacker* margins = new MarginStacker( editor );
    
    margins->setVisible( MarginStacker::LineNumber, true );
    margins->setVisible( MarginStacker::Spacing, true );
    
    //editor->setMarginStacker( margins );
    editor->resize( 640, 480 );
    
    QRect r = QRect( QPoint(), editor->size() );
    r.moveCenter( QApplication::desktop()->availableGeometry().center() );
    
    editor->move( r.topLeft() );
    
    editor->show();
    
    return app.exec();
}
