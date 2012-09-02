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
            QE_OTHER_INIT( name ),
            QE_OTHER_INIT( defStyleNum ),
            QE_OTHER_INIT( spellChecking ),
            QE_OTHER_INIT( color ),
            QE_OTHER_INIT( selColor ),
            QE_OTHER_INIT( bold ),
            QE_OTHER_INIT( italic ),
            QE_OTHER_INIT( strikeOut ),
            QE_OTHER_INIT( underline ),
            QE_OTHER_INIT( backgroundColor ),
            QE_OTHER_INIT( selBackgroundColor )
    {
    }
    
    virtual ~ItemDataData() {
    }
};

QE_IMPL_SHARED_CLASS( ItemData )

Syntax::ItemData::~ItemData()
{
}

QE_IMPL_MEMBER( QString, name, ItemData )
QE_IMPL_MEMBER( QString, defStyleNum, ItemData )
QE_IMPL_MEMBER( bool, spellChecking, ItemData )
QE_IMPL_MEMBER( QColor, color, ItemData )
QE_IMPL_MEMBER( QColor, selColor, ItemData )
QE_IMPL_MEMBER( bool, bold, ItemData )
QE_IMPL_MEMBER( bool, italic, ItemData )
QE_IMPL_MEMBER( bool, strikeOut, ItemData )
QE_IMPL_MEMBER( bool, underline, ItemData )
QE_IMPL_MEMBER( QColor, backgroundColor, ItemData )
QE_IMPL_MEMBER( QColor, selBackgroundColor, ItemData )
