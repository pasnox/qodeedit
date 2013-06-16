/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : QodeEdit.h
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#ifndef QODEEDIT_H
#define QODEEDIT_H

#include <qglobal.h>

class QMetaObject;

#ifndef Q_MOC_RUN
namespace
#else
class
#endif
QodeEdit {
#if defined( Q_MOC_RUN )
    Q_GADGET
    Q_ENUMS( Ruler Margin Rule Style )

public:
#endif

    enum Ruler {
        NoRuler = -1,
        LineRuler,
        BackgroundRuler
    };

    // the order is important as it defined the presentation order of the margins
    enum Margin {
        InvalidMargin = -1,
        BookmarkMargin,
        NumberMargin,
        FoldMargin,
        RevisionMargin,
        SpaceMargin
    };

    enum Rule {
        InvalidRule = -1,
        KeywordRule,
        FloatRule,
        HlCOctRule,
        HlCHexRule,
        HlCFloatRule,
        IntRule,
        DetectCharRule,
        Detect2CharsRule,
        AnyCharRule,
        StringDetectRule,
        WordDetectRule,
        RegExprRule,
        LineContinueRule,
        HlCStringCharRule,
        RangeDetectRule,
        HlCCharRule,
        DetectSpacesRule,
        DetectIdentifierRule,
        IncludeRulesRule
    };

    enum DefaultStyle {
        InvalidStyle = -1,
        NormalStyle,
        KeywordStyle,
        DataTypeStyle,
        DecValStyle,
        BaseNStyle,
        FloatStyle,
        CharStyle,
        StringStyle,
        CommentStyle,
        OthersStyle,
        AlertStyle,
        FunctionStyle,
        RegionMarkerStyle,
        ErrorStyle
    };

    const QMetaObject* metaObject();
} // QodeEdit

#endif // QODEEDIT_H
