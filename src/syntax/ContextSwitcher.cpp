#include "ContextSwitcher.h"
#include "ContextStack.h"
#include "syntax/Document.h"
#include "Tools.h"

class Syntax::ContextSwitcherData {
public:
    int popsCount;
    Syntax::Context contextToSwitch;
    
    ContextSwitcherData( const QString& operations, const Syntax::Context::Hash& contexts )
        : popsCount( 0 )
    {
        QString rest = operations;
        
        while ( rest.startsWith( "#pop" ) ) {
            popsCount++;
            rest.remove( 0, 4 );
        }
        
        if ( rest == "#stay" ) {
            if ( popsCount ) {
                qWarning( "%s: Invalid context operation '%s'", Q_FUNC_INFO, qPrintable( operations ) );
            }
        }
        else if ( contexts.contains( rest ) ) {
            contextToSwitch = contexts[ rest ];
        }
        else if ( rest.startsWith( "##" ) ) {
            // TODO implement IncludeRules
        }
        else if ( !rest.isEmpty() ) {
            qWarning( "%s: Unknown context '%s' in '%s'", Q_FUNC_INFO, qPrintable( rest ), qPrintable( QStringList( contexts.keys() ).join( ", " ) ) );
        }
    }
    
    virtual ~ContextSwitcherData() {
    }
};

Syntax::ContextSwitcher::ContextSwitcher( const QString& operations, const Syntax::Context::Hash& contexts )
    : d( new Syntax::ContextSwitcherData( operations, contexts ) )
{
}

Syntax::ContextSwitcher::~ContextSwitcher()
{
    delete d;
}

Syntax::ContextSwitcher& Syntax::ContextSwitcher::operator=( const Syntax::ContextSwitcher& other )
{
    if ( this != &other ) {
        d->popsCount = other.d->popsCount;
        d->contextToSwitch = other.d->contextToSwitch;
    }

    return *this;
}

bool Syntax::ContextSwitcher::operator==( const Syntax::ContextSwitcher& other ) const
{
    return
        d->popsCount == other.d->popsCount &&
        d->contextToSwitch == other.d->contextToSwitch
    ;
}

bool Syntax::ContextSwitcher::operator!=( const Syntax::ContextSwitcher& other ) const
{
    return !operator==( other );
}

Syntax::ContextStack Syntax::ContextSwitcher::nextContextStack( const Syntax::ContextStack& contextStack, const QStringList& matches ) const
{
    Syntax::ContextStack stack = contextStack;
    
    if ( d->popsCount > 0 ) {
        stack = stack.pop( d->popsCount );
    }
    
    if ( !d->contextToSwitch.isNull() ) {
        stack = stack.append( d->contextToSwitch, d->contextToSwitch.dynamic() ? matches : QStringList() );
    }
    
    return stack;
}
