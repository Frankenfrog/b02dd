#!/bin/sh

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
CMAKE_BASE_DIR="$(dirname "$DIR")"

if [ -f CMakeLists.txt ]
then 
  echo "Directory contains CMakeLists.txt. You should use a clean out of source build. Exiting."
  exit 1
fi

if [ -f CMakeCache.txt ]
then 
  echo "Directory contains CMake files, will clean up."
  rm -rf bin/ CMake* cmake_install.cmake Makefile lib/ main/ src/
fi

echo "Building CMake build system."
if [ "$1" = "debug" ]
then
  $CMAKE_EXECUTABLE -DCMAKE_INSTALL_PREFIX=$B02DDSYS -DCMAKE_BUILD_TYPE=Dbg $CMAKE_BASE_DIR
elif [ "$1" = "profiling" ]
then
  $CMAKE_EXECUTABLE -DCMAKE_INSTALL_PREFIX=$B02DDSYS -DCMAKE_BUILD_TYPE=Profiling $CMAKE_BASE_DIR
else 
  $CMAKE_EXECUTABLE -DCMAKE_INSTALL_PREFIX=$B02DDSYS -DCMAKE_BUILD_TYPE=Release $CMAKE_BASE_DIR
fi

echo "creating symbolic links"
ln -s $CMAKE_BASE_DIR/config config
ln -s $CMAKE_BASE_DIR/python python 
