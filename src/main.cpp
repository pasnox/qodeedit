#include <QtGui>

#include "QodeEdit.h"
#include "MarginStacker.h"

class QodeEditor : public QodeEdit {
    Q_OBJECT

public:
    QodeEditor( QWidget* parent = 0 )
        : QodeEdit( parent )
    {
        new QShortcut( QKeySequence::Save, this, SLOT( save() ) );
    }

protected slots:
    void save() {
        document()->setModified( false );
    }
};

int main( int argc, char** argv )
{
    QApplication app( argc, argv );
    
    QodeEditor* editor = new QodeEditor;
    MarginStacker* margins = new MarginStacker( editor );
    
    margins->setVisible( MarginStacker::LineBookmark, true );
    margins->setVisible( MarginStacker::LineNumber, true );
    margins->setVisible( MarginStacker::LineRevision, true );
    margins->setVisible( MarginStacker::Spacing, true );
    
    //editor->setMarginStacker( margins );
    editor->resize( 640, 480 );
    
    QRect r = QRect( QPoint(), editor->size() );
    r.moveCenter( QApplication::desktop()->availableGeometry().center() );
    
    editor->move( r.topLeft() );
    
    editor->show();
    
    return app.exec();
}

#include "main.moc"
