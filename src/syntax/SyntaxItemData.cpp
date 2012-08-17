#include "SyntaxItemData.h"

class Syntax::ItemDataData : public QSharedData
{
public:
    QString name;
    QString defStyleNum;
    bool spellChecking;
    QColor color;
    QColor selColor;
    bool bold;
    bool italic;
    bool strikeOut;
    bool underline;
    QColor backgroundColor;
    QColor selBackgroundColor;
    
    ItemDataData()
        : QSharedData(),
            spellChecking( false ),
            bold( false ),
            italic( false ),
            strikeOut( false ),
            underline( false )
    {
    }
    
    ItemDataData( const Syntax::ItemDataData& other )
        : QSharedData( other ),
            SYNTAX_OTHER_INIT( name ),
            SYNTAX_OTHER_INIT( defStyleNum ),
            SYNTAX_OTHER_INIT( spellChecking ),
            SYNTAX_OTHER_INIT( color ),
            SYNTAX_OTHER_INIT( selColor ),
            SYNTAX_OTHER_INIT( bold ),
            SYNTAX_OTHER_INIT( italic ),
            SYNTAX_OTHER_INIT( strikeOut ),
            SYNTAX_OTHER_INIT( underline ),
            SYNTAX_OTHER_INIT( backgroundColor ),
            SYNTAX_OTHER_INIT( selBackgroundColor )
    {
    }
    
    virtual ~ItemDataData() {
    }
};

Syntax::ItemData::ItemData()
    : d( new Syntax::ItemDataData )
{
}

Syntax::ItemData::ItemData( const Syntax::ItemData& other )
    : d( other.d )
{
}

Syntax::ItemData::~ItemData()
{
}

SYNTAX_IMPL_MEMBER( QString, name, ItemData )
SYNTAX_IMPL_MEMBER( QString, defStyleNum, ItemData )
SYNTAX_IMPL_MEMBER( bool, spellChecking, ItemData )
SYNTAX_IMPL_MEMBER( QColor, color, ItemData )
SYNTAX_IMPL_MEMBER( QColor, selColor, ItemData )
SYNTAX_IMPL_MEMBER( bool, bold, ItemData )
SYNTAX_IMPL_MEMBER( bool, italic, ItemData )
SYNTAX_IMPL_MEMBER( bool, strikeOut, ItemData )
SYNTAX_IMPL_MEMBER( bool, underline, ItemData )
SYNTAX_IMPL_MEMBER( QColor, backgroundColor, ItemData )
SYNTAX_IMPL_MEMBER( QColor, selBackgroundColor, ItemData )
SYNTAX_IMPL_OPERATORS( ItemData )
