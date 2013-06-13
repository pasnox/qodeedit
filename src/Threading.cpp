#include "Threading.h"
#include "Tools.h"
#include "syntax/Document.h"

#include <QtConcurrent/QtConcurrentRun>

QFuture<QStringList> QodeEdit::Threading::listFilesInPaths( const QStringList& paths, const QStringList& filters, bool recursive, bool sort )
{
    return QtConcurrent::run( QodeEdit::Tools::listFilesInPaths, paths, filters, recursive, sort );
}

QFuture<QHash<QString, Syntax::Document> > QodeEdit::Threading::parseSyntaxesFiles( const QStringList& paths )
{
    return QtConcurrent::run( QodeEdit::Tools::parseSyntaxesFiles, paths );
}

QFuture<QHash<QString, QString> > QodeEdit::Threading::bestMatchingMimeTypesIcons( const QHash<QString, QStringList>& mimeTypes, const QString& defaultMimeType )
{
    return QtConcurrent::run( QodeEdit::Tools::bestMatchingMimeTypesIcons, mimeTypes, defaultMimeType, false );
}

QFuture<QHash<QString, QPair<QString, QString> > > QodeEdit::Threading::getFilesContentWithTextCodec( const QStringList& filePaths, const QByteArray& textCodec )
{
    return QtConcurrent::run( QodeEdit::Tools::getFilesContentWithTextCodec, filePaths, textCodec, false );
}
