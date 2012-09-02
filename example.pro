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