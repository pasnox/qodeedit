#include "SyntaxGeneral.h"

class Syntax::GeneralData : public QSharedData
{
public:
    Syntax::Comment::List comments;
    Syntax::Keywords keywords;
    Syntax::Folding folding;
    Syntax::Indentation indentation;
    Syntax::EmptyLine::List emptyLines;
    
    GeneralData()
        : QSharedData()
    {
    }
    
    GeneralData( const Syntax::GeneralData& other )
        : QSharedData( other ),
            SYNTAX_OTHER_INIT( comments ),
            SYNTAX_OTHER_INIT( keywords ),
            SYNTAX_OTHER_INIT( folding ),
            SYNTAX_OTHER_INIT( indentation ),
            SYNTAX_OTHER_INIT( emptyLines )
    {
    }
    
    virtual ~GeneralData()
    {
    }
};

Syntax::General::General()
    : d( new Syntax::GeneralData )
{
}

Syntax::General::General( const Syntax::General& other )
    : d( other.d )
{
}

Syntax::General::~General()
{
}

SYNTAX_IMPL_MEMBER( Syntax::Comment::List, comments, General )
SYNTAX_IMPL_MEMBER( Syntax::Keywords, keywords, General )
SYNTAX_IMPL_MEMBER( Syntax::Folding, folding, General )
SYNTAX_IMPL_MEMBER( Syntax::Indentation, indentation, General )
SYNTAX_IMPL_MEMBER( Syntax::EmptyLine::List, emptyLines, General )
SYNTAX_IMPL_OPERATORS( General )
