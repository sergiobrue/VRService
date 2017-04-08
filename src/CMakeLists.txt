cmake_minimum_required (VERSION 2.8.12)
project (VRService)

set (EXECNAME vrs)
set (EXECTEST test_vrs)

#Version
set(PIN_VERSION_MAJOR 1)
set(PIN_VERSION_MINOR 0)

# Custom CMAKE MODULES ----
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules/")
# -------------------------

if (CMAKE_BUILD_TYPE)
  string(TOUPPER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE)
  message("| BUILD TYPE ${CMAKE_BUILD_TYPE}")
endif(CMAKE_BUILD_TYPE)


# Release and debug --------------------------
if(NOT CMAKE_BUILD_TYPE STREQUAL "RELEASE")
  message("| Compiling in DEBUG MODE")
  set (CMAKE_CXX_FLAGS "-O0 -ggdb ${CMAKE_CXX_FLAGS}")
else(NOT CMAKE_BUILD_TYPE STREQUAL "RELEASE")
  message("| Compiling in RELEASE MODE")
  set(CMAKE_CXX_FLAGS "-O3  -ffast-math -fomit-frame-pointer -DNDEBUG ${CMAKE_CXX_FLAGS}")
endif(NOT CMAKE_BUILD_TYPE STREQUAL "RELEASE")
# ---------------------------------------------

set (CMAKE_CXX_FLAGS "-std=c++14 -Werror -Wall ${CMAKE_CXX_FLAGS}")

if (MINGW)
  list(APPEND CMAKE_PREFIX_PATH $ENV{MINGW})
  set(GCC_CXX_FLAGS "-D__USE_MINGW_ANSI_STDIO=1 ${CMAKE_CXX_FLAGS}")
endif (MINGW)

# Try to find static libraries first in WIN32
IF(WIN32)
    set(CMAKE_FIND_LIBRARY_SUFFIXES .a ${CMAKE_FIND_LIBRARY_SUFFIXES})
ENDIF(WIN32)

find_package(cppnetlib 0.12.0 REQUIRED)

add_executable(${EXECNAME} HTTPServer.cc ResourceFolder.cc ResourceFile.cc
  User.cc Group.cc main.cc)

add_executable(${EXECTEST} HTTPServer.cc ResourceFolder.cc ResourceFile.cc
  User.cc Group.cc test.cc)


include_directories( ${CPPNETLIB_INCLUDE_DIRS} )
target_link_libraries( ${EXECNAME} ${CPPNETLIB_LIBRARIES} stdc++ )
target_link_libraries( ${EXECTEST} ${CPPNETLIB_LIBRARIES} stdc++ )
