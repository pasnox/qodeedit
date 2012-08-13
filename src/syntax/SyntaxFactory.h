#ifndef SYNTAXFACTORY_H
#define SYNTAXFACTORY_H

#include "SyntaxDocument.h"

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
    
    Syntax::Document document( const QString& name );
    
    Syntax::Highlighter* highlighter( const QString& name, TextDocument* textDocument = 0 );
    Syntax::Highlighter* highlighterForFilePath( const QString& filePath, TextDocument* textDocument = 0 );
    Syntax::Highlighter* highlighterForMimeType( const QString& mimeType, TextDocument* textDocument = 0 );
    
    Syntax::Model* model( QObject* parent = 0 );
}; // Factory

}; // Syntax

#endif // SYNTAXFACTORY_H
