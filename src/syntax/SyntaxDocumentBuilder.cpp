#include "SyntaxDocumentBuilder.h"
#include "SyntaxDocument.h"

class Syntax::DocumentBuilderData : public QSharedData
{
public:
    QHash<QString, Syntax::Document> documents;
    
    DocumentBuilderData()
        : QSharedData()
    {
    }
    
    DocumentBuilderData( const Syntax::DocumentBuilderData& other )
        : QSharedData( other ),
            SYNTAX_OTHER_INIT( documents )
    {
    }
    
    virtual ~DocumentBuilderData() {
    }
    
    void mergeRules( Syntax::Document& document, Syntax::Context& context, Syntax::Rule& rule ) {
        QString srcContextName = rule.context();
        QString srcSyntaxName = document.name();
        
        // import external initial context rules
        if ( srcContextName.startsWith( "##" ) ) {
            srcSyntaxName = srcContextName.mid( 2 );
            srcContextName.clear(); // filled up later with document defaultContext
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
        Q_ASSERT( documents.contains( srcSyntaxName ) );
        Syntax::Document& srcDocument = documents[ srcSyntaxName ];
        
        // get source context name if needed
        if ( rule.context().startsWith( "##" ) ) {
            srcContextName = srcDocument.highlighting().defaultContext();
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
        Q_ASSERT( !rule.name().isEmpty() );
        
        if ( rule.type() == QodeEdit::IncludeRule ) {
            mergeRules( document, context, rule );
        }
        else {
            Syntax::Rule::List& rules = rule.rules();
            
            for ( int i = rules.count() -1; i >= 0; i-- ) {
                buildRuleRule( document, context, rules[ i ] );
            }
        }
    }
    
    void buildContextRule( Syntax::Document& document, Syntax::Context& context, Syntax::Rule& rule ) {
        Q_ASSERT( !rule.name().isEmpty() );
        
        if ( rule.type() == QodeEdit::IncludeRule ) {
            mergeRules( document, context, rule );
        }
        else {
            Syntax::Rule::List& rules = rule.rules();
            
            for ( int i = rules.count() -1; i >= 0; i-- ) {
                buildRuleRule( document, context, rules[ i ] );
            }
        }
    }
    
    void buildContextRules( Syntax::Document& document, Syntax::Context& context ) {
        if ( document.finalyzed() ) {
            return;
        }
        
        Syntax::Rule::List& rules = context.rules();
        
        for ( int i = rules.count() -1; i >= 0; i-- ) {
            buildContextRule( document, context, rules[ i ] );
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
        foreach ( const QString& syntaxName, documents.keys() ) {
            buildDocument( documents[ syntaxName ] );
        }
    }
};

Syntax::DocumentBuilder::DocumentBuilder( const QHash<QString, Syntax::Document>& documents )
    : d( new Syntax::DocumentBuilderData )
{
    d->documents = documents;
}

Syntax::DocumentBuilder::DocumentBuilder( const Syntax::DocumentBuilder& other )
    : d( other.d )
{
}

Syntax::DocumentBuilder::~DocumentBuilder()
{
}

SYNTAX_IMPL_OPERATORS( DocumentBuilder )

void Syntax::DocumentBuilder::buildDocuments()
{
    d->buildDocuments();
}
