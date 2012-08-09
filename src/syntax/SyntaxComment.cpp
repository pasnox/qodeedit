#include "SyntaxComment.h"

class Syntax::CommentData : public QSharedData
{
public:
    QString name;
    QString start;
    QString end;
    QString region;
    QString weakDeliminator;
    QString position;
    
    CommentData()
        : QSharedData()
    {
    }
    
    CommentData( const Syntax::CommentData& other )
        : QSharedData( other ),
            SYNTAX_OTHER_INIT( name ),
            SYNTAX_OTHER_INIT( start ),
            SYNTAX_OTHER_INIT( end ),
            SYNTAX_OTHER_INIT( region ),
            SYNTAX_OTHER_INIT( weakDeliminator ),
            SYNTAX_OTHER_INIT( position )
    {
    }
    
    virtual ~CommentData()
    {
    }
};

Syntax::Comment::Comment()
    : d( new Syntax::CommentData ),
        SYNTAX_D_INIT( name ),
        SYNTAX_D_INIT( start ),
        SYNTAX_D_INIT( end ),
        SYNTAX_D_INIT( region ),
        SYNTAX_D_INIT( weakDeliminator ),
        SYNTAX_D_INIT( position )
{
}

Syntax::Comment::Comment( const Syntax::Comment& other )
    : d( other.d ),
        SYNTAX_D_INIT( name ),
        SYNTAX_D_INIT( start ),
        SYNTAX_D_INIT( end ),
        SYNTAX_D_INIT( region ),
        SYNTAX_D_INIT( weakDeliminator ),
        SYNTAX_D_INIT( position )
{
}

Syntax::Comment::~Comment()
{
}

Syntax::Comment& Syntax::Comment::operator=( const Syntax::Comment& other )
{
    if ( this != &other ) {
        d = other.d;
        SYNTAX_D_COPY( name );
        SYNTAX_D_COPY( start );
        SYNTAX_D_COPY( end );
        SYNTAX_D_COPY( region );
        SYNTAX_D_COPY( weakDeliminator );
        SYNTAX_D_COPY( position );
    }
    
    return *this;
}
