#ifndef SYNTAXDOCUMENT_H
#define SYNTAXDOCUMENT_H

#include "SyntaxList.h"
#include "SyntaxHighlighting.h"
#include "SyntaxGeneral.h"
#include "SyntaxSpellChecking.h"

namespace Syntax {

class Document
{
public:
    typedef QList<Syntax::Document> List;
    
    // Required
    QString name; ///< Name of the syntax document (ie: Asm6502)
    QString localizedName; ///< Translated display name
    QString section; ///< Submenu section (ie: Assembly)
    Syntax::List extensions; ///< List of file extensions
    // Optional
    QString version; ///< The version of the syntax file
    QString kateVersion;
    QString indenter; ///< Indenter to use for this syntax
    Syntax::List mimeTypes; ///< Mimetypes this syntax applie to
    int priority; ///< Priority for conflict-resolution when the same file suffix has multiple highlighting definitions
    bool hidden; ///< Hides the syntax from the application's menus
    QString style; ///< Default style provided by the syntax
    QString author; ///< Author's name
    QString license; ///< License; for example: "LGPL"
    bool caseSensitive;
    //QString identifier; // ?
    bool finalyzed; ///< Tell if the document has been totally parsed and built
    
    Syntax::Highlighting highlighting;
    Syntax::General general;
    Syntax::SpellChecking spellChecking;
    
    Document();
    virtual ~Document();
    
    virtual bool operator==( const Syntax::Document& other ) const;
    virtual bool operator!=( const Syntax::Document& other ) const;
    virtual bool operator<( const Syntax::Document& other ) const;
    
    bool open( const QString& filePath, QString* error = 0 );
    
    static QHash<QString, Syntax::Document> open( const QStringList& filePaths, QString* error = 0 );
};

}; // Syntax

#endif // SYNTAXDOCUMENT_H
