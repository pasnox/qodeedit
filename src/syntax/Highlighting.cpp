/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : Highlighting.cpp
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#include "Highlighting.h"

class Syntax::HighlightingData : public QSharedData
{
public:
    QString defaultContextName;
    Syntax::HashList lists;
    Syntax::Context::Hash contexts;
    Syntax::ItemData::Hash itemDatas;

    HighlightingData()
        : QSharedData()
    {
    }

    HighlightingData( const Syntax::HighlightingData& other )
        : QSharedData( other ),
            QE_OTHER_INIT( defaultContextName ),
            QE_OTHER_INIT( lists ),
            QE_OTHER_INIT( contexts ),
            QE_OTHER_INIT( itemDatas )
    {
    }

    virtual ~HighlightingData() {
    }
};

QE_IMPL_SHARED_CLASS( Highlighting, Syntax )

Syntax::Highlighting::~Highlighting()
{
}

QE_IMPL_MEMBER( QString, defaultContextName, Highlighting, Syntax )
QE_IMPL_MEMBER( Syntax::HashList, lists, Highlighting, Syntax )
QE_IMPL_MEMBER( Syntax::Context::Hash, contexts, Highlighting, Syntax )
QE_IMPL_MEMBER( Syntax::ItemData::Hash, itemDatas, Highlighting, Syntax )

Syntax::List Syntax::Highlighting::list( const QString& name ) const
{
    return d->lists.value( name );
}

Syntax::Context Syntax::Highlighting::context( const QString& name ) const
{
    return d->contexts.value( name );
}

Syntax::Context Syntax::Highlighting::defaultContext() const
{
    return d->contexts.value( d->defaultContextName );
}
