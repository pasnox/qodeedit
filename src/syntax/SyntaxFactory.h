#ifndef SYNTAXFACTORY_H
#define SYNTAXFACTORY_H

#include "SyntaxDocument.h"

#include <QString>

class QStringList;

class TextDocument;

namespace Syntax {

class Highlighter;
class Model;

namespace Factory {
    bool load( QString* error = 0 );
    void free();
    
    Syntax::Highlighter* highlighter( const QString& name, TextDocument* textDocument = 0 );
    Syntax::Model* model( QObject* parent = 0 );
}; // Factory

}; // Syntax

#endif // SYNTAXFACTORY_H
