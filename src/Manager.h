#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QMetaObject>
#include <QHash>

class QStringList;
class QFileInfo;
class QIODevice;
class QUrl;

class TextDocument;

namespace Syntax {
    class Document;
    class Highlighter;
    class Model;
}

namespace Theme {
    class Schema;
}

namespace QodeEdit {

class ManagerData;

class Manager : public QObject
{
    Q_OBJECT
    friend class QodeEdit::ManagerData;

private:
    QodeEdit::ManagerData* d;

public:
    Manager( QObject* parent = 0 );
    virtual ~Manager();

    void initialize();
    void deinitialize();

    QString userSharedDataFilePath( const QString& extended = QString::null ) const;
    void setUserSharedDataFilePath( const QString& filePath );

    QString userSchemaDefinitionFilePath() const;
    QString userSyntaxDefinitionFilePath() const;

    QStringList schemaDefinitionFilePaths() const;
    QStringList syntaxDefinitionFilePaths() const;

    QString mimeTypeForFile( const QString& fileName ) const;
    QString mimeTypeForFile( const QFileInfo& fileInfo ) const;
    QString mimeTypeForData( const QByteArray& data ) const;
    QString mimeTypeForData( QIODevice* device ) const;
    QString mimeTypeForFileNameAndData( const QString& fileName, QIODevice* device ) const;
    QString mimeTypeForFileNameAndData( const QString& fileName, const QByteArray& data ) const;
    QString mimeTypeForUrl( const QUrl& url ) const;
    QStringList mimeTypesForFileName( const QString& fileName ) const;

    QStringList availableSyntaxesList() const;
    QStringList availableSchemasList() const;

    QHash<QString, Syntax::Document> availableSyntaxes() const;
    Syntax::Document syntax( const QString& name );

    QHash<QString, Theme::Schema> availableSchemas() const;
    Theme::Schema schema( const QString& name );

    Syntax::Model* model( QObject* parent = 0 );

    Syntax::Highlighter* highlighter( const QString& syntaxName, TextDocument* textDocument = 0 ) const;
    Syntax::Highlighter* highlighterForFilePath( const QString& filePath, TextDocument* textDocument = 0 ) const;
    Syntax::Highlighter* highlighterForMimeType( const QString& mimeType, TextDocument* textDocument = 0 ) const;

    static QString sharedDataFilePath( const QString& extended = QString::null );
    static QString schemaDefinitionFilePath();
    static QString syntaxDefinitionFilePath();

    static const char* version();
    static QString versionString();

signals:
    void syntaxesUpdated();
    void schemasUpdated();
    void updated();
    void error( const QString& message );
};

} // QodeEdit

#endif // MANAGER_H
