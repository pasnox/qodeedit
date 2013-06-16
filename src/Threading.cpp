#include "Threading.h"
#include "Tools.h"
#include "syntax/Document.h"

#if QT_VERSION < 0x050000
#include <QtConcurrentRun>
#else
#include <QtConcurrent/QtConcurrentRun>
#endif

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
