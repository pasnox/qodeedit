###########################################################################################
##      Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
##
##  Author    : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
##  Project   : QodeEdit
##  FileName  : example.pro
##  Date      : 2012-05-27T13:18:50
##  License   : LGPL3
##  Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
##  Home Page : https://github.com/pasnox/qodeedit
##
##  This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
##  WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
##
###########################################################################################
win32|macx {
    OXYGEN_THEME_PATH = $$PWD/../oxygen-icons-png.git

    exists( $${OXYGEN_THEME_PATH} ) {
        QICON_THEMES_PATH = $${OXYGEN_THEME_PATH}
    }
}

include( config.pri )
initializeProject( app, $${BUILD_TARGET}, $${BUILD_MODE}, $${BUILD_PATH}/$${TARGET_NAME}, $${BUILD_TARGET_PATH} )
autoGenerateFile( "QodeEditExampleConfig.h.in", "example/QodeEditExampleConfig.h" )

greaterThan( QT_MAJOR_VERSION, 4 ):QT *= widgets

INCLUDEPATH *= $$getFolders( example ) $$getFolders( src )
DEPENDPATH *= $${INCLUDEPATH}

LIBS *= -L$${BUILD_TARGET_PATH} -l$$targetForMode( QodeEdit )

FORMS *= \
    example/UIMain.ui

HEADERS *= \
    example/UIMain.h

SOURCES *= example/main.cpp \
    example/UIMain.cpp
