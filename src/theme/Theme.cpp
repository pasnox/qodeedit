/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : SyntaxTheme.cpp
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#include "Theme.h"

#include <QFile>

class Theme::SchemaData : public QSharedData
{
public:
    QHash<QodeEdit::DefaultStyle, Theme::Style> defaultStyles;
    QString name;
    
    SchemaData()
        : QSharedData(),
            name( "default" )
    {
        initToDefault();
    }
    
    SchemaData( const Theme::SchemaData& other )
        : QSharedData( other ),
            QE_OTHER_INIT( defaultStyles ),
            QE_OTHER_INIT( name )
    {
    }
    
    virtual ~SchemaData() {
    }
    
    void initToDefault() {
        //defaultStyles[ QodeEdit::NormalStyle ].;
        
        defaultStyles[ QodeEdit::KeywordStyle ].setFontWeight( QFont::Bold );
        
        defaultStyles[ QodeEdit::DataTypeStyle ].setForeground( QBrush( QColor( "#0057ae" ) ) );
        
        defaultStyles[ QodeEdit::DecValStyle ].setForeground( QBrush( QColor( "#b07e00" ) ) );
        defaultStyles[ QodeEdit::BaseNStyle ].setForeground( QBrush( QColor( "#b07e00" ) ) );
        defaultStyles[ QodeEdit::FloatStyle ].setForeground( QBrush( QColor( "#b07e00" ) ) );
        
        defaultStyles[ QodeEdit::CharStyle ].setForeground( QBrush( QColor( "#ff80e0" ) ) );
        
        defaultStyles[ QodeEdit::StringStyle ].setForeground( QBrush( QColor( "#bf0303" ) ) );
        
        defaultStyles[ QodeEdit::CommentStyle ].setForeground( QBrush( QColor( "#888786" ) ) );
        defaultStyles[ QodeEdit::CommentStyle ].setFontItalic( true );
        
        defaultStyles[ QodeEdit::OthersStyle ].setForeground( QBrush( QColor( "#006e26" ) ) );
        
        defaultStyles[ QodeEdit::AlertStyle ].setForeground( QBrush( QColor( "#bf0303" ) ) );
        defaultStyles[ QodeEdit::AlertStyle ].setBackground( QBrush( QColor( "#f7e7e7" ) ) );
        defaultStyles[ QodeEdit::AlertStyle ].setFontWeight( QFont::Bold );
        
        defaultStyles[ QodeEdit::FunctionStyle ].setForeground( QBrush( QColor( "#442886" ) ) );
        
        defaultStyles[ QodeEdit::RegionMarkerStyle ].setForeground( QBrush( QColor( "#0057ae" ) ) );
        
        defaultStyles[ QodeEdit::ErrorStyle ].setForeground( QBrush( QColor( "#e1eaf8" ) ) );
    }
};

QE_IMPL_SHARED_CLASS( Schema, Theme )

Theme::Schema::~Schema()
{
}

QString Theme::Schema::name() const
{
    return d->name;
}

void Theme::Schema::setName( const QString& name )
{
    d->name = name;
}

Theme::Style Theme::Schema::defaultStyle( QodeEdit::DefaultStyle type ) const
{
    return d->defaultStyles.value( type );
}

void Theme::Schema::setDefaultStyle( QodeEdit::DefaultStyle type, const Theme::Style& style )
{
    d->defaultStyles[ type ] = style;
}
