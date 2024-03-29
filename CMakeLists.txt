#
# If the user specifies -DCMAKE_BUILD_TYPE on the command line, take their
# definition
# and dump it in the cache along with proper documentation, otherwise set
# CMAKE_BUILD_TYPE
# to Debug prior to calling PROJECT()
#

IF(DEFINED CMAKE_BUILD_TYPE)
   SET(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Choose the type of
build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release
RelWithDebInfo MinSizeRel.")
ELSE()
   SET(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build, options
are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo
MinSizeRel.")
ENDIF()

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb -std=c++0x -std=c++14" CACHE STRING "Debug options." FORCE)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -std=c++0x -std=c++14" CACHE STRING "Debug options." FORCE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "$ENV{DOOFITSYS}/cmake/Modules/")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "$ENV{DOOCORESYS}/cmake/Modules/")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "$ENV{DOOSELECTIONSYS}/cmake/Modules/")

set(BASEPATH "${CMAKE_SOURCE_DIR}/src")
include_directories(${BASEPATH})

set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")

# Project Definition
project(B02DD)
cmake_minimum_required(VERSION 2.6)

if(${APPLE})
  MESSAGE( STATUS "Building for Mac OS X, switching on C++11 flags for Mac OS X/clang" )
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
endif(${APPLE})
IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  MESSAGE( STATUS "Building for Linux, switching off C++11 flags for Linux/gcc" )
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -std=c++1y")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

FIND_PACKAGE(Boost 1.48 COMPONENTS program_options filesystem thread system random REQUIRED)

find_package(ROOT REQUIRED)
find_package(DooCore REQUIRED)
find_package(DooSelection REQUIRED)
find_package(DooFit REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

include_directories(${DooCore_INCLUDE_DIR})
link_directories(${DooCore_LIBRARY_DIR})

include_directories(${DooSelection_INCLUDE_DIR})
link_directories(${DooSelection_LIBRARY_DIR})

include_directories(${DooFit_INCLUDE_DIR})
link_directories(${DooFit_LIBRARY_DIR})

include_directories(${ROOT_INCLUDE_DIR})

# CPToyMC
SET(CPToyMC_BASE $ENV{CPTOYMCSYS})
SET(CPToyMC_INCLUDES "${CPToyMC_BASE}/include")
SET(CPToyMC_INCLUDE_DIR "${CPToyMC_BASE}/include")
SET(CPToyMC_LIBRARY_DIR "${CPToyMC_BASE}/lib")
SET(CPToyMC_LIBRARIES "-lCPToyMC")

include_directories(${CPToyMC_INCLUDE_DIR})
link_directories(${CPToyMC_LIBRARY_DIR})

set(ALL_LIBRARIES ${DooSelection_LIBRARIES} ${DooFit_LIBRARIES} ${DooCore_LIBRARIES} ${ROOT_LIBRARIES} ${ROOFIT_LIBRARIES} ${Boost_LIBRARIES} ${ADDITIONAL_LIBRARIES} "-lTreePlayer")

add_subdirectory(main)
add_subdirectory(src)
