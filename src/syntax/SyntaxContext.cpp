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
    : d( new Syntax::ContextData ),
        SYNTAX_D_INIT( name ),
        SYNTAX_D_INIT( attribute ),
        SYNTAX_D_INIT( lineEndContext ),
        SYNTAX_D_INIT( fallThrough ),
        SYNTAX_D_INIT( fallThroughContext ),
        SYNTAX_D_INIT( dynamic ),
        SYNTAX_D_INIT( noIndentationBasedFolding ),
        SYNTAX_D_INIT( caseSensitive ),
        SYNTAX_D_INIT( rules )
{
}

Syntax::Context::Context( const Syntax::Context& other )
    : d( other.d ),
        SYNTAX_D_INIT( name ),
        SYNTAX_D_INIT( attribute ),
        SYNTAX_D_INIT( lineEndContext ),
        SYNTAX_D_INIT( fallThrough ),
        SYNTAX_D_INIT( fallThroughContext ),
        SYNTAX_D_INIT( dynamic ),
        SYNTAX_D_INIT( noIndentationBasedFolding ),
        SYNTAX_D_INIT( caseSensitive ),
        SYNTAX_D_INIT( rules )
{
}

Syntax::Context::~Context()
{
}

Syntax::Context& Syntax::Context::operator=( const Syntax::Context& other )
{
    if ( this != &other ) {
        d = other.d;
        SYNTAX_D_COPY( name );
        SYNTAX_D_COPY( attribute );
        SYNTAX_D_COPY( lineEndContext );
        SYNTAX_D_COPY( fallThrough );
        SYNTAX_D_COPY( fallThroughContext );
        SYNTAX_D_COPY( dynamic );
        SYNTAX_D_COPY( noIndentationBasedFolding );
        SYNTAX_D_COPY( caseSensitive );
        SYNTAX_D_COPY( rules );
    }
    
    return *this;
}
