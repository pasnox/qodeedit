#ifndef SYNTAXTHEME_H
#define SYNTAXTHEME_H

#include <QExplicitlySharedDataPointer>
#include <QList>
#include <QTextCharFormat>

#include "SyntaxHelpers.h"

namespace Syntax {

class ThemeData;

class ThemeStyle : public QTextCharFormat
{
};

class Theme
{
private:
    QExplicitlySharedDataPointer<Syntax::ThemeData> d;
    
public:
    enum DefaultStyle {
        dsNormal,
        dsKeyword,
        dsDataType,
        dsDecVal,
        dsBaseN,
        dsFloat,
        dsChar,
        dsString,
        dsComment,
        dsOthers,
        dsAlert,
        dsFunction,
        dsRegionMarker,
        dsError
    };
    
    typedef QList<Syntax::Theme> List;
    
    Theme( const QString& filePath = QString::null );
    Theme( const Syntax::Theme& other );
    virtual ~Theme();
    
    SYNTAX_DECL_OPERATORS( Theme );
    
    QString name() const;
    
    Syntax::ThemeStyle style( Syntax::Theme::DefaultStyle type ) const;
    void setStyle( Syntax::Theme::DefaultStyle type, const Syntax::ThemeStyle& style );

protected:
    void setName( const QString& name );
};

}; // Syntax

#endif // SYNTAXTHEME_H
