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
    QHash<QodeEdit::Style, Theme::Style> styles;
    QString name;
    
    SchemaData()
        : QSharedData(),
            name( "default" )
    {
        initToDefault();
    }
    
    SchemaData( const Theme::SchemaData& other )
        : QSharedData( other ),
            QE_OTHER_INIT( styles ),
            QE_OTHER_INIT( name )
    {
    }
    
    virtual ~SchemaData() {
    }
    
    void initToDefault() {
        //styles[ QodeEdit::NormalStyle ].;
        
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

Theme::Style Theme::Schema::style( QodeEdit::Style type ) const
{
    return d->styles.value( type );
}

void Theme::Schema::setStyle( QodeEdit::Style type, const Theme::Style& style )
{
    d->styles[ type ] = style;
}
