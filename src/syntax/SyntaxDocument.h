#ifndef SYNTAXDOCUMENT_H
#define SYNTAXDOCUMENT_H

#include <QExplicitlySharedDataPointer>

#include "SyntaxHelpers.h"
#include "SyntaxList.h"
#include "SyntaxHighlighting.h"
#include "SyntaxGeneral.h"
#include "SyntaxSpellChecking.h"

namespace Syntax {

class DocumentData;

class Document
{
private:
    QExplicitlySharedDataPointer<Syntax::DocumentData> d;
    
public:
    typedef QList<Syntax::Document> List;
    
    // Required
    SYNTAX_DECL_MEMBER( QString, name ); ///< Name of the syntax document (ie: Asm6502)
    SYNTAX_DECL_MEMBER( QString, localizedName ); ///< Translated display name
    SYNTAX_DECL_MEMBER( QString, section ); ///< Submenu section (ie: Assembly)
    SYNTAX_DECL_MEMBER( Syntax::List, extensions ); ///< List of file extensions
    // Optional
    SYNTAX_DECL_MEMBER( QString, version ); ///< The version of the syntax file
    SYNTAX_DECL_MEMBER( QString, kateVersion );
    SYNTAX_DECL_MEMBER( QString, indenter ); ///< Indenter to use for this syntax
    SYNTAX_DECL_MEMBER( Syntax::List, mimeTypes ); ///< Mimetypes this syntax applie to
    SYNTAX_DECL_MEMBER( int, priority ); ///< Priority for conflict-resolution when the same file suffix has multiple highlighting definitions
    SYNTAX_DECL_MEMBER( bool, hidden ); ///< Hides the syntax from the application's menus
    SYNTAX_DECL_MEMBER( QString, style ); ///< Default style provided by the syntax
    SYNTAX_DECL_MEMBER( QString, author ); ///< Author's name
    SYNTAX_DECL_MEMBER( QString, license ); ///< License; for example: "LGPL"
    SYNTAX_DECL_MEMBER( bool, caseSensitive );
    //SYNTAX_DECL_MEMBER( QString, identifier ); // ?
    SYNTAX_DECL_MEMBER( bool, finalyzed ); ///< Tell if the document has been totally parsed and built
    SYNTAX_DECL_MEMBER( Syntax::Highlighting, highlighting );
    SYNTAX_DECL_MEMBER( Syntax::General, general );
    SYNTAX_DECL_MEMBER( Syntax::SpellChecking, spellChecking );
    
    Document();
    Document( const Syntax::Document& other );
    virtual ~Document();
    
    SYNTAX_DECL_OPERATORS( Document );
    virtual bool operator<( const Syntax::Document& other ) const;
    
    bool open( const QString& filePath, QString* error = 0 );
    
    static QHash<QString, Syntax::Document> open( const QStringList& filePaths, QString* error = 0 );
};

}; // Syntax

#endif // SYNTAXDOCUMENT_H
