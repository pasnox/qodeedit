/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : Factory.h
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#ifndef FACTORY_H
#define FACTORY_H

#include "Document.h"

#include <QString>

class QStringList;
class QFileInfo;
class QUrl;

class TextDocument;

namespace Syntax {

class Highlighter;
class Model;

namespace Factory {
    bool load( QString* error = 0 );
    void free();
    
    QStringList availableSyntaxes();
    
    QString mimeTypeForFile( const QString& fileName );
    QString mimeTypeForFile( const QFileInfo& fileInfo );
    QString mimeTypeForData( const QByteArray& data );
    QString mimeTypeForData( QIODevice* device );
    QString mimeTypeForFileNameAndData( const QString& fileName, QIODevice* device );
    QString mimeTypeForFileNameAndData( const QString& fileName, const QByteArray& data );
    QString mimeTypeForUrl( const QUrl& url );
    QStringList mimeTypesForFileName( const QString& fileName );
    
    Syntax::Document document( const QString& syntaxName );
    
    Syntax::Highlighter* highlighter( const QString& syntaxName, const QString& syntaxThemeName, TextDocument* textDocument = 0 );
    Syntax::Highlighter* highlighterForFilePath( const QString& filePath, TextDocument* textDocument = 0 );
    Syntax::Highlighter* highlighterForMimeType( const QString& mimeType, TextDocument* textDocument = 0 );
    
    Syntax::Model* model( QObject* parent = 0 );
}; // Factory

}; // Syntax

#endif // FACTORY_H
