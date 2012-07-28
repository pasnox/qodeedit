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
    
    QString schemaDefinitionFilePath();
    QString syntaxDefinitionFilePath();
    
    QString customSchemaDefinitionFilePath();
    QString customSyntaxDefinitionFilePath();
    
    QStringList schemaDefinitionFilePaths();
    QStringList syntaxDefinitionFilePaths();
};

#endif // QODEEDIT_H
