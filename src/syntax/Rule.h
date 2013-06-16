/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : Rule.h
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#ifndef RULE_H
#define RULE_H

#include <QExplicitlySharedDataPointer>
#include <QList>
#include <QHash>
#include <QString>
#include <QVariant>

#include "Helpers.h"
#include "QodeEdit.h"

namespace Syntax {

class RuleData;
class CommonRuleData;
class CommonRulesRuleData;
class CommonStringRuleData;

class KeywordRuleData;
typedef Syntax::CommonRulesRuleData FloatRuleData;
typedef Syntax::CommonRuleData HlCOctRuleData;
typedef Syntax::CommonRuleData HlCHexRuleData;
typedef Syntax::CommonRuleData HlCFloatRuleData;
typedef Syntax::CommonRulesRuleData IntRuleData;
class DetectCharRuleData;
class Detect2CharsRuleData;
class AnyCharRuleData;
typedef Syntax::CommonStringRuleData StringDetectRuleData;
typedef Syntax::CommonStringRuleData WordDetectRuleData;
class RegExprRuleData;
typedef Syntax::CommonRuleData LineContinueRuleData;
typedef Syntax::CommonRuleData HlCStringCharRuleData;
class RangeDetectRuleData;
typedef Syntax::CommonRuleData HlCCharRuleData;
typedef Syntax::CommonRuleData DetectSpacesRuleData;
typedef Syntax::CommonRuleData DetectIdentifierRuleData;
class IncludeRulesRuleData;

class CommonRule;
class KeywordRule;
class FloatRule;
class HlCOctRule;
class HlCHexRule;
class HlCFloatRule;
class IntRule;
class DetectCharRule;
class Detect2CharsRule;
class AnyCharRule;
class StringDetectRule;
class WordDetectRule;
class RegExprRule;
class LineContinueRule;
class HlCStringCharRule;
class RangeDetectRule;
class HlCCharRule;
class DetectSpacesRule;
class DetectIdentifierRule;
class IncludeRulesRule;

class Rule
{
protected:
    QExplicitlySharedDataPointer<Syntax::RuleData> d;

public:
    typedef QList<Syntax::Rule> List;

    QE_DECL_SHARED_CLASS( Rule, Syntax );

    QE_DECL_MEMBER( QodeEdit::Rule, type );

    bool isNull() const;
    QString context() const;
    Syntax::Rule::List rules() const;

    Syntax::CommonRule toCommon() const;
    Syntax::KeywordRule toKeyword() const;
    Syntax::FloatRule toFloat() const;
    Syntax::HlCOctRule toHlCOct() const;
    Syntax::HlCHexRule toHlCHex() const;
    Syntax::HlCFloatRule toHlCFloat() const;
    Syntax::IntRule toInt() const;
    Syntax::DetectCharRule toDetectChar() const;
    Syntax::Detect2CharsRule toDetect2Chars() const;
    Syntax::AnyCharRule toAnyChar() const;
    Syntax::StringDetectRule toStringDetect() const;
    Syntax::WordDetectRule toWordDetect() const;
    Syntax::RegExprRule toRegExpr() const;
    Syntax::LineContinueRule toLineContinue() const;
    Syntax::HlCStringCharRule toHlCStringChar() const;
    Syntax::RangeDetectRule toRangeDetect() const;
    Syntax::HlCCharRule toHlCChar() const;
    Syntax::DetectSpacesRule toDetectSpaces() const;
    Syntax::DetectIdentifierRule toDetectIdentifier() const;
    Syntax::IncludeRulesRule toIncludeRules() const;

    static Syntax::Rule create( QodeEdit::Rule type, const QHash<QString, QVariant>& data );
};

class CommonRule : public Syntax::Rule
{
public:
    QE_DECL_SHARED_CLASS( CommonRule, Syntax );

    QE_DECL_MEMBER( QString, attribute );
    QE_DECL_MEMBER( QString, context );
    QE_DECL_MEMBER( QString, beginRegion );
    QE_DECL_MEMBER( QString, endRegion );
    QE_DECL_MEMBER( bool, lookAhead );
    QE_DECL_MEMBER( bool, firstNonSpace );
    QE_DECL_MEMBER( int, column );
};

class CommonRulesRule : public Syntax::CommonRule
{
public:
    QE_DECL_SHARED_CLASS( CommonRulesRule, Syntax );

