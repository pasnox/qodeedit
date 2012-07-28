#include "UIMain.h"
#include "ui_UIMain.h"
#include "CodeEditor.h"
#include "MarginStacker.h"
#include "SyntaxFactory.h"
#include "SyntaxModel.h"

// QodeEditor

QodeEditor::QodeEditor( QWidget* parent )
    : CodeEditor( parent )
{
    MarginStacker* margins = new MarginStacker( this );
    margins->setVisible( MarginStacker::LineBookmark, true );
    margins->setVisible( MarginStacker::LineNumber, true );
    margins->setVisible( MarginStacker::LineRevision, true );
    margins->setVisible( MarginStacker::LineFold, true );
    margins->setVisible( MarginStacker::LineSpacing, true );
    
    // fake save document shortcut
    new QShortcut( QKeySequence::Save, this, SLOT( save() ) );
}

void QodeEditor::save()
{
    document()->setModified( false );
}

// SpacerWidget

class SpacerWidget : public QWidget {
public:
    SpacerWidget( QWidget* parent = 0 )
        : QWidget( parent )
    {
        setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Minimum );
    }
};

// UIMain

UIMain::UIMain( QWidget* parent )
    : QMainWindow( parent ), ui( new Ui_UIMain ),
        mSyntaxModel( Syntax::Factory::model( this ) )
{
    ui->setupUi( this );
    ui->cbSyntax->setModel( mSyntaxModel );
    ui->toolBar->addWidget( new SpacerWidget( this ) );
    ui->toolBar->addWidget( ui->cbSyntax );
    
    QString error;
    
    if ( Syntax::Factory::load( &error ) ) {
        error = "Syntaxes loaded correctly";
    }
    
    ui->qeEdit->setText( error );
}

UIMain::~UIMain()
{
    delete ui;
}
