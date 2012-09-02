###########################################################################################
##      Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
##
##  Author    : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
##  Project   : QodeEdit
##  FileName  : macx.pri
##  Date      : 2012-05-27T13:18:50
##  License   : LGPL3
##  Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
##  Home Page : https://github.com/pasnox/qodeedit
##
##  This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
##  WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
##
###########################################################################################

# Mac universal build from 10.3 & up

macx {
    SDK_PATH = $$(MAC_SDKS_PATH)
    isEmpty( SDK_PATH ):SDK_PATH = /Developer/SDKs
    CONFIG *= app_bundle
    
    universal {
        QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.3
        QMAKE_MAC_SDK = $${SDK_PATH}/MacOSX10.6.sdk
        CONFIG -= x86_64
        CONFIG *= x86
        CONFIG *= ppc
    }
    
    # this link is required for building the ppc port to avoid the undefined __Unwind_Resume symbol
    CONFIG( ppc ):LIBS *= -lgcc_eh
}
