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
            QE_OTHER_INIT( caseSensitive ),
            QE_OTHER_INIT( weakDeliminator ),
            QE_OTHER_INIT( additionalDeliminator ),
            QE_OTHER_INIT( wordWrapDeliminator )
    {
    }
    
    virtual ~KeywordsData() {
    }
};

QE_IMPL_SHARED_CLASS( Keywords )

Syntax::Keywords::~Keywords()
{
}

QE_IMPL_MEMBER( bool, caseSensitive, Keywords )
QE_IMPL_MEMBER( QString, weakDeliminator, Keywords )
QE_IMPL_MEMBER( QString, additionalDeliminator, Keywords )
QE_IMPL_MEMBER( QString, wordWrapDeliminator, Keywords )
