/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : UIMain.cpp
** Date      : 2012-09-02T23:04:12
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#include "UIMain.h"
#include "ui_UIMain.h"
#include "editor/CodeEditor.h"
#include "editor/TextDocument.h"
#include "margin/MarginStacker.h"
#include "syntax/Highlighter.h"
#include "syntax/Model.h"
#include "syntax/Document.h"
#include "QodeEdit.h"
#include "Manager.h"
#include "Tools.h"
#include "Threading.h"

static QMutex qMutex;
static UIMain* qMain = 0;

// QodeEditor

QodeEditor::QodeEditor( QWidget* parent )
    : CodeEditor( parent )
{
    setCaretLineBackground( QColor( 150, 150, 150, 150 ) );
    
    MarginStacker* margins = new MarginStacker( this );
    margins->setVisible( QodeEdit::BookmarkMargin, true );
    margins->setVisible( QodeEdit::NumberMargin, true );
    margins->setVisible( QodeEdit::RevisionMargin, true );
    margins->setVisible( QodeEdit::FoldMargin, true );
    margins->setVisible( QodeEdit::SpaceMargin, true );
    
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
    : QMainWindow( parent ),
        ui( new Ui_UIMain ),
        mManager( new QodeEdit::Manager( this ) )
{
    {
        QMutexLocker locker( &qMutex );
        
        if ( !qMain ) {
            qMain = this;
        }
    }
    
    ui->setupUi( this );
    ui->cbSyntax->setModel( mManager->model() );
    ui->toolBar->addWidget( new SpacerWidget( this ) );
    ui->toolBar->addWidget( ui->cbSyntax );
    
    qInstallMsgHandler( UIMain::messageHandler );
    connect( mManager, SIGNAL( updated() ), this, SLOT( manager_updated() ) );
    
    mManager->initialize();
    
#if !defined( QT_NO_DEBUG )
    //debug();
#endif
}

UIMain::~UIMain()
{
    {
        QMutexLocker locker( &qMutex );
        
        if ( qMain == this ) {
            qMain = 0;
        }
    }
    
    delete ui;
}

void UIMain::messageHandler( QtMsgType type, const char* msg )
{
    QMutexLocker locker( &qMutex );
    QString string;
    
    switch ( type ) {
        case QtDebugMsg:
            string = QString( "Debug: %1" ).arg( msg );
            break;
        case QtWarningMsg:
            string = QString( "Warning: %1" ).arg( msg );
            break;
        case QtCriticalMsg:
            string = QString( "Critical: %1" ).arg( msg );
            break;
        case QtFatalMsg:
            string = QString( "Fatal: %1" ).arg( msg );
            break;
    }
    
    QMetaObject::invokeMethod( qMain, "appendDebugMessage", Qt::QueuedConnection, Q_ARG( const QString&, string ) );
    
    if ( type == QtFatalMsg ) {
        abort();
    }
}

void UIMain::appendDebugMessage( const QString& message )
{
    ui->pteDebug->appendPlainText( message );
    printf( "%s\n", qPrintable( message ) );
}

QodeEditor* UIMain::editor( int row ) const
{
    QListWidgetItem* item = ui->lwEditors->item( row );
    
    if ( !item ) {
        Q_ASSERT( item );
        return 0;
    }
    
    return item->data( Qt::UserRole ).value<QodeEditor*>();
}

void UIMain::debug()
{
    qWarning() << mManager->availableSyntaxesList();
    qWarning() << mManager->availableSchemasList();
    
    qWarning() << mManager->mimeTypeForFile( "toto.h" );
    qWarning() << mManager->mimeTypeForFile( "toto.c" );
    qWarning() << mManager->mimeTypeForFile( "toto.cpp" );
    qWarning() << mManager->mimeTypeForFile( "toto.adb" );
    
    qWarning() << mManager->mimeTypeForData( "#include <iostream>\n" );
    qWarning() << mManager->mimeTypeForData( "#include <stdlib.h>\n" );
    qWarning() << mManager->mimeTypeForData( "#import <stdlib.h>\n" );
    
    qWarning() << mManager->mimeTypeForUrl( QUrl( "http://toto.com/test.html" ) );
    qWarning() << mManager->mimeTypeForUrl( QUrl( "http://toto.com/test.pdf" ) );
    qWarning() << mManager->mimeTypeForUrl( QUrl( "http://toto.com/test.jpg" ) );
    
    qWarning() << mManager->mimeTypesForFileName( "toto.h" );
    qWarning() << mManager->mimeTypesForFileName( "toto.c" );
    qWarning() << mManager->mimeTypesForFileName( "toto.cpp" );
    qWarning() << mManager->mimeTypesForFileName( "toto.adb" );
    
    qWarning() << QodeEdit::Tools::rulerToString( QodeEdit::NoRuler );
    qWarning() << QodeEdit::Tools::rulerToString( QodeEdit::BackgroundRuler );
    qWarning() << QodeEdit::Tools::stringToRuler( "background" );
    qWarning() << QodeEdit::Tools::stringToRuler( "backgroundRuler" );
    qWarning() << QodeEdit::Tools::stringToRuler( "Background" );
}

void UIMain::on_lwEditors_currentRowChanged( int row )
{
    if ( ui->swEditors->currentIndex() != row ) {
        ui->swEditors->setCurrentIndex( row );
    }
}

void UIMain::on_swEditors_currentChanged( int row )
{
    if ( ui->lwEditors->currentRow() != row ) {
        ui->lwEditors->setCurrentRow( row );
    }
    
    ui->cbSyntax->setCurrentSyntax( editor( row )->textDocument()->syntaxHighlighter()->syntaxDocument().name() );
}

void UIMain::listFilesFinished()
{
    const QStringList files = mListFilesWatcher->result();
    mListFilesWatcher->deleteLater();
    
    if ( !mOpenFilesWatcher ) {
        mOpenFilesWatcher = new QFutureWatcher<QHash<QString, QPair<QString, QString> > >( this );
        connect( mOpenFilesWatcher, SIGNAL( finished() ), this, SLOT( openFilesFinished() ) );
        mOpenFilesWatcher->setFuture( QodeEdit::Threading::getFilesContentWithTextCodec( files, "UTF-8" ) );
    }
}

void UIMain::openFilesFinished()
{
    const QHash<QString, QPair<QString, QString> > contents = mOpenFilesWatcher->result();
    mOpenFilesWatcher->deleteLater();
    
    foreach ( const QString& filePath, contents.keys() ) {
        const QPair<QString, QString>& pair = contents[ filePath ];
        
        // File opened
        if ( pair.second.isEmpty() ) {
            QodeEditor* editor = new QodeEditor( this );
            Syntax::Highlighter* highlighter = mManager->highlighterForFilePath( filePath );
            
            editor->setInitialText( pair.first );
            editor->textDocument()->setSyntaxHighlighter( highlighter );
            
            QListWidgetItem* item = new QListWidgetItem( ui->lwEditors );
            item->setText( QString( "%1 (%2)" ).arg( QFileInfo( filePath ).fileName() ).arg( highlighter->syntaxDocument().name() ) );
            item->setData( Qt::UserRole, QVariant::fromValue( editor ) );
            ui->swEditors->addWidget( editor );
        }
        // An error occurs
        else {
            qWarning() << pair.second;
        }
        
        #warning better use a progressive QtConcurrent way
        QApplication::processEvents();
    }
}

void UIMain::manager_updated()
{
    statusBar()->showMessage( tr( "QodeEdit ready." ) );
    
    if ( ui->swEditors->count() > 0 ) {
        return;
    }
    
    if ( !mListFilesWatcher ) {
        const QString path = mManager->sharedDataFilePath( "/tests/hl" );
        
        mListFilesWatcher = new QFutureWatcher<QStringList>( this );
        connect( mListFilesWatcher, SIGNAL( finished() ), this, SLOT( listFilesFinished() ) );
        mListFilesWatcher->setFuture( QodeEdit::Threading::listFilesInPaths( QStringList( path ), QStringList(), true ) );
    }
}
