# shared configuration file

include( functions.pri )

BUILD_TARGET = qodeedit
BUILD_RAMDISK = /media/ramdisk
exists( $${BUILD_RAMDISK} ):BUILD_PATH = $${BUILD_RAMDISK}/build
else:BUILD_PATH = build
BUILD_PATH = $${BUILD_PATH}/$${BUILD_TARGET}
BUILD_TARGET_PATH = bin/$${Q_TARGET}
BUILD_MODE = debug
BUILD_TYPE = shared

# Initialize a project
# $$1 = template (app or lib)
# $$2 = target name (in release name)
# $$3 = build mode (debug, release)
# $$4 = build path
# $$5 = build target path
# $$6 = build type
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

    CONFIG -= release debug debug_and_release warn_on warn_off ppc x86 x86_64
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