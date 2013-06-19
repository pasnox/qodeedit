###########################################################################################
##      Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
##
##  Author    : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
##  Project   : QodeEdit
##  FileName  : QodeEdit.pro
##  Date      : 2012-05-27T13:18:50
##  License   : LGPL3
##  Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
##  Home Page : https://github.com/pasnox/qodeedit
##
##  This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
##  WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
##
###########################################################################################
include( config.pri )
initializeProject( lib, $${BUILD_TARGET}, $${BUILD_MODE}, $${BUILD_PATH}/$${TARGET_NAME}, $${BUILD_TARGET_PATH}, $${BUILD_TYPE}, $${BUILD_VERSION} )
autoGenerateFile( "QodeEditConfig.h.in", "src/QodeEditConfig.h" )

QT *= xml
greaterThan( QT_MAJOR_VERSION, 4 ):QT *= widgets

INCLUDEPATH *= $${PWD}/src
DEPENDPATH *= $$getFolders( $${PWD} )

greaterThan( QT_MAJOR_VERSION, 4 ) {
} else:greaterThan( QT_MAJOR_VERSION, 3 ) {
    MIMETYPES_QT4_ROOT = $${PWD}/mimetypes-qt4

    exists( $${MIMETYPES_QT4_ROOT} ) {
        SOURCES_PATHS = $$getFolders( $${MIMETYPES_QT4_ROOT}/src )
        DEPENDPATH *= $${SOURCES_PATHS}
        INCLUDEPATH *= $${SOURCES_PATHS}

        include( $${MIMETYPES_QT4_ROOT}/src/mimetypes/mimetypes.pri )

        HEADERS *= $${MIMETYPES_QT4_ROOT}/src/mimetypes-qt4-helpers.h
        SOURCES *= $${MIMETYPES_QT4_ROOT}/src/mimetypes-qt4-helpers.cpp

        HEADERS *= $${MIMETYPES_QT4_ROOT}/src/io/qstandardpaths.h
        SOURCES *= $${MIMETYPES_QT4_ROOT}/src/io/qstandardpaths.cpp

        macx {
            SOURCES *= $${MIMETYPES_QT4_ROOT}/src/io/qstandardpaths_mac.cpp
            LIBS *= "-framework Carbon"
        } else:unix {
            SOURCES *= $${MIMETYPES_QT4_ROOT}/src/io/qstandardpaths_unix.cpp
        } else:win32 {
            SOURCES *= $${MIMETYPES_QT4_ROOT}/src/io/qstandardpaths_win.cpp
        }
    } else {
        error( Qt 4 build need dependency project mimetypes-qt4 uncompressed in $${MIMETYPES_QT4_ROOT} folder. You can get it here https://github.com/pasnox/mimetypes-qt4 )
    }
}

FORMS *=

HEADERS *=  \
    src/QodeEdit.h \
    src/Tools.h \
    src/editor/CodeEditor.h \
    src/editor/TextDocument.h \
    src/editor/PlainTextDocumentLayout.h \
    src/editor/TextBlockUserData.h \
    src/margin/MarginStacker.h \
    src/margin/AbstractMargin.h \
    src/margin/LineBookmarkMargin.h \
    src/margin/LineNumberMargin.h \
    src/margin/LineRevisionMargin.h \
    src/margin/LineSpacingMargin.h \
    src/syntax/Helpers.h \
    src/syntax/List.h \
    src/syntax/Document.h \
    src/syntax/ItemData.h \
    src/syntax/Rule.h \
    src/syntax/Comment.h \
    src/syntax/Keywords.h \
    src/syntax/Highlighting.h \
    src/syntax/Context.h \
    src/syntax/General.h \
    src/syntax/Folding.h \
    src/syntax/EmptyLine.h \
    src/syntax/Indentation.h \
    src/syntax/SpellChecking.h \
    src/syntax/Configuration.h \
    src/syntax/Encoding.h \
    src/syntax/Parser.h \
    src/syntax/DocumentBuilder.h \
    src/syntax/Model.h \
    src/syntax/Highlighter.h \
    src/syntax/ComboBox.h \
    src/syntax/ContextStack.h \
    src/syntax/ContextSwitcher.h \
    src/theme/Theme.h \
    src/Threading.h \
    src/Manager.h

SOURCES *=  \
    src/QodeEdit.cpp \
    src/Tools.cpp \
    src/editor/CodeEditor.cpp \
    src/editor/TextDocument.cpp \
    src/editor/PlainTextDocumentLayout.cpp \
    src/editor/TextBlockUserData.cpp \
    src/margin/MarginStacker.cpp \
    src/margin/AbstractMargin.cpp \
    src/margin/LineBookmarkMargin.cpp \
    src/margin/LineNumberMargin.cpp \
    src/margin/LineRevisionMargin.cpp \
    src/margin/LineSpacingMargin.cpp \
    src/syntax/Document.cpp \
    src/syntax/ItemData.cpp \
    src/syntax/Rule.cpp \
    src/syntax/Comment.cpp \
    src/syntax/Keywords.cpp \
    src/syntax/Highlighting.cpp \
    src/syntax/Context.cpp \
    src/syntax/General.cpp \
    src/syntax/Folding.cpp \
    src/syntax/EmptyLine.cpp \
    src/syntax/Indentation.cpp \
    src/syntax/SpellChecking.cpp \
    src/syntax/Configuration.cpp \
    src/syntax/Encoding.cpp \
    src/syntax/Parser.cpp \
    src/syntax/DocumentBuilder.cpp \
    src/syntax/Model.cpp \
    src/syntax/Highlighter.cpp \
    src/syntax/ComboBox.cpp \
    src/syntax/ContextStack.cpp \
    src/syntax/ContextSwitcher.cpp \
    src/theme/Theme.cpp \
    src/Threading.cpp \
    src/Manager.cpp
