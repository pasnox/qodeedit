/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : SpellChecking.cpp
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#include "SpellChecking.h"

class Syntax::SpellCheckingData : public QSharedData
{
public:
    Syntax::Configuration configuration;
    Syntax::Encoding::List encodings;

    SpellCheckingData()
        : QSharedData()
    {
    }

    SpellCheckingData( const Syntax::SpellCheckingData& other )
        : QSharedData( other ),
            QE_OTHER_INIT( configuration ),
            QE_OTHER_INIT( encodings )
    {
    }

    virtual ~SpellCheckingData() {
    }
};

QE_IMPL_SHARED_CLASS( SpellChecking, Syntax )

Syntax::SpellChecking::~SpellChecking()
{
}

QE_IMPL_MEMBER( Syntax::Configuration, configuration, SpellChecking, Syntax )
QE_IMPL_MEMBER( Syntax::Encoding::List, encodings, SpellChecking, Syntax )
