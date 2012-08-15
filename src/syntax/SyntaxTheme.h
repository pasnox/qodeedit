#ifndef SYNTAXTHEME_H
#define SYNTAXTHEME_H

#include <QExplicitlySharedDataPointer>
#include <QList>
#include <QTextCharFormat>

#include "SyntaxHelpers.h"
#include "QodeEdit.h"

namespace Syntax {

class ThemeData;

class ThemeStyle : public QTextCharFormat
{
};

class Theme
{
    Q_ENUMS( DefaultStyle )
    
private:
    QExplicitlySharedDataPointer<Syntax::ThemeData> d;
    
public:
    typedef QList<Syntax::Theme> List;
    
    Theme( const QString& filePath = QString::null );
    Theme( const Syntax::Theme& other );
    virtual ~Theme();
    
    SYNTAX_DECL_OPERATORS( Theme );
    
    QString name() const;
    
    Syntax::ThemeStyle style( QodeEdit::Style type ) const;
    void setStyle( QodeEdit::Style type, const Syntax::ThemeStyle& style );

protected:
    void setName( const QString& name );
};

}; // Syntax

#endif // SYNTAXTHEME_H
