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
    
    virtual ~CommentData() {
    }
};

Syntax::Comment::Comment()
    : d( new Syntax::CommentData )
{
}

Syntax::Comment::Comment( const Syntax::Comment& other )
    : d( other.d )
{
}

Syntax::Comment::~Comment()
{
}

SYNTAX_IMPL_MEMBER( QString, name, Comment )
SYNTAX_IMPL_MEMBER( QString, start, Comment )
SYNTAX_IMPL_MEMBER( QString, end, Comment )
SYNTAX_IMPL_MEMBER( QString, region, Comment )
SYNTAX_IMPL_MEMBER( QString, weakDeliminator, Comment )
SYNTAX_IMPL_MEMBER( QString, position, Comment )
SYNTAX_IMPL_OPERATORS( Comment )
