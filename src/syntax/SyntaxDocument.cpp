#include "SyntaxDocument.h"
#include "SyntaxHighlighting.h"
#include "SyntaxGeneral.h"

// SyntaxLanguage

class Syntax::Language {
public:
    // Required
    QString name; ///< Name of the syntax document (ie: Asm6502)
    QString localizedName; ///< Translated display name
    QString section; ///< Submenu section (ie: Assembly)
    Syntax::List suffixes; ///< List of file suffixes
    // Optional
    QString version;
    QString kateVersion;
    QString indenter; ///< Indenter to use for this syntax
    Syntax::List mimeTypes; ///< Mimetypes this syntax applie to
    int priority; ///< Priority for conflict-resolution when the same file suffix has multiple highlighting definitions
    bool hidden; ///< Hides the syntax from the application's menus
    QString style; ///< Default style provided by the syntax
    QString author; ///< Author's name
    QString license; ///< License; for example: "LGPL"
    //QString identifier; // ?
    
    Syntax::Highlighting highlighting;
    Syntax::General general;
};

// SyntaxDocumentPrivate

class Syntax::DocumentPrivate {
public:
    Syntax::Language language;
    
    DocumentPrivate( Syntax::Document* _document )
        : document( _document )
    {
        Q_ASSERT( document );
    }

private:
    Syntax::Document* document;
};

// SyntaxDocument

Syntax::Document::Document( const QString& filePath )
    : d( new Syntax::DocumentPrivate( this ) )
{
}

Syntax::Document::~Document()
{
    delete d;
}
