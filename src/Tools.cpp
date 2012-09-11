/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : Tools.cpp
** Date      : 2012-09-11T20:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#include "Tools.h"

#include <QStringList>
#include <QDir>
#include <QDesktopServices>
#include <QMetaObject>
#include <QMetaEnum>
#include <QDebug>

namespace QodeEdit {

namespace Tools {
    class CaseInsensitiveEnumerator {
    public:
        CaseInsensitiveEnumerator( const QMetaEnum& enumerator = QMetaEnum() ) {
            name = QString::fromAscii( enumerator.name() ).toLower();
            
            for ( int i = 0; i < enumerator.keyCount(); i++ ) {
                const int value( enumerator.value( i ) );
                QString key( enumerator.key( i ) );
                key.chop( name.size() );
                normal[ value ] = key;
                lower[ key.toLower() ] = value;
            }
        }
        
        QString valueToKey( int value ) const {
            return normal.value( value );
        }
        
        int keyToValue( const QString& key ) const {
            QString string = key.toLower();
            
            if ( string.endsWith( name ) ) {
                string.chop( name.size() );
            }
            
            return lower.value( string );
        }

    private:
        QString name;
        QHash<int, QString> normal;
        QHash<QString, int> lower;
    };
    
    const QMetaObject& mo() {
        return QodeEdit::Manager::staticMetaObject;
    }
    
    static CaseInsensitiveEnumerator ruler( mo().enumerator( mo().indexOfEnumerator( "Ruler" ) ) );
    static CaseInsensitiveEnumerator margin( mo().enumerator( mo().indexOfEnumerator( "Margin" ) ) );
    static CaseInsensitiveEnumerator rule( mo().enumerator( mo().indexOfEnumerator( "Rule" ) ) );
    static CaseInsensitiveEnumerator style( mo().enumerator( mo().indexOfEnumerator( "Style" ) ) );
}; // Tools

}; // QodeEdit

QString QodeEdit::Tools::rulerToString( QodeEdit::Ruler ruler )
{
    return QodeEdit::Tools::ruler.valueToKey( ruler );
}

QodeEdit::Ruler QodeEdit::Tools::stringToRuler( const QString& string )
{
    return QodeEdit::Ruler( QodeEdit::Tools::ruler.keyToValue( string ) );
}

QString QodeEdit::Tools::marginToString( QodeEdit::Margin margin )
{
    return QodeEdit::Tools::margin.valueToKey( margin );
}

QodeEdit::Margin QodeEdit::Tools::stringToMargin( const QString& string )
{
    return QodeEdit::Margin( QodeEdit::Tools::margin.keyToValue( string ) );
}

QString QodeEdit::Tools::ruleToString( QodeEdit::Rule rule )
{
    return QodeEdit::Tools::rule.valueToKey( rule );
}

QodeEdit::Rule QodeEdit::Tools::stringToRule( const QString& string )
{
    return QodeEdit::Rule( QodeEdit::Tools::rule.keyToValue( string ) );
}

QString QodeEdit::Tools::styleToString( QodeEdit::Style style )
{
    return QodeEdit::Tools::style.valueToKey( style );
}

QodeEdit::Style QodeEdit::Tools::stringToStyle( const QString& string )
{
    return QodeEdit::Style( QodeEdit::Tools::style.keyToValue( string ) );
}

bool QodeEdit::Tools::stringEquals( const QString& left, const QString& right, Qt::CaseSensitivity sensitivity )
{
    return QString::compare( left, right, sensitivity ) == 0;
}

bool QodeEdit::Tools::stringLessThan( const QString& left, const QString& right, Qt::CaseSensitivity sensitivity )
{
    return QString::compare( left, right, sensitivity ) < 0;
}

bool QodeEdit::Tools::localeAwareStringEquals( const QString& left, const QString& right )
{
    return QString::localeAwareCompare( left, right ) == 0;
}

bool QodeEdit::Tools::localeAwareStringLessThan( const QString& left, const QString& right )
{
    return QString::localeAwareCompare( left, right ) < 0;
}

bool QodeEdit::Tools::versionStringLessThan( const QString& left, const QString& right )
{
    if ( left == right ) {
        return false;
    }
    
    const QStringList leftParts = left.split( "." );
    const QStringList rightParts = right.split( "." );
    
    // major
    if ( leftParts.value( 0 ).toInt() != rightParts.value( 0 ).toInt() ) {
        return leftParts.value( 0 ).toInt() < rightParts.value( 0 ).toInt();
    }
    // minor
    else if ( leftParts.value( 1 ).toInt() != rightParts.value( 1 ).toInt() ) {
        return leftParts.value( 1 ).toInt() < rightParts.value( 1 ).toInt();
    }
    // patch
    else if ( leftParts.value( 2 ).toInt() != rightParts.value( 2 ).toInt() ) {
        return leftParts.value( 2 ).toInt() < rightParts.value( 2 ).toInt();
    }
    // build
    else if ( leftParts.value( 3 ).toInt() != rightParts.value( 3 ).toInt() ) {
        return leftParts.value( 3 ).toInt() < rightParts.value( 3 ).toInt();
    }
    // extra
    else if ( leftParts.value( 4 ).isEmpty() && !rightParts.value( 4 ).isEmpty() ) {
        return false;
    }
    // extra
    else if ( !leftParts.value( 4 ).isEmpty() && rightParts.value( 4 ).isEmpty() ) {
        return true;
    }
    
    // extra
    return leftParts.value( 4 ) < rightParts.value( 4 ); // not the best but afaik ;)
}
