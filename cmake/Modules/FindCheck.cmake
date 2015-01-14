set(CHECK_FOUND FALSE)

find_path(CHECK_INCLUDE_DIR check.h
  /usr/local/include
  /usr/include
)

find_library(CHECK_LIBRARY check
  /usr/local/lib
  /usr/lib
)

if(CHECK_INCLUDE_DIR)
  if(CHECK_LIBRARY)
    set(CHECK_FOUND TRUE)
  endif(CHECK_LIBRARY)
endif(CHECK_INCLUDE_DIR)

if(CHECK_FOUND)
  message(STATUS "Found check: ${CHECK_LIBRARY}")
else(CHECK_FOUND)
  message(FATAL_ERROR "Could not find check.")
endif(CHECK_FOUND)
