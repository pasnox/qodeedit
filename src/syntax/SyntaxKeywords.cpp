#include "SyntaxKeywords.h"

class Syntax::KeywordsData : public QSharedData
{
public:
    bool caseSensitive;
    QString weakDeliminator;
    QString additionalDeliminator;
    QString wordWrapDeliminator;
    
    KeywordsData()
        : QSharedData(),
            caseSensitive( false )
    {
    }
    
    KeywordsData( const Syntax::KeywordsData& other )
        : QSharedData( other ),
            SYNTAX_OTHER_INIT( caseSensitive ),
            SYNTAX_OTHER_INIT( weakDeliminator ),
            SYNTAX_OTHER_INIT( additionalDeliminator ),
            SYNTAX_OTHER_INIT( wordWrapDeliminator )
    {
    }
    
    virtual ~KeywordsData() {
    }
};

Syntax::Keywords::Keywords()
    : d( new Syntax::KeywordsData )
{
}

Syntax::Keywords::Keywords( const Syntax::Keywords& other )
    : d( other.d )
{
}

Syntax::Keywords::~Keywords()
{
}

SYNTAX_IMPL_MEMBER( bool, caseSensitive, Keywords )
SYNTAX_IMPL_MEMBER( QString, weakDeliminator, Keywords )
SYNTAX_IMPL_MEMBER( QString, additionalDeliminator, Keywords )
SYNTAX_IMPL_MEMBER( QString, wordWrapDeliminator, Keywords )
SYNTAX_IMPL_OPERATORS( Keywords )
