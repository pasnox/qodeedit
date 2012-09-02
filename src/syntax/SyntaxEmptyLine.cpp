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
            QE_OTHER_INIT( regExpr ),
            QE_OTHER_INIT( caseSensitive )
    {
    }
    
    virtual ~EmptyLineData() {
    }
};

QE_IMPL_SHARED_CLASS( EmptyLine )

Syntax::EmptyLine::~EmptyLine()
{
}

QE_IMPL_MEMBER( QString, regExpr, EmptyLine )
QE_IMPL_MEMBER( bool, caseSensitive, EmptyLine )
