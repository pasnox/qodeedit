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

INCLUDEPATH *= $$getFolders( . )
DEPENDPATH *= $${INCLUDEPATH}

greaterThan( QT_MAJOR_VERSION, 4 ) {
} else:greaterThan( QT_MAJOR_VERSION, 3 ) {
    MIMETYPES_QT4_ROOT = ./mimetypes-qt4

    exists( $${MIMETYPES_QT4_ROOT} ) {
        SOURCES_PATHS = $$getFolders( $${MIMETYPES_QT4_ROOT} )
        DEPENDPATH *= $${SOURCES_PATHS}
        INCLUDEPATH *= $${SOURCES_PATHS}

        include( $${MIMETYPES_QT4_ROOT}/mimetypes/mimetypes.pri )

        HEADERS *= $${MIMETYPES_QT4_ROOT}/io/qstandardpaths.h
        SOURCES *= $${MIMETYPES_QT4_ROOT}/io/qstandardpaths.cpp

        macx {
            SOURCES *= $${MIMETYPES_QT4_ROOT}/io/*_mac.c*
            LIBS *= "-framework Carbon"
        } else:unix {
            SOURCES *= $${MIMETYPES_QT4_ROOT}/io/*_unix.c*
        } else:win32 {
            SOURCES *= $${MIMETYPES_QT4_ROOT}/io/*_win.c*
        }
    } else {
        error( Qt 4 build need dependency project mimetypes-qt4 uncompressed in $${MIMETYPES_QT4_ROOT} folder. You can get it here https://github.com/pasnox/mimetypes-qt4 )
    }
}

FORMS *=

HEADERS *= \
    src/QodeEdit.h \
    src/editor/CodeEditor.h \
    src/document/TextDocument.h \
    src/document/PlainTextDocumentLayout.h \
    src/document/TextBlockUserData.h \
    src/margins/MarginStacker.h \
    src/margins/AbstractMargin.h \
    src/margins/LineBookmarkMargin.h \
    src/margins/LineNumberMargin.h \
    src/margins/LineRevisionMargin.h \
    src/margins/LineSpacingMargin.h \
    src/syntax/SyntaxHelpers.h \
    src/syntax/SyntaxItemData.h \
    src/syntax/SyntaxRule.h \
    src/syntax/SyntaxComment.h \
    src/syntax/SyntaxKeywords.h \
    src/syntax/SyntaxHighlighting.h \
    src/syntax/SyntaxContext.h \
    src/syntax/SyntaxGeneral.h \
    src/syntax/SyntaxDocument.h \
    src/syntax/SyntaxParser.h \
    src/syntax/SyntaxList.h \
    src/syntax/SyntaxFolding.h \
    src/syntax/SyntaxEmptyLine.h \
    src/syntax/SyntaxIndentation.h \
    src/syntax/SyntaxSpellChecking.h \
    src/syntax/SyntaxConfiguration.h \
    src/syntax/SyntaxEncoding.h \
    src/syntax/SyntaxFactory.h \
    src/syntax/SyntaxModel.h \
    src/syntax/SyntaxHighlighter.h \
    src/syntax/SyntaxComboBox.h \
    src/syntax/SyntaxDocumentBuilder.h \
    src/syntax/SyntaxTheme.h

SOURCES *= \
    src/QodeEdit.cpp \
    src/editor/CodeEditor.cpp \
    src/document/TextDocument.cpp \
    src/document/PlainTextDocumentLayout.cpp \
    src/document/TextBlockUserData.cpp \
    src/margins/MarginStacker.cpp \
    src/margins/AbstractMargin.cpp \
    src/margins/LineBookmarkMargin.cpp \
    src/margins/LineNumberMargin.cpp \
    src/margins/LineRevisionMargin.cpp \
    src/margins/LineSpacingMargin.cpp \
    src/syntax/SyntaxRule.cpp \
    src/syntax/SyntaxContext.cpp \
    src/syntax/SyntaxComment.cpp \
    src/syntax/SyntaxDocument.cpp \
    src/syntax/SyntaxGeneral.cpp \
    src/syntax/SyntaxKeywords.cpp \
    src/syntax/SyntaxHighlighting.cpp \
    src/syntax/SyntaxItemData.cpp \
    src/syntax/SyntaxParser.cpp \
    src/syntax/SyntaxFolding.cpp \
    src/syntax/SyntaxEmptyLine.cpp \
    src/syntax/SyntaxIndentation.cpp \
    src/syntax/SyntaxSpellChecking.cpp \
    src/syntax/SyntaxConfiguration.cpp \
    src/syntax/SyntaxEncoding.cpp \
    src/syntax/SyntaxFactory.cpp \
    src/syntax/SyntaxModel.cpp \
    src/syntax/SyntaxHighlighter.cpp \
    src/syntax/SyntaxComboBox.cpp \
    src/syntax/SyntaxDocumentBuilder.cpp \
    src/syntax/SyntaxTheme.cpp
