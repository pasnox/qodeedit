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
#include "Manager.h"
#include "syntax/Document.h"
#include "syntax/DocumentBuilder.h"

#include <QStringList>
#include <QDir>
#include <QDesktopServices>
#include <QMetaObject>
#include <QMetaEnum>
#include <QTime>
#include <QIcon>
#include <QApplication>
#include <QTextCodec>
#include <QDebug>

namespace QodeEdit {

namespace Tools {
    class CaseInsensitiveEnumerator {
    public:
        CaseInsensitiveEnumerator( const QMetaEnum& enumerator = QMetaEnum() ) {
            name = QString::fromUtf8( enumerator.name() ).toLower();

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
        return *QodeEdit::metaObject();
    }

    static CaseInsensitiveEnumerator ruler( mo().enumerator( mo().indexOfEnumerator( "Ruler" ) ) );
    static CaseInsensitiveEnumerator margin( mo().enumerator( mo().indexOfEnumerator( "Margin" ) ) );
    static CaseInsensitiveEnumerator rule( mo().enumerator( mo().indexOfEnumerator( "Rule" ) ) );
    static CaseInsensitiveEnumerator defaultStyle( mo().enumerator( mo().indexOfEnumerator( "DefaultStyle" ) ) );
    static QHash<QString, QSet<QChar> > sets;
} // Tools

} // QodeEdit

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

QString QodeEdit::Tools::defaultStyleToString( QodeEdit::DefaultStyle style )
{
    return QodeEdit::Tools::defaultStyle.valueToKey( style );
}

QodeEdit::DefaultStyle QodeEdit::Tools::stringToDefaultStyle( const QString& string )
{
    return QodeEdit::DefaultStyle( QodeEdit::Tools::defaultStyle.keyToValue( string ) );
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

QTextCodec* QodeEdit::Tools::textCodec( const QByteArray& name, const QByteArray& data )
{
    QTextCodec* codec = QTextCodec::codecForName( name );

    if ( !codec ) {
        codec = QTextCodec::codecForUtfText( data );
    }

    if ( !codec ) {
        codec = QTextCodec::codecForLocale();
    }

    return codec;
}

const QSet<QChar>& QodeEdit::Tools::stringToSet( const QString& string )
{
    QSet<QChar>& set = QodeEdit::Tools::sets[ string ];

    if ( set.count() != string.count() ) {
        foreach ( const QChar& c, string ) {
            set << c;
        }
    }

    return set;
}

QStringList QodeEdit::Tools::listFilesInPath( const QString& path, const QStringList& filters, bool recursive, bool sort )
{
    QDir dir( path );
    QStringList files;

    foreach ( const QFileInfo& file, dir.entryInfoList( filters, QDir::Files ) ) {
        files << QDir::cleanPath( file.absoluteFilePath() );
    }

    if ( recursive ) {
        foreach ( const QFileInfo& file, dir.entryInfoList( QDir::AllDirs | QDir::NoDotAndDotDot ) ) {
            files << QodeEdit::Tools::listFilesInPath( file.absoluteFilePath(), filters, true );
        }
    }

    if ( sort ) {
        qSort( files.begin(), files.end(), QodeEdit::Tools::localeAwareStringLessThan );
    }

    return files;
}

QStringList QodeEdit::Tools::listFilesInPaths( const QStringList& paths, const QStringList& filters, bool recursive, bool sort )
{
    QStringList files;

    foreach ( const QString& path, paths ) {
        files << QodeEdit::Tools::listFilesInPath( path, filters, recursive, false );
    }

    if ( sort ) {
        qSort( files.begin(), files.end(), QodeEdit::Tools::localeAwareStringLessThan );
    }

    return files;
}

QHash<QString, Syntax::Document> QodeEdit::Tools::parseSyntaxesFiles( const QStringList& paths )
{
#if !defined( QT_NO_DEBUG )
    QTime time;
    time.start();
#endif

    const QStringList files = QodeEdit::Tools::listFilesInPaths( paths, QStringList( "*.xml" ), false );
    QString error;

#if !defined( QT_NO_DEBUG )
    qWarning( "%s: Found files in %f seconds", Q_FUNC_INFO , time.elapsed() /1000.0 );
#endif

    QHash<QString, Syntax::Document> documents = Syntax::Document::open( files, &error );

#if !defined( QT_NO_DEBUG )
    qWarning( "%s: Parsed files in %f seconds", Q_FUNC_INFO , time.elapsed() /1000.0 );
#endif

    /*if ( error.isEmpty() ) {
        Syntax::DocumentBuilder builder;
        builder.buildDocuments( documents );

#if !defined( QT_NO_DEBUG )
        qWarning( "%s: Build files in %f seconds", Q_FUNC_INFO , time.elapsed() /1000.0 );
#endif
    }
    else {
#if !defined( QT_NO_DEBUG )
        qWarning( "%s: %s", Q_FUNC_INFO, qPrintable( error ) );
        qWarning( "%s: Fails in %f seconds", Q_FUNC_INFO , time.elapsed() /1000.0 );
#endif
    }*/

    return documents;
}

QHash<QString, QString> QodeEdit::Tools::bestMatchingMimeTypesIcons( const QHash<QString, QStringList>& mimeTypes, const QString& defaultMimeType, bool processEvents )
{
    const QString defaultMimeStringIconName = QString( defaultMimeType ).replace( "/", "-" );
    QHash<QString, QString> hash;
    QString iconName;

    foreach ( const QString& key, mimeTypes.keys() ) {
        iconName.clear();

        foreach ( const QString& mimeType, mimeTypes[ key ] ) {
            iconName = QString( mimeType ).replace( "/", "-" );

            if ( QIcon::hasThemeIcon( iconName ) ) {
                break;
            }
            else {
                iconName.clear();
            }
        }

        if ( iconName.isEmpty() ) {
            iconName = defaultMimeStringIconName;
        }

        hash[ key ] = iconName;

        if ( processEvents ) {
            QApplication::processEvents();
        }
    }

    return hash;
}

QHash<QString, QPair<QString, QString> > QodeEdit::Tools::getFilesContentWithTextCodec( const QStringList& filePaths, const QByteArray& textCodec, bool processEvents )
{
    const QTextCodec* codec = QodeEdit::Tools::textCodec( textCodec );
    QHash<QString, QPair<QString, QString> > contents;

    foreach ( const QString& filePath, filePaths ) {
        QFile file( filePath );

        if ( file.open( QIODevice::ReadOnly ) ) {
            contents[ filePath ] = qMakePair( codec->toUnicode( file.readAll() ), QString() );
        }
        else {
            contents[ filePath ] = qMakePair( QString(), file.errorString() );
        }

        if ( processEvents ) {
            QApplication::processEvents();
        }
    }

    return contents;
}
