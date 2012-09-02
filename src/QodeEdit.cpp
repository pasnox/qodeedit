#include "QodeEdit.h"
#include "QodeEditConfig.h"

#include <QStringList>
#include <QDir>
#include <QDesktopServices>
#include <QMetaObject>
#include <QMetaEnum>
#include <QDebug>

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

struct QodeEditData {
    QodeEditData() {
        const QMetaObject& mo = QodeEdit::staticMetaObject;
        ruler = CaseInsensitiveEnumerator( mo.enumerator( mo.indexOfEnumerator( "Ruler" ) ) );
        margin = CaseInsensitiveEnumerator( mo.enumerator( mo.indexOfEnumerator( "Margin" ) ) );
        rule = CaseInsensitiveEnumerator( mo.enumerator( mo.indexOfEnumerator( "Rule" ) ) );
        style = CaseInsensitiveEnumerator( mo.enumerator( mo.indexOfEnumerator( "Style" ) ) );
    }
    
    QString userSharedDataFilePath;
    CaseInsensitiveEnumerator ruler;
    CaseInsensitiveEnumerator margin;
    CaseInsensitiveEnumerator rule;
    CaseInsensitiveEnumerator style;
};

static QodeEditData qodeEditData;

QString QodeEdit::rulerToString( QodeEdit::Ruler ruler )
{
    return qodeEditData.ruler.valueToKey( ruler );
}

QodeEdit::Ruler QodeEdit::stringToRuler( const QString& string )
{
    return QodeEdit::Ruler( qodeEditData.ruler.keyToValue( string ) );
}

QString QodeEdit::marginToString( QodeEdit::Margin margin )
{
    return qodeEditData.margin.valueToKey( margin );
}

QodeEdit::Margin QodeEdit::stringToMargin( const QString& string )
{
    return QodeEdit::Margin( qodeEditData.margin.keyToValue( string ) );
}

QString QodeEdit::ruleToString( QodeEdit::Rule rule )
{
    return qodeEditData.rule.valueToKey( rule );
}

QodeEdit::Rule QodeEdit::stringToRule( const QString& string )
{
    return QodeEdit::Rule( qodeEditData.rule.keyToValue( string ) );
}

QString QodeEdit::styleToString( QodeEdit::Style style )
{
    return qodeEditData.style.valueToKey( style );
}

QodeEdit::Style QodeEdit::stringToStyle( const QString& string )
{
    return QodeEdit::Style( qodeEditData.style.keyToValue( string ) );
}

const char* QodeEdit::version()
{
    return PACKAGE_VERSION;
}

QString QodeEdit::versionString()
{
    return PACKAGE_VERSION;
}

QString QodeEdit::sharedDataFilePath( const QString& extended )
{
    return QDir::cleanPath( QString( "%1/%2" )
        .arg( PACKAGE_ABSOLUTE_DATA_DIR )
        .arg( extended ) );
}

QString QodeEdit::userSharedDataFilePath( const QString& extended )
{
    return qodeEditData.userSharedDataFilePath.isEmpty()
        ? QDir::cleanPath( QString( "%1/%2/%3" )
            .arg( QDesktopServices::storageLocation( QDesktopServices::DataLocation ) )
            .arg( PACKAGE_NAME )
            .arg( extended ) )
        : qodeEditData.userSharedDataFilePath
    ;
}

void QodeEdit::setUserSharedDataFilePath( const QString& filePath )
{
    qodeEditData.userSharedDataFilePath = filePath;
}

QString QodeEdit::schemaDefinitionFilePath()
{
    return QodeEdit::sharedDataFilePath( "schemas" );
}

QString QodeEdit::syntaxDefinitionFilePath()
{
    return QodeEdit::sharedDataFilePath( "syntax" );
}

QString QodeEdit::userSchemaDefinitionFilePath()
{
    return QodeEdit::userSharedDataFilePath( "schemas" );
}

QString QodeEdit::userSyntaxDefinitionFilePath()
{
    return QodeEdit::userSharedDataFilePath( "syntax" );
}

QStringList QodeEdit::schemaDefinitionFilePaths()
{
    return QStringList()
        << QodeEdit::schemaDefinitionFilePath()
        << QodeEdit::userSchemaDefinitionFilePath()
    ;
}

QStringList QodeEdit::syntaxDefinitionFilePaths()
{
    return QStringList()
        << QodeEdit::syntaxDefinitionFilePath()
        << QodeEdit::userSyntaxDefinitionFilePath()
    ;
}

bool QodeEdit::stringEquals( const QString& left, const QString& right, Qt::CaseSensitivity sensitivity )
{
    return QString::compare( left, right, sensitivity ) == 0;
}

bool QodeEdit::stringLessThan( const QString& left, const QString& right, Qt::CaseSensitivity sensitivity )
{
    return QString::compare( left, right, sensitivity ) < 0;
}

bool QodeEdit::localeAwareStringEquals( const QString& left, const QString& right )
{
    return QString::localeAwareCompare( left, right ) == 0;
}

bool QodeEdit::localeAwareStringLessThan( const QString& left, const QString& right )
{
    return QString::localeAwareCompare( left, right ) < 0;
}

bool QodeEdit::versionStringLessThan( const QString& left, const QString& right )
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
