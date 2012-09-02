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
            QE_OTHER_INIT( char_ ),
            QE_OTHER_INIT( string ),
            QE_OTHER_INIT( ignored )
    {
    }
    
    virtual ~EncodingData() {
    }
};

QE_IMPL_SHARED_CLASS( Encoding )

Syntax::Encoding::~Encoding()
{
}

QE_IMPL_MEMBER( QString, char_, Encoding )
QE_IMPL_MEMBER( QString, string, Encoding )
QE_IMPL_MEMBER( bool, ignored, Encoding )
