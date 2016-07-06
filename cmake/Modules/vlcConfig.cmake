INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_VLC vlc)

FIND_PATH(
    VLC_INCLUDE_DIRS
    NAMES vlc/api.h
    HINTS $ENV{VLC_DIR}/include
        ${PC_VLC_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    VLC_LIBRARIES
    NAMES gnuradio-vlc
    HINTS $ENV{VLC_DIR}/lib
        ${PC_VLC_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(VLC DEFAULT_MSG VLC_LIBRARIES VLC_INCLUDE_DIRS)
MARK_AS_ADVANCED(VLC_LIBRARIES VLC_INCLUDE_DIRS)

