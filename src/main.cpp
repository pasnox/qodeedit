#include <QtGui>

#include "CodeEditor.h"
#include "MarginStacker.h"

#include "SyntaxDocument.h"

class QodeEditor : public CodeEditor {
    Q_OBJECT

public:
    QodeEditor( QWidget* parent = 0 )
        : CodeEditor( parent )
    {
        // fake save document shortcut
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
    
    QRect rect = QRect( QPoint(), QSize( 640, 480 ) );
    rect.moveCenter( QApplication::desktop()->availableGeometry().center() );
    
    MarginStacker* margins = new MarginStacker;
    margins->setVisible( MarginStacker::LineBookmark, true );
    margins->setVisible( MarginStacker::LineNumber, true );
    margins->setVisible( MarginStacker::LineRevision, true );
    margins->setVisible( MarginStacker::LineFold, true );
    margins->setVisible( MarginStacker::LineSpacing, true );
    
    QodeEditor* editor = new QodeEditor;
    editor->setMarginStacker( margins );
    editor->setGeometry( rect );
    editor->show();
    
    Syntax::Document document;
    qWarning() << document.open( "/home/pasnox/Developpement/C++/Qt5/mks-ng/3rdparty/qodeedit.git/share/syntax/cpp.xml" );
    
    return app.exec();
}

#include "main.moc"
