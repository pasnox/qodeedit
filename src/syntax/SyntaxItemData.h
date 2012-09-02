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
    
    QE_DECL_SHARED_CLASS( ItemData );
    
    // Required
    QE_DECL_MEMBER( QString, name ); ///< Name of the item data
    QE_DECL_MEMBER( QString, defStyleNum );
    // optional
    QE_DECL_MEMBER( QColor, color );
    QE_DECL_MEMBER( QColor, selColor );
    QE_DECL_MEMBER( bool, italic );
    QE_DECL_MEMBER( bool, bold );
    QE_DECL_MEMBER( bool, underline );
    QE_DECL_MEMBER( bool, strikeOut );
    QE_DECL_MEMBER( QColor, backgroundColor );
    QE_DECL_MEMBER( QColor, selBackgroundColor );
    QE_DECL_MEMBER( bool, spellChecking );
};

}; // Syntax

#endif // SYNTAXITEMDATA_H
