Q_HOST_OS = $${QMAKE_HOST.os}
Q_LOWER_HOST_OS = $$lower( $${Q_HOST_OS} )

win32 {
	!isEqual(  Q_LOWER_HOST_OS, "windows" ) {
		CONFIG *= cb_win32
	}
}

macx {
	!isEqual(  Q_LOWER_HOST_OS, "darwin" ) {
		CONFIG *= cb_mac
	}
}

Q_TARGET = $${Q_HOST_OS}
Q_ARCH = $${QT_ARCH}

cb_win32 {
  Q_TARGET = Windows
}

cb_mac {
  Q_TARGET = Darwin
}

Q_TARGET_ARCH = "$${Q_TARGET}-$${Q_ARCH}"

Q_NULL =
Q_BACK_SLASH = "\\"
Q_SLASH = "/"
Q_QUOTE = "\""
Q_DOLLAR = "\\$"
Q_OPENING_BRACE = "\\{"
Q_CLOSING_BRACE = "\\}"

# lupdate/lrelease too buggy ( not full qmake interpreter ), so avoid functions def in this case
isEmpty( translations_pass ) {
    # return the list of directories recursively from a given path ($$1)
    # Forbidden filters can be given ($$2)
    defineReplace( getFolders ) {
        q_paths = $$1
        q_filters   = $$2 .svn
        q_folders   =

        for( q_path, q_paths ) {
            command = "ls -RQ1 \"$$q_path\" | grep \":\" | sed \"s/://g\" | sed \"s/'/\\\\\\'/g\""
            macx|win32:command   = ls -R1 \"$$q_path\" | grep \":\" | sed \"s/://g\" | sed \"s/\'/\\\\\\\'/g\" | sed \"s/\\(.*\\)/\\\"\\1\\\"/g\"
            win32:!cb_win32:command  = "for /D /R \"$$q_path\" %i in (*) do @echo \"%i\""

            _q_folders  = $$system( $$command )
            _q_folders *= $$1
            
            _q_folders = $$replace( _q_folders, $$Q_BACK_SLASH, $$Q_SLASH )

            # loop paths
            for( q_folder, _q_folders ) {
                # check filters
                filtered = false

                for( q_filter, q_filters ) {
                    result = $$find( q_folder, $$q_filter )
                    !isEmpty( result ):filtered = true
                }

                isEqual( filtered, false ):exists( $$q_folder ) {
                    q_folders   *= $$q_folder
                }
            }
        }
        
        #message( Getting folders for $$q_paths: $$q_folders )

        return( $$q_folders )
    }

    # return relative paths for the given paths ($$1)
    # according to root path ($$2)
    # new root path can be given ($$3)
    # Forbidden filters can be given ($$4)
    defineReplace( getRelativeFolders ) {
        q_paths = $$1
        q_root_path = $$2
        q_new_root_path = $$3
        q_filters   = $$4
        q_folders = $$getFolders( $$q_paths, $$q_filters )
        q_folders = $$replace( q_folders, $$q_root_path, $$q_new_root_path )
        
        #message( Getting relative folders for $$q_paths: $$q_folders )
        
        return( $$q_folders )
    }
    
    # return the project build mode
    defineReplace( buildMode ) {
        CONFIG( debug, debug|release ) {
            return( debug )
        } else {
            return( release )
        }
    }

    # return the target name ($$1) according to build mode($$2)
    defineReplace( targetForMode ) {
        q_target    = $$1
        q_mode  = $$2
        isEmpty( q_mode ):q_mode    = $$buildMode()
        
        isEqual( q_mode, release ) {
            q_target    = $$quote( $$q_target )
        } else {
            unix:q_target   = $$quote( $$join( q_target, , , _debug ) )
            else:q_target   = $$quote( $$join( q_target, , , d ) )
        }
        
        return( $$q_target )
    }

    # this function set the template name ($$1)
    defineTest( setTemplate ) {
        TEMPLATE  = $$1
        
        export( TEMPLATE )
    }

    # this function set the target name ($$1) according to the build mode ($$2)
    defineTest( setTarget ) {
        TARGET  = $$targetForMode( $$1, $$2 )
        
        export( TARGET )
    }

    defineTest( setTemporaryDirectories ) {
        q_build_path    = $$1
        q_mode  = $$buildMode()

        OBJECTS_DIR = $${q_build_path}/$${Q_TARGET_ARCH}/$${q_mode}/obj
        UI_DIR  = $${q_build_path}/$${Q_TARGET_ARCH}/$${q_mode}/ui
        MOC_DIR = $${q_build_path}/$${Q_TARGET_ARCH}/$${q_mode}/moc
        RCC_DIR = $${q_build_path}/$${Q_TARGET_ARCH}/$${q_mode}/rcc

        export( OBJECTS_DIR )
        export( UI_DIR )
        export( MOC_DIR )
        export( RCC_DIR )
    }
    
    defineTest( setTargetDirectory ) {
        DESTDIR = $$1
        
        win32:CONFIG( shared ) {
            DLLDESTDIR = $$1
        }
        
        export( DESTDIR )
        win32:export( DLLDESTDIR )
    }
} else {
    defineReplace( getFolders ) {
    }
    
    defineReplace( getRelativeFolders ) {
    }
    
    defineReplace( buildMode ) {
    }
    
    defineReplace( targetForMode ) {
    }
    
    defineTest( setTemplate ) {
    }
    
    defineTest( setTarget ) {
    }
    
    defineTest( setTemporaryDirectories ) {
    }
    
    defineTest( setTargetDirectory ) {
    }
}