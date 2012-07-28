#include "SyntaxFactory.h"
#include "SyntaxHighlighter.h"
#include "SyntaxModel.h"
#include "TextDocument.h"
#include "QodeEdit.h"

#include <QStringList>
#include <QDir>
#include <QPointer>
#include <QDebug>

namespace Syntax {
    namespace Factory {
        QHash<QString, Syntax::Document> mDocuments; // brut parsed document - not to use
        QHash<QString, Syntax::Document> mCachedDocuments; // built document - ready to use
        QList<QPointer<Syntax::Model> > mModels;
        
        Syntax::Document cachedDocument( const QString& name ) {
            Syntax::Document& document = Syntax::Factory::mCachedDocuments[ name ];
            
            if ( document.name.isEmpty() ) {
                // build cached document;
            }
            
            return document;
        }
        
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
        
        Syntax::Document document( const QString& name ) {
            return Syntax::Factory::cachedDocument( name );
        }
    };
};

bool Syntax::Factory::load( QString* _error )
{
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
    
    const QHash<QString, Syntax::Document> documents = Syntax::Document::open( files, &error );
    
    if ( _error ) {
        *_error = error;
    }
    
    if ( error.isEmpty() ) {
        Syntax::Factory::mDocuments = documents;
        Syntax::Factory::mCachedDocuments.clear();
        Syntax::Factory::updateModels();
        return true;
    }
    
    return false;
}

void Syntax::Factory::free()
{
    Syntax::Factory::mDocuments.clear();
    Syntax::Factory::mCachedDocuments.clear();
    Syntax::Factory::updateModels();
}

Syntax::Highlighter* Syntax::Factory::highlighter( const QString& name, TextDocument* textDocument )
{
    return new Syntax::Highlighter( Syntax::Factory::cachedDocument( name ), textDocument );
}

Syntax::Model* Syntax::Factory::model( QObject* parent )
{
    Syntax::Factory::mModels << new Syntax::Model( &Syntax::Factory::mDocuments, parent );
    return Syntax::Factory::mModels.last();
}
