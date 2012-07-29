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
        void buildContextRule( Syntax::Document& document, Syntax::Context& context, Syntax::Rule& rule );
        
        Syntax::Rule::List copyRules( Syntax::Document& document, Syntax::Rule& rule ) {
            Syntax::Rule::List rules;
            
            // import external rules
            if ( rule.context.startsWith( "##" ) ) {
                qWarning( "%s: Importing external rules is not yet handled (%s/%s)", Q_FUNC_INFO, qPrintable( document.name ), qPrintable( rule.context ) );
            }
            // import external contex rules
            else if ( rule.context.contains( "##" ) ) {
                const QStringList contextParts = rule.context.split( "##" );
                const QString contextName = contextParts.first();
                const QString syntaxName = contextParts.last();
                Q_ASSERT( !contextName.isEmpty() );
                Q_ASSERT( !syntaxName.isEmpty() );
                Q_ASSERT( Syntax::Factory::mDocuments.contains( syntaxName ) );
                Syntax::Document& externalDocument = Syntax::Factory::mDocuments[ syntaxName ];
                Syntax::Context::Hash& externalContexts = externalDocument.highlighting.contexts;
                Q_ASSERT( externalContexts.contains( contextName ) );
                Syntax::Context& externalContext = externalContexts[ contextName ];
                
                // make sure the copying context has already been built
                for ( int i = externalContext.rules.count() -1; i >= 0; i-- ) {
                    Syntax::Factory::buildContextRule( externalDocument, externalContext, externalContext.rules[ i ] );
                }
                
                // final rules to send
                rules = externalContext.rules;
            }
            // import internal context rules
            else {
                Syntax::Context::Hash& contexts = document.highlighting.contexts;
                Q_ASSERT( contexts.contains( rule.context ) );
                Syntax::Context& context = contexts[ rule.context ];
                
                // make sure the copying context has already been built
                for ( int i = context.rules.count() -1; i >= 0; i-- ) {
                    Syntax::Factory::buildContextRule( document, context, context.rules[ i ] );
                }
                
                // final rules to send
                rules = context.rules;
            }
            
            return rules;
        }
        
        void buildRuleRule( Syntax::Document& document, Syntax::Rule& parentRule, Syntax::Rule& rule ) {
            Q_ASSERT( !rule.type.isEmpty() );
            
            if ( rule.enumType() == Syntax::Rule::IncludeRules ) {
                const Syntax::Rule::List copiedRules = Syntax::Factory::copyRules( document, rule );
                parentRule.rules.removeOne( rule );
                parentRule.rules << copiedRules;
            }
            else {
                for ( int i = rule.rules.count() -1; i >= 0; i-- ) {
                    Syntax::Factory::buildRuleRule( document, rule, rule.rules[ i ] );
                }
            }
        }
        
        void buildContextRule( Syntax::Document& document, Syntax::Context& context, Syntax::Rule& rule ) {
            Q_ASSERT( !rule.type.isEmpty() );
            
            if ( rule.enumType() == Syntax::Rule::IncludeRules ) {
                const Syntax::Rule::List copiedRules = Syntax::Factory::copyRules( document, rule );
                context.rules.removeOne( rule );
                context.rules << copiedRules;
            }
            else {
                for ( int i = rule.rules.count() -1; i >= 0; i-- ) {
                    Syntax::Factory::buildRuleRule( document, rule, rule.rules[ i ] );
                }
            }
        }
        
        void buildDocuments() {
            foreach ( const QString& syntaxName, Syntax::Factory::mDocuments.keys() ) {
                Syntax::Document& document = Syntax::Factory::mDocuments[ syntaxName ];
                
                foreach ( const QString& contextName, document.highlighting.contexts.keys() ) {
                    Syntax::Context& context = document.highlighting.contexts[ contextName ];
                    
                    for ( int i = context.rules.count() -1; i >= 0; i-- ) {
                        Syntax::Factory::buildContextRule( document, context, context.rules[ i ] );
                    }
                }
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
