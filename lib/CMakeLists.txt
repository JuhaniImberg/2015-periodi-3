file(GLOB LIB_SOURCE_FILES src/*.c)

add_library(tila ${LIB_SOURCE_FILES})
target_include_directories(tila PUBLIC include/)
