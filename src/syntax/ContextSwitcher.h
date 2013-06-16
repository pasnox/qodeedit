#ifndef CONTEXTSWITCHER_H
#define CONTEXTSWITCHER_H

#include "syntax/Context.h"

#include <QStringList>

namespace Syntax {

class ContextStack;
class ContextSwitcherData;

class ContextSwitcher
{
public:
    ContextSwitcher( const QString& operations = QString(), const Syntax::Context::Hash& contexts = Syntax::Context::Hash() );
    virtual ~ContextSwitcher();

    ContextSwitcher& operator=( const ContextSwitcher& other );
    bool operator==( const ContextSwitcher& other ) const;
    bool operator!=( const ContextSwitcher& other ) const;

    Syntax::ContextStack nextContextStack( const Syntax::ContextStack& contextStack, const QStringList& matches = QStringList() ) const;

private:
    Syntax::ContextSwitcherData* d;
};

} // Syntax

#endif // CONTEXTSWITCHER_H
