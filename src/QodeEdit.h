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
        NoRuler = 0x0,
        LineRuler = 0x1,
        BackgroundRuler = 0x2
    };
    
    // the order is important as it defined the presentation order of the margins
    enum Margin {
        InvalidMargin = -1,
        BookmarkMargin = 0, // done
        NumberMargin = 1, // done
        FoldMargin = 2,
        RevisionMargin = 3, // done
        SpaceMargin = 4, // done
    };
    
    enum Rule {
        InvalidRule = -1,
        AnyCharRule,
        Detect2CharsRule,
        DetectCharRule,
        DetectIdentifierRule,
        DetectSpacesRule,
        FloatRule,
        HlCCharRule,
        HlCHexRule,
        HlCOctRule,
        HlCStringCharRule,
        IncludeRule,
        IntRule,
        KeywordRule,
        LineContinueRule,
        RangeDetectRule,
        RegExprRule,
        StringDetectRule,
        WordDetectRule
    };
    
    enum Style {
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
