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
        
        void mergeRules( Syntax::Document& document, Syntax::Context& context, Syntax::Rule::List& list, Syntax::Rule& rule ) {
            QString srcContextName = rule.context;
            QString srcSyntaxName = document.name;
            
            // import external initial context rules
            if ( rule.context.startsWith( "##" ) ) {
                srcSyntaxName = rule.context.mid( 2 );
                srcContextName.clear(); // fill up later with document initialContext
            }
            // import external contex rules
            else if ( rule.context.contains( "##" ) ) {
                const QStringList parts = rule.context.split( "##" );
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
            if ( rule.context.startsWith( "##" ) ) {
                srcContextName = srcDocument.highlighting.initialContext;
            }
            
            // get source context
            Q_ASSERT( srcDocument.highlighting.contexts.contains( srcContextName ) );
            Syntax::Context& srcContext = srcDocument.highlighting.contexts[ srcContextName ];
            
            // make sure the document is built
            if ( srcDocument.name != document.name ) {
                buildDocument( srcDocument );
            }
            // make sure the context is ready
            else {
                buildContextRules( srcDocument, srcContext );
            }
            
            // update context attribute
            if ( rule.includeAttrib ) {
                context.attribute = srcContext.attribute;
            }
            
            // update rules
            const Syntax::Rule::List& rules = srcContext.rules;
            const int index = list.indexOf( rule );
            
            list.removeAt( index );
            
            for ( int i = rules.count() -1; i >= 0; i-- ) {
                list.insert( index,  rules[ i ] );
            }
        }
        
        void buildRuleRule( Syntax::Document& document, Syntax::Context& context, Syntax::Rule& parentRule, Syntax::Rule& rule ) {
            Q_ASSERT( !rule.type.isEmpty() );
            
            if ( rule.enumType() == Syntax::Rule::IncludeRules ) {
                Syntax::Factory::mergeRules( document, context, parentRule.rules, rule );
            }
            else {
                for ( int i = rule.rules.count() -1; i >= 0; i-- ) {
                    Syntax::Factory::buildRuleRule( document, context, rule, rule.rules[ i ] );
                }
            }
        }
        
        void buildContextRule( Syntax::Document& document, Syntax::Context& context, Syntax::Rule& rule ) {
            Q_ASSERT( !rule.type.isEmpty() );
            
            if ( rule.enumType() == Syntax::Rule::IncludeRules ) {
                Syntax::Factory::mergeRules( document, context, context.rules, rule );
            }
            else {
                for ( int i = rule.rules.count() -1; i >= 0; i-- ) {
                    Syntax::Factory::buildRuleRule( document, context, rule, rule.rules[ i ] );
                }
            }
        }
        
        void buildContextRules( Syntax::Document& document, Syntax::Context& context ) {
            if ( document.finalyzed ) {
                return;
            }
            
            for ( int i = context.rules.count() -1; i >= 0; i-- ) {
                Syntax::Factory::buildContextRule( document, context, context.rules[ i ] );
            }
        }
        
        void buildDocument( Syntax::Document& document ) {
            if ( document.finalyzed ) {
                return;
            }
            
            foreach ( const QString& contextName, document.highlighting.contexts.keys() ) {
                buildContextRules( document, document.highlighting.contexts[ contextName ] );
            }
            
            document.finalyzed = true;
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

Syntax::Highlighter* Syntax::Factory::highlighter( const QString& name, TextDocument* textDocument )
{
    return new Syntax::Highlighter( Syntax::Factory::document( name ), textDocument );
}

Syntax::Model* Syntax::Factory::model( QObject* parent )
{
    Syntax::Factory::mModels << new Syntax::Model( &Syntax::Factory::mDocuments, parent );
    return Syntax::Factory::mModels.last();
}
