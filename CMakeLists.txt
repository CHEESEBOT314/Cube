cmake_minimum_required(VERSION 3.10)
project(Cube)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set(CMAKE_EXE_LINKER_FLAGS -static)
set(CMAKE_CXX_STANDARD 20)

set(SOURCES main.cxx
            cube.cxx
            slice.cxx)

include_directories(.)
add_executable(Cube ${SOURCES})