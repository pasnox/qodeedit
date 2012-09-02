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
            QE_OTHER_INIT( comments ),
            QE_OTHER_INIT( keywords ),
            QE_OTHER_INIT( folding ),
            QE_OTHER_INIT( indentation ),
            QE_OTHER_INIT( emptyLines )
    {
    }
    
    virtual ~GeneralData() {
    }
};

QE_IMPL_SHARED_CLASS( General )

Syntax::General::~General()
{
}

QE_IMPL_MEMBER( Syntax::Comment::List, comments, General )
QE_IMPL_MEMBER( Syntax::Keywords, keywords, General )
QE_IMPL_MEMBER( Syntax::Folding, folding, General )
QE_IMPL_MEMBER( Syntax::Indentation, indentation, General )
QE_IMPL_MEMBER( Syntax::EmptyLine::List, emptyLines, General )
