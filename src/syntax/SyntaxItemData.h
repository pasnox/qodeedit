#ifndef SYNTAXITEMDATA_H
#define SYNTAXITEMDATA_H

#include <QExplicitlySharedDataPointer>
#include <QHash>
#include <QString>
#include <QColor>

#include "SyntaxHelpers.h"

namespace Syntax {

class ItemDataData;

class ItemData
{
private:
    QExplicitlySharedDataPointer<Syntax::ItemDataData> d;
    
public:
    typedef QHash<QString, Syntax::ItemData> Hash;
    
    // Required
    SYNTAX_DECL_MEMBER( QString, name ); ///< Name of the item data
    SYNTAX_DECL_MEMBER( QString, defStyleNum );
    // optional
    SYNTAX_DECL_MEMBER( QColor, color );
    SYNTAX_DECL_MEMBER( QColor, selColor );
    SYNTAX_DECL_MEMBER( bool, italic );
    SYNTAX_DECL_MEMBER( bool, bold );
    SYNTAX_DECL_MEMBER( bool, underline );
    SYNTAX_DECL_MEMBER( bool, strikeOut );
    SYNTAX_DECL_MEMBER( QColor, backgroundColor );
    SYNTAX_DECL_MEMBER( QColor, selBackgroundColor );
    SYNTAX_DECL_MEMBER( bool, spellChecking );
    
    ItemData();
    ItemData( const Syntax::ItemData& other );
    virtual ~ItemData();
    
    SYNTAX_DECL_OPERATORS( ItemData );
};

}; // Syntax

#endif // SYNTAXITEMDATA_H
