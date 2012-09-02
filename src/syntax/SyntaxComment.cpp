#include "SyntaxComment.h"

class Syntax::CommentData : public QSharedData
{
public:
    QString name;
    QString start;
    QString end;
    QString region;
    QString position;
    
    CommentData()
        : QSharedData()
    {
    }
    
    CommentData( const Syntax::CommentData& other )
        : QSharedData( other ),
            QE_OTHER_INIT( name ),
            QE_OTHER_INIT( start ),
            QE_OTHER_INIT( end ),
            QE_OTHER_INIT( region ),
            QE_OTHER_INIT( position )
    {
    }
    
    virtual ~CommentData() {
    }
};

QE_IMPL_SHARED_CLASS( Comment )

Syntax::Comment::~Comment()
{
}

QE_IMPL_MEMBER( QString, name, Comment )
QE_IMPL_MEMBER( QString, start, Comment )
QE_IMPL_MEMBER( QString, end, Comment )
QE_IMPL_MEMBER( QString, region, Comment )
QE_IMPL_MEMBER( QString, position, Comment )
