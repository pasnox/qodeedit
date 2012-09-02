#include "SyntaxContext.h"

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

QE_IMPL_SHARED_CLASS( Context )

Syntax::Context::~Context()
{
}

QE_IMPL_MEMBER( QString, name, Context )
QE_IMPL_MEMBER( QString, attribute, Context )
QE_IMPL_MEMBER( QString, lineBeginContext, Context )
QE_IMPL_MEMBER( QString, lineEndContext, Context )
QE_IMPL_MEMBER( bool, fallThrough, Context )
QE_IMPL_MEMBER( QString, fallThroughContext, Context )
QE_IMPL_MEMBER( bool, dynamic, Context )
QE_IMPL_MEMBER( bool, noIndentationBasedFolding, Context )
QE_IMPL_MEMBER( Syntax::Rule::List, rules, Context )
