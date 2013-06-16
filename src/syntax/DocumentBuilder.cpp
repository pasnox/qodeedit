/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : DocumentBuilder.cpp
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#include "DocumentBuilder.h"
#include "Document.h"

#include <QDebug>

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
            QE_OTHER_INIT( documents )
    {
    }

    virtual ~DocumentBuilderData() {
    }

    void mergeRules( Syntax::Document& document, Syntax::Context& context, Syntax::Rule& _rule ) {
        Syntax::IncludeRulesRule rule = _rule.toIncludeRules();
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
            srcContextName = srcDocument.highlighting().defaultContextName();
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
        Q_ASSERT( rule.type() != QodeEdit::InvalidRule );

        if ( rule.type() == QodeEdit::IncludeRulesRule ) {
            mergeRules( document, context, rule );
        }
        else {
            Syntax::Rule::List rules = rule.rules();

            for ( int i = rules.count() -1; i >= 0; i-- ) {
                buildRuleRule( document, context, rules[ i ] );
            }
        }
    }

    void buildContextRule( Syntax::Document& document, Syntax::Context& context, Syntax::Rule& rule ) {
        Q_ASSERT( rule.type() != QodeEdit::InvalidRule );

        if ( rule.type() == QodeEdit::IncludeRulesRule ) {
            mergeRules( document, context, rule );
        }
        else {
            Syntax::Rule::List rules = rule.rules();

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

    void buildDocuments( const QHash<QString, Syntax::Document>& _documents ) {
        documents = _documents;

        foreach ( const QString& syntaxName, documents.keys() ) {
            buildDocument( documents[ syntaxName ] );
        }
    }
};

QE_IMPL_SHARED_CLASS( DocumentBuilder, Syntax )

Syntax::DocumentBuilder::~DocumentBuilder()
{
}

void Syntax::DocumentBuilder::buildDocuments( const QHash<QString, Syntax::Document>& documents )
{
    d->buildDocuments( documents );
}
