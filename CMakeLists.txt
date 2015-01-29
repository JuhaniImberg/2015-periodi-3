cmake_minimum_required(VERSION 2.8.4)
project(tila)
enable_testing()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Wextra")

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DIS_DEBUG -g -O0 --coverage")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

add_custom_target(docs
                  COMMAND headerdoc2html -Ejo docs "${CMAKE_SOURCE_DIR}/lib/include"
                  COMMAND gatherheaderdoc docs index.html
                  COMMENT "Generates HeaderDoc documentation")

add_subdirectory(lib)
add_subdirectory(cmd)
add_subdirectory(test)
