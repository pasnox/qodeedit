/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : QodeEdit.cpp
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#include "QodeEdit.h"
#include "QodeEditConfig.h"
#include "Tools.h"
#include "syntax/Document.h"
#include "syntax/Highlighter.h"
#include "theme/Theme.h"

#include <QStringList>
#include <QDir>
#include <QDesktopServices>
#include <QMimeDatabase>
#include <QHash>


/*#include "syntax/DocumentBuilder.h"
#include "syntax/Highlighter.h"
#include "syntax/Model.h"
#include "theme/Theme.h"
#include "editor/TextDocument.h"
#include "Tools.h"

#include <QStringList>
#include <QDir>
#include <QPointer>
#include <QTime>

#include <QDebug>*/

class QodeEdit::ManagerData {
public:
    QString userSharedDataFilePath;
    QMimeDatabase mMimeDatabase;
    QHash<QString, Syntax::Document> mDocuments;
    
    /*
    QList<QPointer<Syntax::Model> > mModels;
    
    
    void updateModels() {
        for ( int i = mModels.count() -1; i >= 0; i-- ) {
            Syntax::Model* model = mModels[ i ];
            
            if ( model ) {
                model->update();
            }
            else {
                mModels.removeAt( i );
            }
        }
    }
    
    Syntax::Document::List documents() {
        return mDocuments.values();
    }*/
};

QodeEdit::Manager::Manager( QObject* parent )
    : QObject( parent ),
        d( new QodeEdit::ManagerData )
{
}

QodeEdit::Manager::~Manager()
{
    delete d;
}

QString QodeEdit::Manager::userSharedDataFilePath( const QString& extended ) const
{
    return d->userSharedDataFilePath.isEmpty()
        ? QDir::cleanPath( QString( "%1/%2/%3" )
            .arg( QDesktopServices::storageLocation( QDesktopServices::DataLocation ) )
            .arg( QString::fromUtf8( PACKAGE_NAME ) )
            .arg( extended ) )
        : d->userSharedDataFilePath
    ;
}

void QodeEdit::Manager::setUserSharedDataFilePath( const QString& filePath )
{
    d->userSharedDataFilePath = filePath;
}

QString QodeEdit::Manager::userSchemaDefinitionFilePath() const
{
    return QodeEdit::Manager::userSharedDataFilePath( "schemas" );
}

QString QodeEdit::Manager::userSyntaxDefinitionFilePath() const
{
    return QodeEdit::Manager::userSharedDataFilePath( "syntax" );
}

QStringList QodeEdit::Manager::schemaDefinitionFilePaths() const
{
    return QStringList()
        << QodeEdit::Manager::schemaDefinitionFilePath()
        << QodeEdit::Manager::userSchemaDefinitionFilePath()
    ;
}

QStringList QodeEdit::Manager::syntaxDefinitionFilePaths() const
{
    return QStringList()
        << QodeEdit::Manager::syntaxDefinitionFilePath()
        << QodeEdit::Manager::userSyntaxDefinitionFilePath()
    ;
}

QString QodeEdit::Manager::mimeTypeForFile( const QString& fileName ) const
{
    return d->mMimeDatabase.mimeTypeForFile( fileName ).name();
}

QString QodeEdit::Manager::mimeTypeForFile( const QFileInfo& fileInfo ) const
{
    return d->mMimeDatabase.mimeTypeForFile( fileInfo ).name();
}

QString QodeEdit::Manager::mimeTypeForData( const QByteArray& data ) const
{
    return d->mMimeDatabase.mimeTypeForData( data ).name();
}

QString QodeEdit::Manager::mimeTypeForData( QIODevice* device ) const
{
    return d->mMimeDatabase.mimeTypeForData( device ).name();
}

QString QodeEdit::Manager::mimeTypeForFileNameAndData( const QString& fileName, QIODevice* device ) const
{
    return d->mMimeDatabase.mimeTypeForFileNameAndData( fileName, device ).name();
}

QString QodeEdit::Manager::mimeTypeForFileNameAndData( const QString& fileName, const QByteArray& data ) const
{
    return d->mMimeDatabase.mimeTypeForFileNameAndData( fileName, data ).name();
}

QString QodeEdit::Manager::mimeTypeForUrl( const QUrl& url ) const
{
    return d->mMimeDatabase.mimeTypeForUrl( url ).name();
}

QStringList QodeEdit::Manager::mimeTypesForFileName( const QString& fileName ) const
{
    const QList<QMimeType> mimeTypes = d->mMimeDatabase.mimeTypesForFileName( fileName );
    QStringList names;
    
    for ( int i = 0; i < mimeTypes.count(); i++ ) {
        names << mimeTypes[ i ].name();
    }
    
    return names;
}

QStringList QodeEdit::Manager::availableSyntaxes() const
{
    QStringList syntaxes = d->mDocuments.keys();
    qSort( syntaxes.begin(), syntaxes.end(), QodeEdit::Tools::localeAwareStringLessThan );
    return syntaxes;
}

