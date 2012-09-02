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
    
    QE_DECL_SHARED_CLASS( Document );
    virtual bool operator<( const Syntax::Document& other ) const;
    
    // Required
    QE_DECL_MEMBER( QString, name ); ///< Name of the syntax document (ie: Asm6502)
    QE_DECL_MEMBER( QString, section ); ///< Submenu section (ie: Assembly)
    QE_DECL_MEMBER( Syntax::List, extensions ); ///< List of file extensions
    QE_DECL_MEMBER( QString, version ); ///< The version of the syntax file
    QE_DECL_MEMBER( QString, kateVersion );
    // Optional
    QE_DECL_MEMBER( QString, style ); ///< Default style provided by the syntax
    QE_DECL_MEMBER( Syntax::List, mimeType ); ///< Mimetypes this syntax applie to
    QE_DECL_MEMBER( bool, caseSensitive );
    QE_DECL_MEMBER( int, priority ); ///< Priority for conflict-resolution when the same file suffix has multiple highlighting definitions
    QE_DECL_MEMBER( QString, author ); ///< Author's name
    QE_DECL_MEMBER( QString, license ); ///< License; for example: "LGPL"
    QE_DECL_MEMBER( QString, indenter ); ///< Indenter to use for this syntax
    QE_DECL_MEMBER( bool, hidden ); ///< Hides the syntax from the application's menus
    // Others
    //QE_DECL_MEMBER( QString, identifier ); // ?
    QE_DECL_MEMBER( QString, defaultDeliminator );
    QE_DECL_MEMBER( QString, localizedName ); ///< Translated display name
    
    QE_DECL_MEMBER( bool, finalyzed ); ///< Tell if the document has been totally parsed and built
    
    QE_DECL_MEMBER( Syntax::Highlighting, highlighting );
    QE_DECL_MEMBER( Syntax::General, general );
    QE_DECL_MEMBER( Syntax::SpellChecking, spellChecking );
    
    bool open( const QString& filePath, QString* error = 0 );
    
    static QHash<QString, Syntax::Document> open( const QStringList& filePaths, QString* error = 0 );
};

}; // Syntax

#endif // SYNTAXDOCUMENT_H
