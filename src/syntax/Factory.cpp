/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : Factory.cpp
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#include "Factory.h"
#include "Document.h"
#include "DocumentBuilder.h"
#include "Highlighter.h"
#include "Model.h"
#include "theme/Theme.h"
#include "document/TextDocument.h"
#include "Tools.h"

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
{/*
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
        
        Syntax::DocumentBuilder builder;
        builder.buildDocuments( Syntax::Factory::mDocuments );
        
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
#endif*/

    return false;
}

void Syntax::Factory::free()
{
    Syntax::Factory::mDocuments.clear();
}

QStringList Syntax::Factory::availableSyntaxes()
{
    QStringList syntaxes = Syntax::Factory::mDocuments.keys();
    qSort( syntaxes.begin(), syntaxes.end(), QodeEdit::Tools::localeAwareStringLessThan );
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

Syntax::Highlighter* Syntax::Factory::highlighter( const QString& syntaxName, const QString& syntaxThemeName, TextDocument* textDocument )
{
    Q_UNUSED( syntaxThemeName );
    #warning update me after having themes factory
    return new Syntax::Highlighter( Syntax::Factory::document( syntaxName ), Syntax::Theme(), textDocument );
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
    
    return Syntax::Factory::highlighter( ( documents.end() -1 ).value()->name(), QString::null, textDocument );
}

Syntax::Highlighter* Syntax::Factory::highlighterForMimeType( const QString& mimeType, TextDocument* textDocument )
{
    QMap<int, Syntax::Document*> documents;
    
    foreach ( const QString& name, Syntax::Factory::mDocuments.keys() ) {
        Syntax::Document& document = Syntax::Factory::mDocuments[ name ];
        
        if ( document.mimeType().contains( mimeType ) ) {
            documents[ document.priority() ] = &document;
        }
    }
    
    if ( documents.isEmpty() ) {
        return 0;
    }
    
    return Syntax::Factory::highlighter( ( documents.end() -1 ).value()->name(), QString::null, textDocument );
}

Syntax::Model* Syntax::Factory::model( QObject* parent )
{
    Syntax::Factory::mModels << new Syntax::Model( &Syntax::Factory::mDocuments, parent );
    return Syntax::Factory::mModels.last();
}
