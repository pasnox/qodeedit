###########################################################################################
##      Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
##
##  Author    : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
##  Project   : QodeEdit
##  FileName  : config.pri
##  Date      : 2012-05-27T13:18:50
##  License   : LGPL3
##  Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
##  Home Page : https://github.com/pasnox/qodeedit
##
##  This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
##  WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
##
###########################################################################################
# shared configuration file

# include qmake-extensions
include( qmake-extensions.pri )

BUILD_TARGET = QodeEdit
BUILD_RAMDISK = /media/ramdisk
exists( $${BUILD_RAMDISK} ):BUILD_PATH = $${BUILD_RAMDISK}/build
else:BUILD_PATH = build
BUILD_PATH = $${BUILD_PATH}/$${BUILD_TARGET}
BUILD_TARGET_PATH = bin/$${Q_TARGET}
BUILD_MODE = release
BUILD_TYPE = shared
BUILD_VERSION = 0.1.0
ABSOLUTE_DATA_DIR = $$PWD/share

# Initialize a project
# $$1 = template (app or lib)
# $$2 = target name (in release name)
# $$3 = build mode (debug, release)
# $$4 = build path
# $$5 = build target path
# $$6 = build type
# $$7 = target version
defineTest( initializeProject ) {
    # template
    q_template = $${1}
    isEmpty( q_template ):error( Fatal error: no template given )

    # target
    q_target = $${2}
    isEmpty( q_target ):error( Fatal error: no target name given )

    # mode
    q_mode = $${3}
    isEmpty( q_mode ):q_mode = $${BUILD_MODE}

    # type
    q_type = $${6}
    isEmpty( q_type ):q_type = $${BUILD_TYPE}

    # path
    q_path = $${4}
    isEmpty( q_path ) {
        q_path = $${BUILD_PATH}/$${BUILD_TARGET}
    }

    # target path
    q_target_path = $${5}
    isEmpty( q_target_path ) {
        q_target_path = $${BUILD_TARGET_PATH}
    }

    # version
    q_version = $${7}

    CONFIG -= release debug debug_and_release warn_on warn_off ppc ppc64 x86 x86_64
    CONFIG *= warn_on thread x11 windows qt $${q_mode} $${q_type}
    isEqual( q_mode, debug ):CONFIG *= console
    VERSION = $${q_version}

    QMAKE_RPATHDIR *= $${BUILD_TARGET_PATH}

    export( CONFIG )
    export( QMAKE_RPATHDIR )
    export( VERSION )

    setTemplate( $${q_template} )
    setTarget( $${q_target}, $${q_mode} )
    setTargetDirectory( $${q_target_path} )
    setTemporaryDirectories( $${q_path} )
}

include( macx.pri )
