/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : ItemData.cpp
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#include "ItemData.h"

class Syntax::ItemDataData : public QSharedData
{
public:
    QString name;
    QString defStyleNum;
    bool spellChecking;
    QColor color;
    QColor selColor;
    bool bold;
    bool italic;
    bool strikeOut;
    bool underline;
    QColor backgroundColor;
    QColor selBackgroundColor;

    ItemDataData()
        : QSharedData(),
            spellChecking( false ),
            bold( false ),
            italic( false ),
            strikeOut( false ),
            underline( false )
    {
    }

    ItemDataData( const Syntax::ItemDataData& other )
        : QSharedData( other ),
            QE_OTHER_INIT( name ),
            QE_OTHER_INIT( defStyleNum ),
            QE_OTHER_INIT( spellChecking ),
            QE_OTHER_INIT( color ),
            QE_OTHER_INIT( selColor ),
            QE_OTHER_INIT( bold ),
            QE_OTHER_INIT( italic ),
            QE_OTHER_INIT( strikeOut ),
            QE_OTHER_INIT( underline ),
            QE_OTHER_INIT( backgroundColor ),
            QE_OTHER_INIT( selBackgroundColor )
    {
    }

    virtual ~ItemDataData() {
    }
};

QE_IMPL_SHARED_CLASS( ItemData, Syntax )

Syntax::ItemData::~ItemData()
{
}

QE_IMPL_MEMBER( QString, name, ItemData, Syntax )
QE_IMPL_MEMBER( QString, defStyleNum, ItemData, Syntax )
QE_IMPL_MEMBER( bool, spellChecking, ItemData, Syntax )
QE_IMPL_MEMBER( QColor, color, ItemData, Syntax )
QE_IMPL_MEMBER( QColor, selColor, ItemData, Syntax )
QE_IMPL_MEMBER( bool, bold, ItemData, Syntax )
QE_IMPL_MEMBER( bool, italic, ItemData, Syntax )
QE_IMPL_MEMBER( bool, strikeOut, ItemData, Syntax )
QE_IMPL_MEMBER( bool, underline, ItemData, Syntax )
QE_IMPL_MEMBER( QColor, backgroundColor, ItemData, Syntax )
QE_IMPL_MEMBER( QColor, selBackgroundColor, ItemData, Syntax )
