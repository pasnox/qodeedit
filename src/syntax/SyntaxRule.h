#ifndef SYNTAXRULE_H
#define SYNTAXRULE_H

#include <QExplicitlySharedDataPointer>
#include <QList>
#include <QHash>
#include <QString>

#include "SyntaxHelpers.h"

namespace Syntax {

class RuleData;

class Rule
{
private:
    QExplicitlySharedDataPointer<Syntax::RuleData> d;
    
public:
    typedef QList<Syntax::Rule> List;
    
    enum Type {
        Invalid = -1,
        AnyChar,
        Detect2Chars,
        DetectChar,
        DetectIdentifier,
        DetectSpaces,
        Float,
        HlCChar,
        HlCHex,
        HlCOct,
        HlCStringChar,
        IncludeRules,
        Int,
        Keyword,
        LineContinue,
        RangeDetect,
        RegExpr,
        StringDetect,
        WordDetect
    };
    
    SYNTAX_DECL_MEMBER( QString, type ); ///< Type of the rule
    SYNTAX_DECL_MEMBER( QString, attribute ); // hlcchar, hlchex, hlcstringchar, linecontinue, int, detectidentifier, anychar, regexpr, stringdetect, detectspaces, detect2chars, worddetect, hlcoct, rangedetect, detectchar, float, keyword
    SYNTAX_DECL_MEMBER( QString, context ); // hlcchar, includerules, hlchex, hlcstringchar, linecontinue, int, detectidentifier, anychar, regexpr, stringdetect, detectspaces, detect2chars, worddetect, hlcoct, rangedetect, detectchar, float, keyword
    SYNTAX_DECL_MEMBER( QString, string ); // anychar, regexpr, stringdetect, worddetect, keyword
    SYNTAX_DECL_MEMBER( QString, beginRegion ); // anychar, regexpr, stringdetect, detect2chars, rangedetect, detectchar, keyword
    SYNTAX_DECL_MEMBER( bool, firstNonSpace ); // anychar, regexpr, stringdetect, detect2chars, detectchar, keyword
    SYNTAX_DECL_MEMBER( QString, char_ ); // detect2chars, rangedetect, detectchar
    SYNTAX_DECL_MEMBER( bool, lookAhead ); // anychar, regexpr, stringdetect, detectspaces, detect2chars, detectchar, keyword
    SYNTAX_DECL_MEMBER( QString, endRegion ); // anychar, regexpr, stringdetect, detect2chars, rangedetect, detectchar, keyword
    SYNTAX_DECL_MEMBER( bool, insensitive ); // regexpr, stringdetect, keyword
    SYNTAX_DECL_MEMBER( QString, char1 ); // detect2chars, rangedetect
    SYNTAX_DECL_MEMBER( int, column ); // anychar, regexpr, stringdetect, detect2chars, detectchar, keyword
    SYNTAX_DECL_MEMBER( bool, dynamic ); // regexpr, stringdetect, detectchar
    SYNTAX_DECL_MEMBER( bool, minimal ); // regexpr
    SYNTAX_DECL_MEMBER( bool, includeAttrib ); // includerules
    SYNTAX_DECL_MEMBER( QString, region ); // regexpr
    SYNTAX_DECL_MEMBER( QString, lineEndContext ); // keyword
    SYNTAX_DECL_MEMBER( QString, weakDelimiter ); // keyword
    SYNTAX_DECL_MEMBER( Syntax::Rule::List, rules ); // children rules
    
    Rule();
    Rule( const Syntax::Rule& other );
    virtual ~Rule();
    
    SYNTAX_DECL_OPERATORS( Rule );
    
    Syntax::Rule::Type enumType() const;
};

}; // Syntax

#endif // SYNTAXRULE_H
