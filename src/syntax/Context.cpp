/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : Context.cpp
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#include "Context.h"

class Syntax::ContextData : public QSharedData
{
public:
    QString name;
    QString attribute;
    QString lineBeginContext;
    QString lineEndContext;
    bool fallThrough;
    QString fallThroughContext;
    bool dynamic;
    bool noIndentationBasedFolding;
    Syntax::Rule::List rules;

    ContextData()
        : QSharedData(),
            attribute( "normal" ),
            lineBeginContext( "#stay" ),
            lineEndContext( "#stay" ),
            fallThrough( false ),
            fallThroughContext( "#stay" ),
            dynamic( false ),
            noIndentationBasedFolding( false )
    {
    }

    ContextData( const Syntax::ContextData& other )
        : QSharedData( other ),
            QE_OTHER_INIT( name ),
            QE_OTHER_INIT( attribute ),
            QE_OTHER_INIT( lineBeginContext ),
            QE_OTHER_INIT( lineEndContext ),
            QE_OTHER_INIT( fallThrough ),
            QE_OTHER_INIT( fallThroughContext ),
            QE_OTHER_INIT( dynamic ),
            QE_OTHER_INIT( noIndentationBasedFolding ),
            QE_OTHER_INIT( rules )
    {
    }

    virtual ~ContextData() {
    }
};

QE_IMPL_SHARED_CLASS( Context, Syntax )

Syntax::Context::~Context()
{
}

QE_IMPL_MEMBER( QString, name, Context, Syntax )
QE_IMPL_MEMBER( QString, attribute, Context, Syntax )
QE_IMPL_MEMBER( QString, lineBeginContext, Context, Syntax )
QE_IMPL_MEMBER( QString, lineEndContext, Context, Syntax )
QE_IMPL_MEMBER( bool, fallThrough, Context, Syntax )
QE_IMPL_MEMBER( QString, fallThroughContext, Context, Syntax )
QE_IMPL_MEMBER( bool, dynamic, Context, Syntax )
QE_IMPL_MEMBER( bool, noIndentationBasedFolding, Context, Syntax )
QE_IMPL_MEMBER( Syntax::Rule::List, rules, Context, Syntax )

bool Syntax::Context::isNull() const
{
    return d->name.isEmpty();
}
