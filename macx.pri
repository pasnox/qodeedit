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