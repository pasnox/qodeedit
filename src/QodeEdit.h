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

#include <QObject>

class QStringList;

namespace QodeEdit {

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

enum Style {
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

class ManagerData;

class Manager : public QObject
{
    Q_OBJECT
    Q_ENUMS( QodeEdit::Ruler QodeEdit::Margin QodeEdit::Rule QodeEdit::Style )
    
private:
    QodeEdit::ManagerData* d;
    
public:
    Manager( QObject* parent = 0 );
    virtual ~Manager();
    
    QString userSharedDataFilePath( const QString& extended = QString::null );
    void setUserSharedDataFilePath( const QString& filePath );
    
    QString userSchemaDefinitionFilePath();
    QString userSyntaxDefinitionFilePath();
    
    QStringList schemaDefinitionFilePaths();
    QStringList syntaxDefinitionFilePaths();
    
    static QString sharedDataFilePath( const QString& extended = QString::null );
    static QString schemaDefinitionFilePath();
    static QString syntaxDefinitionFilePath();
    
    static const char* version();
    static QString versionString();
}; // Manager

}; // QodeEdit

#endif // QODEEDIT_H
