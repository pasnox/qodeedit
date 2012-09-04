###########################################################################################
##      Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
##
##  Author    : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
##  Project   : QodeEdit
##  FileName  : build-all.pro
##  Date      : 2012-05-27T13:18:50
##  License   : LGPL3
##  Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
##  Home Page : https://github.com/pasnox/qodeedit
##
##  This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
##  WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
##
###########################################################################################
XUP.QT_VERSION = Qt System (4.8.1)
XUP.OTHERS_PLATFORM_TARGET_DEFAULT = bin/Linux/QodeEdit_debug
XUP.MAC_PLATFORM_TARGET_DEFAULT = bin/Darwin/QodeEdit_debug.app

include( config.pri )

TEMPLATE = subdirs
CONFIG *= ordered

SUBDIRS = QodeEdit.pro \
    example.pro