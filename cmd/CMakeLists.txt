file(GLOB CMD_SOURCE_FILES src/*.c)
set(LIBS ${LIBS} tila)
set(INCLUDES ${INCLUDES} include ../lib/include)

add_executable(tilacmd ${CMD_SOURCE_FILES})
target_link_libraries(tilacmd ${LIBS})
target_include_directories(tilacmd PUBLIC ${INCLUDES})
set_target_properties(tilacmd PROPERTIES OUTPUT_NAME tila)
