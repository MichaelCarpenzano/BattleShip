find_path(PSPSDK_INCLUDE_DIR
    NAMES pspkernel.h
    HINTS
        $ENV{PSPSDK}/include
        $ENV{PSPDEV}/psp/sdk/include
)

find_path(PSPSDK_LIBRARY_DIR
    NAMES libpspdebug.a
    HINTS
        $ENV{PSPSDK}/lib
        $ENV{PSPDEV}/psp/sdk/lib
)

set(PSPSDK_INCLUDE_DIRS ${PSPSDK_INCLUDE_DIR})
set(PSPSDK_LIBRARY_DIRS ${PSPSDK_LIBRARY_DIR})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(PSPSDK
    REQUIRED_VARS PSPSDK_INCLUDE_DIR PSPSDK_LIBRARY_DIR
)

mark_as_advanced(PSPSDK_INCLUDE_DIR PSPSDK_LIBRARY_DIR)
