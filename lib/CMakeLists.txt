# Copyright 2011,2012 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

########################################################################
# Setup library
########################################################################
include(GrPlatform) #define LIB_SUFFIX

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

list(APPEND vlc_sources
    channel_fixed_impl.cc
    channel_static_impl.cc
    channel_relative_impl.cc
    channel_scaleable_ff_impl.cc
)

set(vlc_sources "${vlc_sources}" PARENT_SCOPE)
if(NOT vlc_sources)
	MESSAGE(STATUS "No C++ sources... skipping lib/")
	return()
endif(NOT vlc_sources)

add_library(gnuradio-vlc SHARED ${vlc_sources})
target_link_libraries(gnuradio-vlc ${Boost_LIBRARIES} ${GNURADIO_ALL_LIBRARIES})
set_target_properties(gnuradio-vlc PROPERTIES DEFINE_SYMBOL "gnuradio_vlc_EXPORTS")

if(APPLE)
    set_target_properties(gnuradio-vlc PROPERTIES
        INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib"
    )
endif(APPLE)

########################################################################
# Install built library files
########################################################################
install(TARGETS gnuradio-vlc
    LIBRARY DESTINATION lib${LIB_SUFFIX} # .so/.dylib file
    ARCHIVE DESTINATION lib${LIB_SUFFIX} # .lib file
    RUNTIME DESTINATION bin              # .dll file
)

########################################################################
# Build and register unit test
########################################################################
include(GrTest)

include_directories(${CPPUNIT_INCLUDE_DIRS})

list(APPEND test_vlc_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/test_vlc.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_vlc.cc
)

add_executable(test-vlc ${test_vlc_sources})

target_link_libraries(
  test-vlc
  ${GNURADIO_RUNTIME_LIBRARIES}
  ${Boost_LIBRARIES}
  ${CPPUNIT_LIBRARIES}
  gnuradio-vlc
)

GR_ADD_TEST(test_vlc test-vlc)
