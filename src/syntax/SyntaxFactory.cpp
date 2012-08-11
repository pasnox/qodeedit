#include "SyntaxFactory.h"
#include "SyntaxHighlighter.h"
#include "SyntaxModel.h"
#include "TextDocument.h"
#include "QodeEdit.h"

#include <QStringList>
#include <QDir>
#include <QPointer>
#include <QTime>
#include <QDebug>

namespace Syntax {
    namespace Factory {
        QHash<QString, Syntax::Document> mDocuments;
        QList<QPointer<Syntax::Model> > mModels;
        
        // forward declare
        void buildDocument( Syntax::Document& document );
        void buildContextRules( Syntax::Document& document, Syntax::Context& context );
        void buildContextRule( Syntax::Document& document, Syntax::Context& context, Syntax::Rule& rule );
        
        void mergeRules( Syntax::Document& document, Syntax::Context& context, Syntax::Rule& rule ) {
            QString srcContextName = rule.context();
            QString srcSyntaxName = document.name();
            
            // import external initial context rules
            if ( srcContextName.startsWith( "##" ) ) {
                srcSyntaxName = srcContextName.mid( 2 );
                srcContextName.clear(); // filled up later with document initialContext
            }
            // import external contex rules
            else if ( srcContextName.contains( "##" ) ) {
                const QStringList parts = srcContextName.split( "##" );
                srcSyntaxName = parts.value( 1 );
                srcContextName = parts.value( 0 );
            }
            // import from current document
            else {
                // nothing to do
            }
            
            // get source document
            Q_ASSERT( Syntax::Factory::mDocuments.contains( srcSyntaxName ) );
            Syntax::Document& srcDocument = Syntax::Factory::mDocuments[ srcSyntaxName ];
            
            // get source context name if needed
            if ( rule.context().startsWith( "##" ) ) {
                srcContextName = srcDocument.highlighting().initialContext();
            }
            
            // get source context
            Q_ASSERT( srcDocument.highlighting().contexts().contains( srcContextName ) );
            Syntax::Context& srcContext = srcDocument.highlighting().contexts()[ srcContextName ];
            
            // make sure the document is built
            if ( srcDocument.name() != document.name() ) {
                buildDocument( srcDocument );
            }
            // make sure the context is ready
            else {
                buildContextRules( srcDocument, srcContext );
            }
            
            // update context attribute
            if ( rule.includeAttrib() ) {
                context.attribute() = srcContext.attribute();
            }
            
            // update rules
            const Syntax::Rule::List& rules = srcContext.rules();
            
            for ( int i = 0; i < rules.count(); i++ ) {
                rule.rules() << rules[ i ];
            }
        }
        
        void buildRuleRule( Syntax::Document& document, Syntax::Context& context, Syntax::Rule& rule ) {
            Q_ASSERT( !rule.type().isEmpty() );
            
            if ( rule.enumType() == Syntax::Rule::IncludeRules ) {
                Syntax::Factory::mergeRules( document, context, rule );
            }
            else {
                Syntax::Rule::List& rules = rule.rules();
                
                for ( int i = rules.count() -1; i >= 0; i-- ) {
                    Syntax::Factory::buildRuleRule( document, context, rules[ i ] );
                }
            }
        }
        
        void buildContextRule( Syntax::Document& document, Syntax::Context& context, Syntax::Rule& rule ) {
            Q_ASSERT( !rule.type().isEmpty() );
            
            if ( rule.enumType() == Syntax::Rule::IncludeRules ) {
                Syntax::Factory::mergeRules( document, context, rule );
            }
            else {
                Syntax::Rule::List& rules = rule.rules();
                
                for ( int i = rules.count() -1; i >= 0; i-- ) {
                    Syntax::Factory::buildRuleRule( document, context, rules[ i ] );
                }
            }
        }
        
        void buildContextRules( Syntax::Document& document, Syntax::Context& context ) {
            if ( document.finalyzed() ) {
                return;
            }
            
            Syntax::Rule::List& rules = context.rules();
            
            for ( int i = rules.count() -1; i >= 0; i-- ) {
                Syntax::Factory::buildContextRule( document, context, rules[ i ] );
            }
        }
        
        void buildDocument( Syntax::Document& document ) {
            if ( document.finalyzed() ) {
                return;
            }
            
            Syntax::Context::Hash& contexts = document.highlighting().contexts();
            
            foreach ( const QString& contextName, contexts.keys() ) {
                buildContextRules( document, contexts[ contextName ] );
            }
            
            document.finalyzed() = true;
        }
        
        void buildDocuments() {
            foreach ( const QString& syntaxName, Syntax::Factory::mDocuments.keys() ) {
                buildDocument( Syntax::Factory::mDocuments[ syntaxName ] );
            }
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
            return Syntax::Factory::mDocuments.value( name );
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
        Syntax::Factory::buildDocuments();
        
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

Syntax::Model* Syntax::Factory::model( QObject* parent )
{
    Syntax::Factory::mModels << new Syntax::Model( &Syntax::Factory::mDocuments, parent );
    return Syntax::Factory::mModels.last();
}
