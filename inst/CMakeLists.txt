cmake_minimum_required(VERSION 3.16)
include(FetchContent)
include(ExternalProject)


set(CMAKE_CXX_COMPILER ${CXX})
set(CMAKE_C_COMPILER ${CC})

project(flashlighttext)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(Boost_USE_STATIC_LIBS ON)
SET(LIBRARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/../flashlighttext/)
SET(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${LIBRARY_DIR}/lib")
SET(COMMON_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${LIBRARY_DIR} -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH} -DCMAKE_POSITION_INDEPENDENT_CODE:bool=ON -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER})

ExternalProject_Add(flashlighttext-project
    GIT_REPOSITORY https://github.com/flashlight/text/
    GIT_TAG v0.0.3
    PREFIX "${CMAKE_CURRENT_BINARY_DIR}/flashlight"
    CMAKE_ARGS ${COMMON_CMAKE_ARGS} -DFL_TEXT_BUILD_TESTS=OFF
)

ExternalProject_Add(kenlm-project
    GIT_REPOSITORY https://github.com/athospd/kenlm/
    GIT_TAG master
    PREFIX "${CMAKE_CURRENT_BINARY_DIR}/kenlm"
    CMAKE_ARGS ${COMMON_CMAKE_ARGS}
)

  
add_dependencies(flashlighttext-project kenlm-project)
