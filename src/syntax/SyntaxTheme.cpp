#include "SyntaxTheme.h"

#include <QFile>

class Syntax::ThemeData : public QSharedData
{
public:
    QHash<QodeEdit::Style, Syntax::ThemeStyle> styles;
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
        //styles[ QodeEdit::Normal ].;
        
        styles[ QodeEdit::KeywordStyle ].setFontWeight( QFont::Bold );
        
        styles[ QodeEdit::DataTypeStyle ].setForeground( QBrush( QColor( "#0057ae" ) ) );
        
        styles[ QodeEdit::DecValStyle ].setForeground( QBrush( QColor( "#b07e00" ) ) );
        styles[ QodeEdit::BaseNStyle ].setForeground( QBrush( QColor( "#b07e00" ) ) );
        styles[ QodeEdit::FloatStyle ].setForeground( QBrush( QColor( "#b07e00" ) ) );
        
        styles[ QodeEdit::CharStyle ].setForeground( QBrush( QColor( "#ff80e0" ) ) );
        
        styles[ QodeEdit::StringStyle ].setForeground( QBrush( QColor( "#bf0303" ) ) );
        
        styles[ QodeEdit::CommentStyle ].setForeground( QBrush( QColor( "#888786" ) ) );
        styles[ QodeEdit::CommentStyle ].setFontItalic( true );
        
        styles[ QodeEdit::OthersStyle ].setForeground( QBrush( QColor( "#006e26" ) ) );
        
        styles[ QodeEdit::AlertStyle ].setForeground( QBrush( QColor( "#bf0303" ) ) );
        styles[ QodeEdit::AlertStyle ].setBackground( QBrush( QColor( "#f7e7e7" ) ) );
        styles[ QodeEdit::AlertStyle ].setFontWeight( QFont::Bold );
        
        styles[ QodeEdit::FunctionStyle ].setForeground( QBrush( QColor( "#442886" ) ) );
        
        styles[ QodeEdit::RegionMarkerStyle ].setForeground( QBrush( QColor( "#0057ae" ) ) );
        
        styles[ QodeEdit::ErrorStyle ].setForeground( QBrush( QColor( "#e1eaf8" ) ) );
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

Syntax::ThemeStyle Syntax::Theme::style( QodeEdit::Style type ) const
{
    return d->styles.value( type );
}

void Syntax::Theme::setStyle( QodeEdit::Style type, const Syntax::ThemeStyle& style )
{
    d->styles[ type ] = style;
}