Syntax::Highlighter* QodeEdit::Manager::highlighter( const QString& syntaxName, const QString& syntaxThemeName, TextDocument* textDocument ) const
{
    Q_UNUSED( syntaxThemeName );
    #warning update me after having themes factory
    return new Syntax::Highlighter( d->mDocuments.value( syntaxName ), Theme::Schema(), textDocument );
}

Syntax::Highlighter* QodeEdit::Manager::highlighterForFilePath( const QString& filePath, TextDocument* textDocument ) const
{
    QMap<int, Syntax::Document*> documents;
    
    foreach ( const QString& name, d->mDocuments.keys() ) {
        Syntax::Document& document = d->mDocuments[ name ];
        
        if ( QDir::match( document.extensions().toList(), filePath ) ) {
            documents[ document.priority() ] = &document;
        }
    }
    
    if ( documents.isEmpty() ) {
        return 0;
    }
    
    return QodeEdit::Manager::highlighter( ( documents.end() -1 ).value()->name(), QString::null, textDocument );
}

Syntax::Highlighter* QodeEdit::Manager::highlighterForMimeType( const QString& mimeType, TextDocument* textDocument ) const
{
    QMap<int, Syntax::Document*> documents;
    
    foreach ( const QString& name, d->mDocuments.keys() ) {
        Syntax::Document& document = d->mDocuments[ name ];
        
        if ( document.mimeType().contains( mimeType ) ) {
            documents[ document.priority() ] = &document;
        }
    }
    
    if ( documents.isEmpty() ) {
        return 0;
    }
    
    return QodeEdit::Manager::highlighter( ( documents.end() -1 ).value()->name(), QString::null, textDocument );
}










/*bool QodeEdit::Manager::load( QString* _error )
{
#if !defined( QT_NO_DEBUG )
    QTime time;
    time.start();
#endif
    
    const QStringList paths = QodeEdit::syntaxDefinitionFilePaths();
    QFileInfoList filesInfo;
    QStringList files;
    QString error;
    
    foreach ( const QString& path, paths ) {
        filesInfo << QDir( path ).entryInfoList( QStringList( "*.xml" ) );
    }
    
    foreach ( const QFileInfo& file, filesInfo ) {
        files << file.absoluteFilePath();
    }
    
#if !defined( QT_NO_DEBUG )
    qWarning( "%s: Found files in %f seconds", Q_FUNC_INFO , time.elapsed() /1000.0 );
#endif
    
    const QHash<QString, Syntax::Document> documents = Syntax::Document::open( files, &error );
    
#if !defined( QT_NO_DEBUG )
    qWarning( "%s: Parsed files in %f seconds", Q_FUNC_INFO , time.elapsed() /1000.0 );
#endif
    
    if ( _error ) {
        *_error = error;
    }
    
    if ( error.isEmpty() ) {
        d->mDocuments = documents;
        
        Syntax::DocumentBuilder builder;
        builder.buildDocuments( d->mDocuments );
        
#if !defined( QT_NO_DEBUG )
        qWarning( "%s: Build files in %f seconds", Q_FUNC_INFO , time.elapsed() /1000.0 );
#endif
        QodeEdit::Manager::updateModels();
#if !defined( QT_NO_DEBUG )
        qWarning( "%s: Initialized in %f seconds", Q_FUNC_INFO , time.elapsed() /1000.0 );
#endif
        return true;
    }
    
#if !defined( QT_NO_DEBUG )
    qWarning( "%s: Fails in %f seconds", Q_FUNC_INFO , time.elapsed() /1000.0 );
#endif

    return false;
}

void QodeEdit::Manager::free()
{
    d->mDocuments.clear();
}





Syntax::Document QodeEdit::Manager::document( const QString& name )
{
    return d->mDocuments.value( name );
}



Syntax::Model* QodeEdit::Manager::model( QObject* parent )
{
    d->mModels << new Syntax::Model( &d->mDocuments, parent );
    return d->mModels.last();
}*/

const char* QodeEdit::Manager::version()
{
    return PACKAGE_VERSION;
}

QString QodeEdit::Manager::versionString()
{
    return PACKAGE_VERSION;
}

QString QodeEdit::Manager::sharedDataFilePath( const QString& extended )
{
    return QDir::cleanPath( QString( "%1/%2" )
        .arg( QString::fromUtf8( PACKAGE_ABSOLUTE_DATA_DIR ) )
        .arg( extended ) );
}

QString QodeEdit::Manager::schemaDefinitionFilePath()
{
    return QodeEdit::Manager::sharedDataFilePath( "schemas" );
}

QString QodeEdit::Manager::syntaxDefinitionFilePath()
{
    return QodeEdit::Manager::sharedDataFilePath( "syntax" );
}
