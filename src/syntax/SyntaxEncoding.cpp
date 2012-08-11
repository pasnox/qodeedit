#include "SyntaxEncoding.h"

class Syntax::EncodingData : public QSharedData
{
public:
    QString char_;
    QString string;
    bool ignored;
    
    EncodingData()
        : QSharedData(),
            ignored( false )
    {
    }
    
    EncodingData( const Syntax::EncodingData& other )
        : QSharedData( other ),
            SYNTAX_OTHER_INIT( char_ ),
            SYNTAX_OTHER_INIT( string ),
            SYNTAX_OTHER_INIT( ignored )
    {
    }
    
    virtual ~EncodingData()
    {
    }
};

Syntax::Encoding::Encoding()
    : d( new Syntax::EncodingData )
{
}

Syntax::Encoding::Encoding( const Syntax::Encoding& other )
    : d( other.d )
{
}

Syntax::Encoding::~Encoding()
{
}

SYNTAX_IMPL_MEMBER( QString, char_, Encoding )
SYNTAX_IMPL_MEMBER( QString, string, Encoding )
SYNTAX_IMPL_MEMBER( bool, ignored, Encoding )
SYNTAX_IMPL_OPERATORS( Encoding )
