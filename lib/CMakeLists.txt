file(GLOB LIB_SOURCE_FILES src/*/*.c)

add_library(tila ${LIB_SOURCE_FILES})
include_directories(include
                    include/datastructures
                    include/util
                    include/parser
                    include/tokenizer
                    include/interpreter
)
