/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : Encoding.cpp
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#include "Encoding.h"

class Syntax::EncodingData : public QSharedData
{
public:
    QString char_;
    QString string;
    bool ignored;

    EncodingData()
        : QSharedData(),
            ignored( false )
    {
    }

    EncodingData( const Syntax::EncodingData& other )
        : QSharedData( other ),
            QE_OTHER_INIT( char_ ),
            QE_OTHER_INIT( string ),
            QE_OTHER_INIT( ignored )
    {
    }

    virtual ~EncodingData() {
    }
};

QE_IMPL_SHARED_CLASS( Encoding, Syntax )

Syntax::Encoding::~Encoding()
{
}

QE_IMPL_MEMBER( QString, char_, Encoding, Syntax )
QE_IMPL_MEMBER( QString, string, Encoding, Syntax )
QE_IMPL_MEMBER( bool, ignored, Encoding, Syntax )
