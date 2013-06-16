/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : Document.h
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "Helpers.h"
#include "List.h"
#include "Highlighting.h"
#include "General.h"
#include "SpellChecking.h"

namespace Syntax {

class DocumentData;

class Document
{
private:
    QExplicitlySharedDataPointer<Syntax::DocumentData> d;

public:
    typedef QList<Syntax::Document> List;

    QE_DECL_SHARED_CLASS( Document, Syntax );
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
    QE_DECL_MEMBER( QSet<QChar>, defaultDeliminator );
    QE_DECL_MEMBER( QString, localizedName ); ///< Translated display name

    QE_DECL_MEMBER( bool, finalyzed ); ///< Tell if the document has been totally parsed and built

    QE_DECL_MEMBER( Syntax::Highlighting, highlighting );
    QE_DECL_MEMBER( Syntax::General, general );
    QE_DECL_MEMBER( Syntax::SpellChecking, spellChecking );

    bool open( const QString& filePath, QString* error = 0 );

    static QHash<QString, Syntax::Document> open( const QStringList& filePaths, QString* error = 0 );
};

} // Syntax

#endif // DOCUMENT_H
