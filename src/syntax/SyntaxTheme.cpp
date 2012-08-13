#include "SyntaxTheme.h"

#include <QFile>

class Syntax::ThemeData : public QSharedData
{
public:
    QHash<Syntax::Theme::DefaultStyle, Syntax::ThemeStyle> styles;
    QString name;
    
    ThemeData()
        : QSharedData(),
            name( "default" )
    {
    }
    
    ThemeData( const Syntax::ThemeData& other )
        : QSharedData( other ),
            SYNTAX_OTHER_INIT( styles ),
            SYNTAX_OTHER_INIT( name )
    {
    }
    
    virtual ~ThemeData() {
    }
    
    void initToDefault() {
        //styles[ Syntax::Theme::dsNormal ].;
        
        styles[ Syntax::Theme::dsKeyword ].setFontWeight( QFont::Bold );
        
        styles[ Syntax::Theme::dsDataType ].setForeground( QBrush( QColor( "#0057ae" ) ) );
        
        styles[ Syntax::Theme::dsDecVal ].setForeground( QBrush( QColor( "#b07e00" ) ) );
        styles[ Syntax::Theme::dsBaseN ].setForeground( QBrush( QColor( "#b07e00" ) ) );
        styles[ Syntax::Theme::dsFloat ].setForeground( QBrush( QColor( "#b07e00" ) ) );
        
        styles[ Syntax::Theme::dsChar ].setForeground( QBrush( QColor( "#ff80e0" ) ) );
        
        styles[ Syntax::Theme::dsString ].setForeground( QBrush( QColor( "#bf0303" ) ) );
        
        styles[ Syntax::Theme::dsComment ].setForeground( QBrush( QColor( "#888786" ) ) );
        styles[ Syntax::Theme::dsComment ].setFontItalic( true );
        
        styles[ Syntax::Theme::dsOthers ].setForeground( QBrush( QColor( "#006e26" ) ) );
        
        styles[ Syntax::Theme::dsAlert ].setForeground( QBrush( QColor( "#bf0303" ) ) );
        styles[ Syntax::Theme::dsAlert ].setBackground( QBrush( QColor( "#f7e7e7" ) ) );
        styles[ Syntax::Theme::dsAlert ].setFontWeight( QFont::Bold );
        
        styles[ Syntax::Theme::dsFunction ].setForeground( QBrush( QColor( "#442886" ) ) );
        
        styles[ Syntax::Theme::dsRegionMarker ].setForeground( QBrush( QColor( "#0057ae" ) ) );
        
        styles[ Syntax::Theme::dsError ].setForeground( QBrush( QColor( "#e1eaf8" ) ) );
    }
};

Syntax::Theme::Theme( const QString& filePath )
    : d( new Syntax::ThemeData )
{
    if ( !QFile::exists( filePath ) ) {
        d->initToDefault();
    }
}

Syntax::Theme::Theme( const Syntax::Theme& other )
    : d( other.d )
{
}

Syntax::Theme::~Theme()
{
}

SYNTAX_IMPL_OPERATORS( Theme )

QString Syntax::Theme::name() const
{
    return d->name;
}

void Syntax::Theme::setName( const QString& name )
{
    d->name = name;
}

Syntax::ThemeStyle Syntax::Theme::style( Syntax::Theme::DefaultStyle type ) const
{
    return d->styles.value( type );
}

void Syntax::Theme::setStyle( Syntax::Theme::DefaultStyle type, const Syntax::ThemeStyle& style )
{
    d->styles[ type ] = style;
}
