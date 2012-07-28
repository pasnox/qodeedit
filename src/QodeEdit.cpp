#include "QodeEdit.h"
#include "main.h"

#include <QStringList>
#include <QDir>
#include <QDesktopServices>

namespace QodeEdit {
    QString mCustomSchemaFilePath;
    QString mCustomSyntaxFilePath;
};

const char* QodeEdit::version()
{
    return PACKAGE_VERSION;
}

QString QodeEdit::versionString()
{
    return PACKAGE_VERSION;
}

QString QodeEdit::sharedDataFilePath( const QString& extended )
{
    return QDir::cleanPath( QString( "%1/%2" )
        .arg( PACKAGE_ABSOLUTE_DATA_DIR )
        .arg( extended )
    );
}

QString QodeEdit::userSharedDataFilePath( const QString& extended )
{
    return QDir::cleanPath( QString( "%1/%2/%3" )
        .arg( QDesktopServices::storageLocation( QDesktopServices::DataLocation ) )
        .arg( PACKAGE_NAME )
        .arg( extended )
    );
}

QString QodeEdit::schemaDefinitionFilePath()
{
    return QodeEdit::sharedDataFilePath( "schemas" );
}

QString QodeEdit::syntaxDefinitionFilePath()
{
    return QodeEdit::sharedDataFilePath( "syntax" );
}

QString QodeEdit::customSchemaDefinitionFilePath()
{
    return QodeEdit::mCustomSchemaFilePath.isEmpty()
        ? QodeEdit::userSharedDataFilePath( "schemas" )
        : QodeEdit::mCustomSchemaFilePath
    ;
}

QString QodeEdit::customSyntaxDefinitionFilePath()
{
    return QodeEdit::mCustomSyntaxFilePath.isEmpty()
        ? QodeEdit::userSharedDataFilePath( "syntax" )
        : QodeEdit::mCustomSyntaxFilePath
    ;
}

QStringList QodeEdit::schemaDefinitionFilePaths()
{
    const QString custom = QodeEdit::customSchemaDefinitionFilePath();
    QStringList paths;
    
    paths << QodeEdit::schemaDefinitionFilePath();
    
    if ( !custom.isEmpty() ) {
        paths << custom;
    }
    
    return paths;
}

QStringList QodeEdit::syntaxDefinitionFilePaths()
{
    const QString custom = QodeEdit::customSyntaxDefinitionFilePath();
    QStringList paths;
    
    paths << QodeEdit::syntaxDefinitionFilePath();
    
    if ( !custom.isEmpty() ) {
        paths << custom;
    }
    
    return paths;
}
