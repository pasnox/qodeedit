#include "QodeEdit.h"
#include "main.h"

#include <QStringList>
#include <QDir>
#include <QDesktopServices>

namespace QodeEdit {
    QString mUserSharedDataFilePath;
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
        .arg( extended ) );
}

QString QodeEdit::userSharedDataFilePath( const QString& extended )
{
    return mUserSharedDataFilePath.isEmpty()
        ? QDir::cleanPath( QString( "%1/%2/%3" )
            .arg( QDesktopServices::storageLocation( QDesktopServices::DataLocation ) )
            .arg( PACKAGE_NAME )
            .arg( extended ) )
        : mUserSharedDataFilePath
    ;
}

void QodeEdit::setUserSharedDataFilePath( const QString& filePath )
{
    mUserSharedDataFilePath = filePath;
}

QString QodeEdit::schemaDefinitionFilePath()
{
    return QodeEdit::sharedDataFilePath( "schemas" );
}

QString QodeEdit::syntaxDefinitionFilePath()
{
    return QodeEdit::sharedDataFilePath( "syntax" );
}

QString QodeEdit::userSchemaDefinitionFilePath()
{
    return QodeEdit::userSharedDataFilePath( "schemas" );
}

QString QodeEdit::userSyntaxDefinitionFilePath()
{
    return QodeEdit::userSharedDataFilePath( "syntax" );
}

QStringList QodeEdit::schemaDefinitionFilePaths()
{
    return QStringList()
        << QodeEdit::schemaDefinitionFilePath()
        << QodeEdit::userSchemaDefinitionFilePath()
    ;
}

QStringList QodeEdit::syntaxDefinitionFilePaths()
{
    return QStringList()
        << QodeEdit::syntaxDefinitionFilePath()
        << QodeEdit::userSyntaxDefinitionFilePath()
    ;
}
