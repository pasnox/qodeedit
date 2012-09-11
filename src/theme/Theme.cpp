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

class Syntax::ThemeData : public QSharedData
{
public:
    QHash<QodeEdit::Style, Syntax::ThemeStyle> styles;
    QString name;
    
    ThemeData()
        : QSharedData(),
            name( "default" )
    {
        initToDefault();
    }
    
    ThemeData( const Syntax::ThemeData& other )
        : QSharedData( other ),
            QE_OTHER_INIT( styles ),
            QE_OTHER_INIT( name )
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

QE_IMPL_SHARED_CLASS( Theme )

Syntax::Theme::~Theme()
{
}

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
