#ifndef QODEEDIT_H
#define QODEEDIT_H

#include <QString>

class QStringList;

namespace QodeEdit
{
    const char* version();
    QString versionString();
    
    QString sharedDataFilePath( const QString& extended = QString::null );
    
    QString userSharedDataFilePath( const QString& extended = QString::null );
    void setUserSharedDataFilePath( const QString& filePath );
    
    QString schemaDefinitionFilePath();
    QString syntaxDefinitionFilePath();
    
    QString userSchemaDefinitionFilePath();
    QString userSyntaxDefinitionFilePath();
    
    QStringList schemaDefinitionFilePaths();
    QStringList syntaxDefinitionFilePaths();
    
    bool stringEquals( const QString& left, const QString& right, Qt::CaseSensitivity sensitivity = Qt::CaseInsensitive );
    bool stringLessThan( const QString& left, const QString& right, Qt::CaseSensitivity sensitivity = Qt::CaseInsensitive );
    bool localeAwareStringEquals( const QString& left, const QString& right );
    bool localeAwareStringLessThan( const QString& left, const QString& right );
    bool versionStringLessThan( const QString& left, const QString& right );
};

#endif // QODEEDIT_H
