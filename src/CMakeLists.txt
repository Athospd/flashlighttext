cmake_minimum_required(VERSION 3.16)
include(FetchContent)
include(ExternalProject)

message("CXX -----------: ${CXX}")
set(CMAKE_CXX_COMPILER ${CXX})
set(CMAKE_C_COMPILER /usr/bin/gcc)

project(flashlighttext)

message("CMAKE_CXX_COMPILER -----------: ${CMAKE_CXX_COMPILER}")
message("C++ compiler path: ${CMAKE_CXX_COMPILER_INIT}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
SET(LIBRARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/../flashlighttext/)
SET(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${LIBRARY_DIR}/lib")
SET(COMMON_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${LIBRARY_DIR} -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH} -DCMAKE_POSITION_INDEPENDENT_CODE:bool=ON -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER})
message(STATUS "CMAKE_INSTALL_PREFIX: ${LIBRARY_DIR}")

ExternalProject_Add(flashlighttext-project
    GIT_REPOSITORY https://github.com/flashlight/text/
    GIT_TAG v0.0.3
    PREFIX "${CMAKE_CURRENT_BINARY_DIR}/flashlight"
    CMAKE_ARGS ${COMMON_CMAKE_ARGS} 
)

ExternalProject_Add(kenlm-project
    GIT_REPOSITORY https://github.com/kpu/kenlm/
    GIT_TAG master
    PREFIX "${CMAKE_CURRENT_BINARY_DIR}/kenlm"
    CMAKE_ARGS ${COMMON_CMAKE_ARGS}
)

  
add_dependencies(flashlighttext-project kenlm-project)
