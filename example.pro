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
include( config.pri )
initializeProject( app, $${BUILD_TARGET}, $${BUILD_MODE}, $${BUILD_PATH}/$${TARGET_NAME}, $${BUILD_TARGET_PATH} )

INCLUDEPATH *= $$getFolders( example ) $$getFolders( src )
DEPENDPATH *= $${INCLUDEPATH}

LIBS *= -L$${BUILD_TARGET_PATH} -l$$targetForMode( QodeEdit )

FORMS *= \
    example/UIMain.ui

HEADERS *= \
    example/UIMain.h

SOURCES *= main.cpp \
    example/UIMain.cpp
