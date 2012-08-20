#ifndef QODEEDIT_H
#define QODEEDIT_H

#include <QObject>

class QStringList;

class QodeEdit : public QObject
{
    Q_OBJECT
    Q_ENUMS( Ruler Margin Rule Style )
    
public:
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
    
    static QString rulerToString( QodeEdit::Ruler ruler );
    static QodeEdit::Ruler stringToRuler( const QString& string );
    
    static QString marginToString( QodeEdit::Margin margin );
    static QodeEdit::Margin stringToMargin( const QString& string );
    
    static QString ruleToString( QodeEdit::Rule rule );
    static QodeEdit::Rule stringToRule( const QString& string );
    
    static QString styleToString( QodeEdit::Style style );
    static QodeEdit::Style stringToStyle( const QString& string );
    
    static const char* version();
    static QString versionString();
    
    static QString sharedDataFilePath( const QString& extended = QString::null );
    
    static QString userSharedDataFilePath( const QString& extended = QString::null );
    static void setUserSharedDataFilePath( const QString& filePath );
    
    static QString schemaDefinitionFilePath();
    static QString syntaxDefinitionFilePath();
    
    static QString userSchemaDefinitionFilePath();
    static QString userSyntaxDefinitionFilePath();
    
    static QStringList schemaDefinitionFilePaths();
    static QStringList syntaxDefinitionFilePaths();
    
    static bool stringEquals( const QString& left, const QString& right, Qt::CaseSensitivity sensitivity = Qt::CaseInsensitive );
    static bool stringLessThan( const QString& left, const QString& right, Qt::CaseSensitivity sensitivity = Qt::CaseInsensitive );
    static bool localeAwareStringEquals( const QString& left, const QString& right );
    static bool localeAwareStringLessThan( const QString& left, const QString& right );
    static bool versionStringLessThan( const QString& left, const QString& right );
};

#endif // QODEEDIT_H
