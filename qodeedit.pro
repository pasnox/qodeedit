###########################################################################################
##      Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
##
##  Author    : You Name <your@email.org>
##  Project   : qodeedit
##  FileName  : qodeedit.pro
##  Date      : 2012-05-27T13:18:50
##  License   : GPL
##  Comment   : Creating using Monkey Studio RAD
##  Home Page : https://github.com/pasnox/qodeedit
##
##  This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
##  WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
##
###########################################################################################

XUP.QT_VERSION = Qt System (4.8.1)
XUP.OTHERS_PLATFORM_TARGET_DEFAULT = bin/Linux/qodeedit_debug

ABSOLUTE_DATA_DIR = $$PWD/share

include( config.pri )
initializeProject( app, $${BUILD_TARGET}, $${BUILD_MODE}, $${BUILD_PATH}/$${TARGET_NAME}, $${BUILD_TARGET_PATH}, "", "0.1.0" )
autoGenerateFile( "main.h.in", "src/main.h" )

QT *= xml

INCLUDEPATH *= $$getFolders( . )
DEPENDPATH *= $${INCLUDEPATH}

FORMS *=  \
    src/example/UIMain.ui

HEADERS *=  \
    src/example/UIMain.h \
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
    src/syntax/SyntaxComboBox.h

SOURCES *= src/main.cpp \
    src/example/UIMain.cpp \
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
    src/syntax/SyntaxComboBox.cpp
