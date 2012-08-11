#include "SyntaxEmptyLine.h"

class Syntax::EmptyLineData : public QSharedData
{
public:
    QString regExpr;
    bool caseSensitive;
    
    EmptyLineData()
        : QSharedData(),
            caseSensitive( false )
    {
    }
    
    EmptyLineData( const Syntax::EmptyLineData& other )
        : QSharedData( other ),
            SYNTAX_OTHER_INIT( regExpr ),
            SYNTAX_OTHER_INIT( caseSensitive )
    {
    }
    
    virtual ~EmptyLineData()
    {
    }
};

Syntax::EmptyLine::EmptyLine()
    : d( new Syntax::EmptyLineData )
{
}

Syntax::EmptyLine::EmptyLine( const Syntax::EmptyLine& other )
    : d( other.d )
{
}

Syntax::EmptyLine::~EmptyLine()
{
}

SYNTAX_IMPL_MEMBER( QString, regExpr, EmptyLine )
SYNTAX_IMPL_MEMBER( bool, caseSensitive, EmptyLine )
SYNTAX_IMPL_OPERATORS( EmptyLine )
