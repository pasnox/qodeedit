#include "ContextStack.h"
#include "Tools.h"
#include "syntax/Document.h"

class Syntax::ContextStackData {
public:
    Syntax::Context::List contexts;
    QList<QStringList> matches;
    
    ContextStackData( const Syntax::Context::List& _contexts, const QList<QStringList>& _matches )
        : contexts( _contexts ),
            matches( _matches )
    {
    }
    
    virtual ~ContextStackData() {
    }
};

Syntax::ContextStack::ContextStack( const Syntax::Context::List& contexts, const QList<QStringList>& matches )
    : d( new Syntax::ContextStackData( contexts, matches ) )
{
}

Syntax::ContextStack::~ContextStack()
{
    delete d;
}

Syntax::ContextStack& Syntax::ContextStack::operator=( const Syntax::ContextStack& other )
{
    if ( this != &other ) {
        d->contexts = other.d->contexts;
        d->matches = other.d->matches;
    }

    return *this;
}

bool Syntax::ContextStack::operator==( const Syntax::ContextStack& other ) const
{
    return
        d->contexts == other.d->contexts &&
        d->matches == other.d->matches
    ;
}

bool Syntax::ContextStack::operator!=( const Syntax::ContextStack& other ) const
{
    return !operator==( other );
}

Syntax::Context Syntax::ContextStack::currentContext() const
{
    return d->contexts.isEmpty() ? Syntax::Context() : d->contexts.last();
}

QStringList Syntax::ContextStack::currentContextMatches() const
{
    return d->matches.isEmpty() ? QStringList() : d->matches.last();
}

Syntax::ContextStack Syntax::ContextStack::pop( int count ) const
{
#ifndef QT_NO_DEBUG
    if ( d->contexts.count() < count ) {
        qWarning( "%s: #pop value is too big", Q_FUNC_INFO );
    }
#endif
    return Syntax::ContextStack( QodeEdit::Tools::startingListItems( d->contexts, count ), QodeEdit::Tools::startingListItems( d->matches, count ) );
}

Syntax::ContextStack Syntax::ContextStack::append( const Syntax::Context& context, const QStringList& matches ) const
{
    return Syntax::ContextStack( Syntax::Context::List( d->contexts ) << context, QList<QStringList>( d->matches ) << matches );
}

Syntax::ContextStack Syntax::ContextStack::create( const Syntax::Document& syntax )
{
    return Syntax::ContextStack( Syntax::Context::List() << syntax.highlighting().defaultContext(), QList<QStringList>() << QStringList() );
}