    QE_DECL_MEMBER( Syntax::Rule::List, rules );
};

class KeywordRule : public Syntax::CommonRule
{
public:
    QE_DECL_SHARED_CLASS( KeywordRule, Syntax );

    QE_DECL_MEMBER( bool, insensitive );
    QE_DECL_MEMBER( QString, string );
    QE_DECL_MEMBER( QString, weakDelimiter );
};

class FloatRule : public Syntax::CommonRulesRule
{
public:
    QE_DECL_SHARED_CLASS( FloatRule, Syntax );
};

class HlCOctRule : public Syntax::CommonRule
{
public:
    QE_DECL_SHARED_CLASS( HlCOctRule, Syntax );
};

class HlCHexRule : public Syntax::CommonRule
{
public:
    QE_DECL_SHARED_CLASS( HlCHexRule, Syntax );
};

class HlCFloatRule : public Syntax::CommonRule
{
public:
    QE_DECL_SHARED_CLASS( HlCFloatRule, Syntax );
};

class IntRule : public Syntax::CommonRulesRule
{
public:
    QE_DECL_SHARED_CLASS( IntRule, Syntax );
};

class DetectCharRule : public Syntax::CommonRule
{
public:
    QE_DECL_SHARED_CLASS( DetectCharRule, Syntax );

    QE_DECL_MEMBER( QChar, char_ );
    QE_DECL_MEMBER( bool, dynamic );
};

class Detect2CharsRule : public Syntax::DetectCharRule
{
public:
    QE_DECL_SHARED_CLASS( Detect2CharsRule, Syntax );

    QE_DECL_MEMBER( QChar, char1 );
};

class AnyCharRule : public Syntax::CommonRule
{
public:
    QE_DECL_SHARED_CLASS( AnyCharRule, Syntax );

    QE_DECL_MEMBER( QString, string );
};

class StringDetectRule : public Syntax::CommonRule
{
public:
    QE_DECL_SHARED_CLASS( StringDetectRule, Syntax );

    QE_DECL_MEMBER( QString, string );
    QE_DECL_MEMBER( bool, insensitive );
    QE_DECL_MEMBER( bool, dynamic );
};

class WordDetectRule : public Syntax::StringDetectRule
{
public:
    QE_DECL_SHARED_CLASS( WordDetectRule, Syntax );

    QE_DECL_MEMBER( QString, string );
    QE_DECL_MEMBER( bool, insensitive );
    QE_DECL_MEMBER( bool, dynamic );
};

class RegExprRule : public Syntax::StringDetectRule
{
public:
    QE_DECL_SHARED_CLASS( RegExprRule, Syntax );

    QE_DECL_MEMBER( bool, minimal );
};

class LineContinueRule : public Syntax::CommonRule
{
public:
    QE_DECL_SHARED_CLASS( LineContinueRule, Syntax );
};

class HlCStringCharRule : public Syntax::CommonRule
{
public:
    QE_DECL_SHARED_CLASS( HlCStringCharRule, Syntax );
};

class RangeDetectRule : public Syntax::CommonRule
{
public:
    QE_DECL_SHARED_CLASS( RangeDetectRule, Syntax );

    QE_DECL_MEMBER( QChar, char_ );
    QE_DECL_MEMBER( QChar, char1 );
};

class HlCCharRule : public Syntax::CommonRule
{
public:
    QE_DECL_SHARED_CLASS( HlCCharRule, Syntax );
};

class DetectSpacesRule : public Syntax::CommonRule
{
public:
    QE_DECL_SHARED_CLASS( DetectSpacesRule, Syntax );
};

class DetectIdentifierRule : public Syntax::CommonRule
{
public:
    QE_DECL_SHARED_CLASS( DetectIdentifierRule, Syntax );
};

class IncludeRulesRule : public Syntax::Rule
{
public:
    QE_DECL_SHARED_CLASS( IncludeRulesRule, Syntax );

    QE_DECL_MEMBER( QString, context );
    QE_DECL_MEMBER( bool, includeAttrib );
    QE_DECL_MEMBER( Syntax::Rule::List, rules );
};

} // Syntax

#endif // RULE_H
