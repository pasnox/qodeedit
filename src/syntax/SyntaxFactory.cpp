#include "SyntaxFactory.h"
#include "SyntaxDocumentBuilder.h"
#include "SyntaxHighlighter.h"
#include "SyntaxModel.h"
#include "TextDocument.h"
#include "QodeEdit.h"

#include <QStringList>
#include <QDir>
#include <QPointer>
#include <QTime>
#include <QMimeDatabase>
#include <QDebug>

namespace Syntax {
    namespace Factory {
        QHash<QString, Syntax::Document> mDocuments;
        QList<QPointer<Syntax::Model> > mModels;
        QMimeDatabase mMimeDatabase;
        
        void updateModels() {
            for ( int i = Syntax::Factory::mModels.count() -1; i >= 0; i-- ) {
                Syntax::Model* model = Syntax::Factory::mModels[ i ];
                
                if ( model ) {
                    model->update();
                }
                else {
                    Syntax::Factory::mModels.removeAt( i );
                }
            }
        }
        
        Syntax::Document::List documents() {
            return Syntax::Factory::mDocuments.values();
        }
    };
};

bool Syntax::Factory::load( QString* _error )
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
        Syntax::Factory::mDocuments = documents;
        
        Syntax::DocumentBuilder builder( Syntax::Factory::mDocuments );
        builder.buildDocuments();
        
#if !defined( QT_NO_DEBUG )
        qWarning( "%s: Build files in %f seconds", Q_FUNC_INFO , time.elapsed() /1000.0 );
#endif
        Syntax::Factory::updateModels();
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

void Syntax::Factory::free()
{
    Syntax::Factory::mDocuments.clear();
}

QStringList Syntax::Factory::availableSyntaxes()
{
    QStringList syntaxes = Syntax::Factory::mDocuments.keys();
    qSort( syntaxes.begin(), syntaxes.end(), QodeEdit::localeAwareStringLessThan );
    return syntaxes;
}

QString Syntax::Factory::mimeTypeForFile( const QString& fileName )
{
    return mMimeDatabase.mimeTypeForFile( fileName ).name();
}

QString Syntax::Factory::mimeTypeForFile( const QFileInfo& fileInfo )
{
    return mMimeDatabase.mimeTypeForFile( fileInfo ).name();
}

QString Syntax::Factory::mimeTypeForData( const QByteArray& data )
{
    return mMimeDatabase.mimeTypeForData( data ).name();
}

QString Syntax::Factory::mimeTypeForData( QIODevice* device )
{
    return mMimeDatabase.mimeTypeForData( device ).name();
}

QString Syntax::Factory::mimeTypeForFileNameAndData( const QString& fileName, QIODevice* device )
{
    return mMimeDatabase.mimeTypeForFileNameAndData( fileName, device ).name();
}

QString Syntax::Factory::mimeTypeForFileNameAndData( const QString& fileName, const QByteArray& data )
{
    return mMimeDatabase.mimeTypeForFileNameAndData( fileName, data ).name();
}

QString Syntax::Factory::mimeTypeForUrl( const QUrl& url )
{
    return mMimeDatabase.mimeTypeForUrl( url ).name();
}

QStringList Syntax::Factory::mimeTypesForFileName( const QString& fileName )
{
    const QList<QMimeType> mimeTypes = mMimeDatabase.mimeTypesForFileName( fileName );
    QStringList names;
    
    for ( int i = 0; i < mimeTypes.count(); i++ ) {
        names << mimeTypes[ i ].name();
    }
    
    return names;
}

Syntax::Document Syntax::Factory::document( const QString& name )
{
    return Syntax::Factory::mDocuments.value( name );
}

Syntax::Highlighter* Syntax::Factory::highlighter( const QString& name, TextDocument* textDocument )
{
    return new Syntax::Highlighter( Syntax::Factory::document( name ), textDocument );
}

Syntax::Highlighter* Syntax::Factory::highlighterForFilePath( const QString& filePath, TextDocument* textDocument )
{
    QMap<int, Syntax::Document*> documents;
    
    foreach ( const QString& name, Syntax::Factory::mDocuments.keys() ) {
        Syntax::Document& document = Syntax::Factory::mDocuments[ name ];
        
        if ( QDir::match( document.extensions().toList(), filePath ) ) {
            documents[ document.priority() ] = &document;
        }
    }
    
    if ( documents.isEmpty() ) {
        return 0;
    }
    
    return Syntax::Factory::highlighter( ( documents.end() -1 ).value()->name(), textDocument );
}

Syntax::Highlighter* Syntax::Factory::highlighterForMimeType( const QString& mimeType, TextDocument* textDocument )
{
    QMap<int, Syntax::Document*> documents;
    
    foreach ( const QString& name, Syntax::Factory::mDocuments.keys() ) {
        Syntax::Document& document = Syntax::Factory::mDocuments[ name ];
        
        if ( document.mimeTypes().contains( mimeType ) ) {
            documents[ document.priority() ] = &document;
        }
    }
    
    if ( documents.isEmpty() ) {
        return 0;
    }
    
    return Syntax::Factory::highlighter( ( documents.end() -1 ).value()->name(), textDocument );
}

Syntax::Model* Syntax::Factory::model( QObject* parent )
{
    Syntax::Factory::mModels << new Syntax::Model( &Syntax::Factory::mDocuments, parent );
    return Syntax::Factory::mModels.last();
}
