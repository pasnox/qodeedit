/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : Tools.h
** Date      : 2012-09-11T20:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#ifndef TOOLS_H
#define TOOLS_H

#include "QodeEdit.h"

#include <Qt>
#include <QByteArray>
#include <QHash>
#include <QPair>

class QStringList;
class QTextCodec;

namespace Syntax {
    class Document;
}

namespace QodeEdit {

namespace Tools {
    QString rulerToString( QodeEdit::Ruler ruler );
    QodeEdit::Ruler stringToRuler( const QString& string );

    QString marginToString( QodeEdit::Margin margin );
    QodeEdit::Margin stringToMargin( const QString& string );

    QString ruleToString( QodeEdit::Rule rule );
    QodeEdit::Rule stringToRule( const QString& string );

    QString defaultStyleToString( QodeEdit::DefaultStyle style );
    QodeEdit::DefaultStyle stringToDefaultStyle( const QString& string );

    bool stringEquals( const QString& left, const QString& right, Qt::CaseSensitivity sensitivity = Qt::CaseInsensitive );
    bool stringLessThan( const QString& left, const QString& right, Qt::CaseSensitivity sensitivity = Qt::CaseInsensitive );
    bool localeAwareStringEquals( const QString& left, const QString& right );
    bool localeAwareStringLessThan( const QString& left, const QString& right );
    bool versionStringLessThan( const QString& left, const QString& right );
    QTextCodec* textCodec( const QByteArray& name, const QByteArray& data = QByteArray() );

    const QSet<QChar>& stringToSet( const QString& string );
    QStringList listFilesInPath( const QString& path, const QStringList& filters, bool recursive, bool sort = false );
    QStringList listFilesInPaths( const QStringList& paths, const QStringList& filters, bool recursive, bool sort = false );
    QHash<QString, Syntax::Document> parseSyntaxesFiles( const QStringList& paths );
    QHash<QString, QString> bestMatchingMimeTypesIcons( const QHash<QString, QStringList>& mimeTypes, const QString& defaultMimeType, bool processEvents );
    QHash<QString, QPair<QString, QString> > getFilesContentWithTextCodec( const QStringList& filePaths, const QByteArray& textCodec, bool processEvents );

    template <class T> QList<T> startingListItems( const QList<T>& list, int count ) {
        if ( list.count() < count ) {
            return QList<T>();
        }

        return list.mid( 0, count );
    }
} // Tools

} // QodeEdit

#endif // TOOLS_H
