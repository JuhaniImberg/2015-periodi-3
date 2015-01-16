enable_testing()
find_package(Check REQUIRED)

file(GLOB TEST_SOURCE_FILES src/*.c)
set(LIBS ${LIBS} tila ${CHECK_LIBRARY} m rt pthread)
set(INCLUDES ${INCLUDES} include ../lib/include ${CHECK_INCLUDE_DIR})

add_executable(tilatest ${TEST_SOURCE_FILES})
target_link_libraries(tilatest ${LIBS})
target_include_directories(tilatest PUBLIC ${INCLUDES})

add_test(tilatest ${CMAKE_CURRENT_BINARY_DIR}/tilatest)
