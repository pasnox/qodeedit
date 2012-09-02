XUP.QT_VERSION = Qt System (4.8.1)
XUP.OTHERS_PLATFORM_TARGET_DEFAULT = bin/Linux/QodeEdit_debug

include( config.pri )

TEMPLATE = subdirs
CONFIG *= ordered

SUBDIRS = QodeEdit.pro \
    example.pro