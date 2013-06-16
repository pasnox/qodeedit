#ifndef CONTEXTSTACK_H
#define CONTEXTSTACK_H

#include "syntax/Context.h"
#include <QStringList>

namespace Syntax {

class Document;
class ContextStackData;

class ContextStack
{
public:
    ContextStack( const Syntax::Context::List& contexts = Syntax::Context::List(), const QList<QStringList>& matches = QList<QStringList>() );
    virtual ~ContextStack();

    Syntax::ContextStack& operator=( const Syntax::ContextStack& other );
    bool operator==( const Syntax::ContextStack& other ) const;
    bool operator!=( const Syntax::ContextStack& other ) const;

    Syntax::Context currentContext() const;
    QStringList currentContextMatches() const;

    Syntax::ContextStack pop( int count ) const;
    Syntax::ContextStack append( const Syntax::Context& context, const QStringList& matches ) const;

    static Syntax::ContextStack create( const Syntax::Document& syntax );

private:
    Syntax::ContextStackData* d;
};

} //Syntax

#endif // CONTEXTSTACK_H
