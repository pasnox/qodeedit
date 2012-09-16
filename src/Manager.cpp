#include "Manager.h"
#include "QodeEditConfig.h"
#include "Threading.h"
#include "Tools.h"
#include "syntax/Document.h"
#include "syntax/Model.h"
#include "syntax/Highlighter.h"
#include "theme/Theme.h"

#include <QStringList>
#include <QDir>
#include <QDesktopServices>
#include <QMimeDatabase>
#include <QHash>
#include <QPointer>
#include <QFutureWatcher>

class QodeEdit::ManagerData : public QObject {
    Q_OBJECT

public:
    QodeEdit::Manager* manager;
    QString userSharedDataFilePath;
    QMimeDatabase mimeDatabase;
    QHash<QString, Syntax::Document> documents;
    //
    QPointer<QFutureWatcher<QHash<QString, Syntax::Document> > > syntaxesFilesWatcher;
    QPointer<QFutureWatcher<QStringList> > schemasFilesWatcher;
    
    ManagerData( QodeEdit::Manager* _manager )
        : QObject( _manager ),
            manager( _manager )
    {
    }
    
    void initialize() {
        if ( syntaxesFilesWatcher || schemasFilesWatcher ) {
            return;
        }
        
        // update syntaxes
        syntaxesFilesWatcher = new QFutureWatcher<QHash<QString, Syntax::Document> >( this );
        connect( syntaxesFilesWatcher, SIGNAL( finished() ), this, SLOT( syntaxesFilesParsed() ) );
        syntaxesFilesWatcher->setFuture( QodeEdit::Threading::parseSyntaxesFiles( manager->syntaxDefinitionFilePaths() ) );
        
        // update schemas
        /*schemasFilesWatcher = new QFutureWatcher<QStringList>( this );
        connect( syntaxesFilesWatcher, SIGNAL( finished() ), this, SLOT( syntaxesFilesParsed() ) );
        schemasFilesWatcher->setFuture( QodeEdit::Threading::listFilesInPaths( manager->syntaxDefinitionFilePaths(), QStringList( "*.xml" ), true ) );*/
    }

public slots:
    void syntaxesFilesParsed() {
        documents = syntaxesFilesWatcher->future().result();
        syntaxesFilesWatcher->deleteLater();
        emit manager->syntaxesUpdated();
        
        if ( !schemasFilesWatcher ) {
            emit manager->updated();
        }
    }
    
    void schemasFilesParsed() {
        /*schemasFilesWatcher = new QFutureWatcher<QStringList>( this );
        schemasFilesWatcher->deleteLater();
        emit manager->schemasUpdated();
        
        if ( !syntaxesFilesWatcher ) {
            emit manager->updated();
        }*/
    }
};

QodeEdit::Manager::Manager( QObject* parent )
    : QObject( parent ),
        d( new QodeEdit::ManagerData( this ) )
{
}

QodeEdit::Manager::~Manager()
{
    deinitialize();
}

void QodeEdit::Manager::initialize()
{
    d->initialize();
}

void QodeEdit::Manager::deinitialize()
{
    d->documents.clear();
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
    return d->mimeDatabase.mimeTypeForFile( fileName ).name();
}

QString QodeEdit::Manager::mimeTypeForFile( const QFileInfo& fileInfo ) const
{
    return d->mimeDatabase.mimeTypeForFile( fileInfo ).name();
}

QString QodeEdit::Manager::mimeTypeForData( const QByteArray& data ) const
{
    return d->mimeDatabase.mimeTypeForData( data ).name();
}

QString QodeEdit::Manager::mimeTypeForData( QIODevice* device ) const
{
    return d->mimeDatabase.mimeTypeForData( device ).name();
}

QString QodeEdit::Manager::mimeTypeForFileNameAndData( const QString& fileName, QIODevice* device ) const
{
    return d->mimeDatabase.mimeTypeForFileNameAndData( fileName, device ).name();
}

QString QodeEdit::Manager::mimeTypeForFileNameAndData( const QString& fileName, const QByteArray& data ) const
{
    return d->mimeDatabase.mimeTypeForFileNameAndData( fileName, data ).name();
}

QString QodeEdit::Manager::mimeTypeForUrl( const QUrl& url ) const
{
    return d->mimeDatabase.mimeTypeForUrl( url ).name();
}

QStringList QodeEdit::Manager::mimeTypesForFileName( const QString& fileName ) const
{
    const QList<QMimeType> mimeTypes = d->mimeDatabase.mimeTypesForFileName( fileName );
    QStringList names;
    
    for ( int i = 0; i < mimeTypes.count(); i++ ) {
        names << mimeTypes[ i ].name();
    }
    
    return names;
}

QStringList QodeEdit::Manager::availableSyntaxes() const
{
    QStringList syntaxes = d->documents.keys();
    qSort( syntaxes.begin(), syntaxes.end(), QodeEdit::Tools::localeAwareStringLessThan );
    return syntaxes;
}

QHash<QString, Syntax::Document> QodeEdit::Manager::availableDocuments() const
{
    return d->documents;
}

Syntax::Document QodeEdit::Manager::document( const QString& name )
{
    return d->documents.value( name );
}

Syntax::Model* QodeEdit::Manager::model( QObject* parent )
{
    return new Syntax::Model( this, parent );
}

Syntax::Highlighter* QodeEdit::Manager::highlighter( const QString& syntaxName, TextDocument* textDocument ) const
{
    return new Syntax::Highlighter( d->documents.value( syntaxName ), Theme::Schema(), textDocument );
}

Syntax::Highlighter* QodeEdit::Manager::highlighterForFilePath( const QString& filePath, TextDocument* textDocument ) const
{
    QMap<int, Syntax::Document*> documents;
    
    foreach ( const QString& name, d->documents.keys() ) {
        Syntax::Document& document = d->documents[ name ];
        
        if ( QDir::match( document.extensions().toList(), filePath ) ) {
            documents[ document.priority() ] = &document;
        }
    }
    
    if ( documents.isEmpty() ) {
        return QodeEdit::Manager::highlighter( QString::null, textDocument );
    }
    
    return QodeEdit::Manager::highlighter( ( documents.end() -1 ).value()->name(), textDocument );
}

Syntax::Highlighter* QodeEdit::Manager::highlighterForMimeType( const QString& mimeType, TextDocument* textDocument ) const
{
    QMap<int, Syntax::Document*> documents;
    
    foreach ( const QString& name, d->documents.keys() ) {
        Syntax::Document& document = d->documents[ name ];
        
        if ( document.mimeType().contains( mimeType ) ) {
            documents[ document.priority() ] = &document;
        }
    }
    
    if ( documents.isEmpty() ) {
        return QodeEdit::Manager::highlighter( QString::null, textDocument );
    }
    
    return QodeEdit::Manager::highlighter( ( documents.end() -1 ).value()->name(), textDocument );
}

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

#include "Manager.moc"
