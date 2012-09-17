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
#include "Tools.h"

#include <QFile>

class Theme::SchemaData : public QSharedData
{
public:
    QHash<QString, Theme::Style> styles;
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
    
    QString syntaxStyleKey( const QString& syntaxName, const QString& styleName ) const {
        return QString( "%1:%2" ).arg( syntaxName.trimmed() ).arg( styleName.trimmed() ).toLower();
    }
    
    QString defaultStyleKey( QodeEdit::DefaultStyle defaultStyle ) const {
        return QString( "ds%1" ).arg( QodeEdit::Tools::defaultStyleToString( defaultStyle ) ).toLower().trimmed();
    }
    
    Theme::Style* defaultStyle( QodeEdit::DefaultStyle defaultStyle ) {
        return &styles[ defaultStyleKey( defaultStyle ) ];
    }
    
    void initToDefault() {
        Theme::Style* style = 0;
        
        style = defaultStyle( QodeEdit::NormalStyle );
        
        style = defaultStyle( QodeEdit::KeywordStyle );
        style->setFontWeight( QFont::Bold );
        
        style = defaultStyle( QodeEdit::DataTypeStyle );
        style->setForeground( QBrush( QColor( "#0057ae" ) ) );
        
        style = defaultStyle( QodeEdit::DecValStyle );
        style->setForeground( QBrush( QColor( "#b07e00" ) ) );
        style->setForeground( QBrush( QColor( "#b07e00" ) ) );
        style->setForeground( QBrush( QColor( "#b07e00" ) ) );
        
        style = defaultStyle( QodeEdit::CharStyle );
        style->setForeground( QBrush( QColor( "#ff80e0" ) ) );
        
        style = defaultStyle( QodeEdit::StringStyle );
        style->setForeground( QBrush( QColor( "#bf0303" ) ) );
        
        style = defaultStyle( QodeEdit::CommentStyle );
        style->setForeground( QBrush( QColor( "#888786" ) ) );
        style->setFontItalic( true );
        
        style = defaultStyle( QodeEdit::OthersStyle );
        style->setForeground( QBrush( QColor( "#006e26" ) ) );
        
        style = defaultStyle( QodeEdit::AlertStyle );
        style->setForeground( QBrush( QColor( "#bf0303" ) ) );
        style->setBackground( QBrush( QColor( "#f7e7e7" ) ) );
        style->setFontWeight( QFont::Bold );
        
        style = defaultStyle( QodeEdit::FunctionStyle );
        style->setForeground( QBrush( QColor( "#442886" ) ) );
        
        style = defaultStyle( QodeEdit::RegionMarkerStyle );
        style->setForeground( QBrush( QColor( "#0057ae" ) ) );
        
        style = defaultStyle( QodeEdit::ErrorStyle );
        style->setForeground( QBrush( QColor( "#e1eaf8" ) ) );
    }
};

QE_IMPL_SHARED_CLASS( Schema, Theme )
QE_IMPL_MEMBER( QString, name, Schema, Theme )

Theme::Schema::~Schema()
{
}

Theme::Style Theme::Schema::syntaxStyle( const QString& syntaxName, const QString& styleName ) const
{
    return d->styles.value( d->syntaxStyleKey( syntaxName, styleName ) );
}

void Theme::Schema::setSyntaxStyle( const QString& syntaxName, const QString& styleName, const Theme::Style& style )
{
    d->styles[ d->syntaxStyleKey( syntaxName, styleName ) ] = style;
}

Theme::Style Theme::Schema::defaultStyle( QodeEdit::DefaultStyle defaultStyle ) const
{
    return d->styles.value( d->defaultStyleKey( defaultStyle ) );
}

void Theme::Schema::setDefaultStyle( QodeEdit::DefaultStyle defaultStyle, const Theme::Style& style )
{
    d->styles[ d->defaultStyleKey( defaultStyle ) ] = style;
}
