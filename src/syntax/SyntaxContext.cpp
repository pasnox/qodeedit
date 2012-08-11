#include "SyntaxContext.h"

class Syntax::ContextData : public QSharedData
{
public:
    QString name;
    QString attribute;
    QString lineEndContext;
    bool fallThrough;
    QString fallThroughContext;
    bool dynamic;
    bool noIndentationBasedFolding;
    bool caseSensitive;
    Syntax::Rule::List rules;
    
    ContextData()
        : QSharedData(),
            fallThrough( false ),
            dynamic( false ),
            noIndentationBasedFolding( false ),
            caseSensitive( false )
    {
    }
    
    ContextData( const Syntax::ContextData& other )
        : QSharedData( other ),
            SYNTAX_OTHER_INIT( name ),
            SYNTAX_OTHER_INIT( attribute ),
            SYNTAX_OTHER_INIT( lineEndContext ),
            SYNTAX_OTHER_INIT( fallThrough ),
            SYNTAX_OTHER_INIT( fallThroughContext ),
            SYNTAX_OTHER_INIT( dynamic ),
            SYNTAX_OTHER_INIT( noIndentationBasedFolding ),
            SYNTAX_OTHER_INIT( caseSensitive ),
            SYNTAX_OTHER_INIT( rules )
    {
    }
    
    virtual ~ContextData()
    {
    }
};

Syntax::Context::Context()
    : d( new Syntax::ContextData )
{
}

Syntax::Context::Context( const Syntax::Context& other )
    : d( other.d )
{
}

Syntax::Context::~Context()
{
}

SYNTAX_IMPL_MEMBER( QString, name, Context )
SYNTAX_IMPL_MEMBER( QString, attribute, Context )
SYNTAX_IMPL_MEMBER( QString, lineEndContext, Context )
SYNTAX_IMPL_MEMBER( bool, fallThrough, Context )
SYNTAX_IMPL_MEMBER( QString, fallThroughContext, Context )
SYNTAX_IMPL_MEMBER( bool, dynamic, Context )
SYNTAX_IMPL_MEMBER( bool, noIndentationBasedFolding, Context )
SYNTAX_IMPL_MEMBER( bool, caseSensitive, Context )
SYNTAX_IMPL_MEMBER( Syntax::Rule::List, rules, Context )
SYNTAX_IMPL_OPERATORS( Context )
