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

bool QodeEdit::stringEquals( const QString& left, const QString& right, Qt::CaseSensitivity sensitivity )
{
    return QString::compare( left, right, sensitivity ) == 0;
}

bool QodeEdit::stringLessThan( const QString& left, const QString& right, Qt::CaseSensitivity sensitivity )
{
    return QString::compare( left, right, sensitivity ) < 0;
}

bool QodeEdit::localeAwareStringEquals( const QString& left, const QString& right )
{
    return QString::localeAwareCompare( left, right ) == 0;
}

bool QodeEdit::localeAwareStringLessThan( const QString& left, const QString& right )
{
    return QString::localeAwareCompare( left, right ) < 0;
}

bool QodeEdit::versionStringLessThan( const QString& left, const QString& right )
{
    if ( left == right ) {
        return false;
    }
    
    const QStringList leftParts = left.split( "." );
    const QStringList rightParts = right.split( "." );
    
    // major
    if ( leftParts.value( 0 ).toInt() != rightParts.value( 0 ).toInt() ) {
        return leftParts.value( 0 ).toInt() < rightParts.value( 0 ).toInt();
    }
    // minor
    else if ( leftParts.value( 1 ).toInt() != rightParts.value( 1 ).toInt() ) {
        return leftParts.value( 1 ).toInt() < rightParts.value( 1 ).toInt();
    }
    // patch
    else if ( leftParts.value( 2 ).toInt() != rightParts.value( 2 ).toInt() ) {
        return leftParts.value( 2 ).toInt() < rightParts.value( 2 ).toInt();
    }
    // build
    else if ( leftParts.value( 3 ).toInt() != rightParts.value( 3 ).toInt() ) {
        return leftParts.value( 3 ).toInt() < rightParts.value( 3 ).toInt();
    }
    // extra
    else if ( leftParts.value( 4 ).isEmpty() && !rightParts.value( 4 ).isEmpty() ) {
        return false;
    }
    // extra
    else if ( !leftParts.value( 4 ).isEmpty() && rightParts.value( 4 ).isEmpty() ) {
        return true;
    }
    
    // extra
    return leftParts.value( 4 ) < rightParts.value( 4 ); // not the best but afaik ;)
}
