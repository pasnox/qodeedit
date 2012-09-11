/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : QodeEdit.cpp
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#include "QodeEdit.h"
#include "QodeEditConfig.h"

#include <QStringList>
#include <QDir>
#include <QDesktopServices>

class QodeEdit::ManagerData {
public:
    QString userSharedDataFilePath;
};

QodeEdit::Manager::Manager( QObject* parent )
    : QObject( parent ),
        d( new QodeEdit::ManagerData )
{
}

QodeEdit::Manager::~Manager()
{
    delete d;
}

QString QodeEdit::Manager::userSharedDataFilePath( const QString& extended )
{
    return d->userSharedDataFilePath.isEmpty()
        ? QDir::cleanPath( QString( "%1/%2/%3" )
            .arg( QDesktopServices::storageLocation( QDesktopServices::DataLocation ) )
            .arg( QString::fromUtf8( PACKAGE_NAME ) )
            .arg( extended ) )
        : d->userSharedDataFilePath
    ;
}

void QodeEdit::Manager::setUserSharedDataFilePath( const QString& filePath )
{
    d->userSharedDataFilePath = filePath;
}

QString QodeEdit::Manager::userSchemaDefinitionFilePath()
{
    return QodeEdit::Manager::userSharedDataFilePath( "schemas" );
}

QString QodeEdit::Manager::userSyntaxDefinitionFilePath()
{
    return QodeEdit::Manager::userSharedDataFilePath( "syntax" );
}

QStringList QodeEdit::Manager::schemaDefinitionFilePaths()
{
    return QStringList()
        << QodeEdit::Manager::schemaDefinitionFilePath()
        << QodeEdit::Manager::userSchemaDefinitionFilePath()
    ;
}

QStringList QodeEdit::Manager::syntaxDefinitionFilePaths()
{
    return QStringList()
        << QodeEdit::Manager::syntaxDefinitionFilePath()
        << QodeEdit::Manager::userSyntaxDefinitionFilePath()
    ;
}

const char* QodeEdit::Manager::version()
{
    return PACKAGE_VERSION;
}

QString QodeEdit::Manager::versionString()
{
    return PACKAGE_VERSION;
}

QString QodeEdit::Manager::sharedDataFilePath( const QString& extended )
{
    return QDir::cleanPath( QString( "%1/%2" )
        .arg( QString::fromUtf8( PACKAGE_ABSOLUTE_DATA_DIR ) )
        .arg( extended ) );
}

QString QodeEdit::Manager::schemaDefinitionFilePath()
{
    return QodeEdit::Manager::sharedDataFilePath( "schemas" );
}

QString QodeEdit::Manager::syntaxDefinitionFilePath()
{
    return QodeEdit::Manager::sharedDataFilePath( "syntax" );
}
