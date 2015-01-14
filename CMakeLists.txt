cmake_minimum_required(VERSION 2.8.4)
project(tila)
enable_testing()

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Wextra")

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DIS_DEBUG")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

add_subdirectory(lib)
add_subdirectory(cmd)
add_subdirectory(test)
