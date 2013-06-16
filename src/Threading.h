#ifndef THREADING_H
#define THREADING_H

#include <QStringList>
#include <QFuture>

namespace Syntax {
    class Document;
}

namespace QodeEdit {

namespace Threading
{
    QFuture<QStringList> listFilesInPaths( const QStringList& paths, const QStringList& filters, bool recursive, bool sort = true );
    QFuture<QHash<QString, Syntax::Document> > parseSyntaxesFiles( const QStringList& paths );
    QFuture<QHash<QString, QString> > bestMatchingMimeTypesIcons( const QHash<QString, QStringList>& mimeTypes, const QString& defaultMimeType );
    QFuture<QHash<QString, QPair<QString, QString> > > getFilesContentWithTextCodec( const QStringList& filePaths, const QByteArray& textCodec );
} // Threading

} // QodeEdit

#endif // THREADING_H
