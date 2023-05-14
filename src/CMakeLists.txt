cmake_minimum_required(VERSION 3.16)
project(flashlighttext)

include(FetchContent)
include(ExternalProject)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(LIBRARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/../flashlighttext/)
SET(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${LIBRARY_DIR}/lib")
SET(COMMON_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${LIBRARY_DIR} -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH} -DCMAKE_POSITION_INDEPENDENT_CODE:bool=ON)
message(STATUS "CMAKE_INSTALL_PREFIX: ${LIBRARY_DIR}")

ExternalProject_Add(kenlm-project
    GIT_REPOSITORY https://github.com/kpu/kenlm/
    GIT_TAG master
    PREFIX "${CMAKE_CURRENT_BINARY_DIR}/kenlm"
    CMAKE_ARGS ${COMMON_CMAKE_ARGS}
)

ExternalProject_Add(flashlighttext-project
    GIT_REPOSITORY https://github.com/flashlight/text/
    GIT_TAG v0.0.3
    PREFIX "${CMAKE_CURRENT_BINARY_DIR}/flashlight"
    CMAKE_ARGS ${COMMON_CMAKE_ARGS}
)

  
add_dependencies(flashlighttext-project kenlm-project)
