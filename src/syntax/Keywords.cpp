/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : Keywords.cpp
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#include "Keywords.h"

class Syntax::KeywordsData : public QSharedData
{
public:
    bool caseSensitive;
    QString weakDeliminator;
    QString additionalDeliminator;
    QString wordWrapDeliminator;

    KeywordsData()
        : QSharedData(),
            caseSensitive( false )
    {
    }

    KeywordsData( const Syntax::KeywordsData& other )
        : QSharedData( other ),
            QE_OTHER_INIT( caseSensitive ),
            QE_OTHER_INIT( weakDeliminator ),
            QE_OTHER_INIT( additionalDeliminator ),
            QE_OTHER_INIT( wordWrapDeliminator )
    {
    }

    virtual ~KeywordsData() {
    }
};

QE_IMPL_SHARED_CLASS( Keywords, Syntax )

Syntax::Keywords::~Keywords()
{
}

QE_IMPL_MEMBER( bool, caseSensitive, Keywords, Syntax )
QE_IMPL_MEMBER( QString, weakDeliminator, Keywords, Syntax )
QE_IMPL_MEMBER( QString, additionalDeliminator, Keywords, Syntax )
QE_IMPL_MEMBER( QString, wordWrapDeliminator, Keywords, Syntax )
