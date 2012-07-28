#include "SyntaxItemData.h"

Syntax::ItemData::ItemData()
{
}

Syntax::ItemData::~ItemData()
{
}

bool Syntax::ItemData::operator==( const Syntax::ItemData& other ) const
{
    return name == other.name &&
        defStyleNum == other.defStyleNum &&
        spellChecking == other.spellChecking &&
        color == other.color &&
        selColor == other.selColor &&
        bold == other.bold &&
        italic == other.italic &&
        strikeOut == other.strikeOut &&
        underline == other.underline &&
        backgroundColor == other.backgroundColor
    ;
}

bool Syntax::ItemData::operator!=( const Syntax::ItemData& other ) const
{
    return !operator==( other );
}
