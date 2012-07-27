#ifndef SYNTAXRULE_H
#define SYNTAXRULE_H

#include <QList>
#include <QHash>
#include <QString>

namespace Syntax {

class Rule
{
public:
    typedef QList<Syntax::Rule> List;
    
    QString type; ///< Type of the rule
    //
    QString attribute; // hlcchar, hlchex, hlcstringchar, linecontinue, int, detectidentifier, anychar, regexpr, stringdetect, detectspaces, detect2chars, worddetect, hlcoct, rangedetect, detectchar, float, keyword
    QString context; // hlcchar, includerules, hlchex, hlcstringchar, linecontinue, int, detectidentifier, anychar, regexpr, stringdetect, detectspaces, detect2chars, worddetect, hlcoct, rangedetect, detectchar, float, keyword
    QString string; // anychar, regexpr, stringdetect, worddetect, keyword
    QString beginRegion; // anychar, regexpr, stringdetect, detect2chars, rangedetect, detectchar, keyword
    bool firstNonSpace; // anychar, regexpr, stringdetect, detect2chars, detectchar, keyword
    QString char_; // detect2chars, rangedetect, detectchar
    bool lookAhead; // anychar, regexpr, stringdetect, detectspaces, detect2chars, detectchar, keyword
    QString endRegion; // anychar, regexpr, stringdetect, detect2chars, rangedetect, detectchar, keyword
    bool insensitive; // regexpr, stringdetect, keyword
    QString char1; // detect2chars, rangedetect
    int column; // anychar, regexpr, stringdetect, detect2chars, detectchar, keyword
    bool dynamic; // regexpr, stringdetect, detectchar
    bool minimal; // regexpr
    bool includeAttrib; // includerules
    QString region; // regexpr
    QString lineEndContext; // keyword
    QString weakDelimiter; // keyword
    Syntax::Rule::List rules;
    
    Rule();
    virtual ~Rule();
};

}; // Syntax

#endif // SYNTAXRULE_H
