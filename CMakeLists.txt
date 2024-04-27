cmake_minimum_required(VERSION 3.10)
project(converter)

set(CMAKE_CXX_STANDARD 17)

# Find libmp3lame headers
find_path(LAME_INCLUDE_DIR lame/lame.h)
if(NOT LAME_INCLUDE_DIR)
    message(FATAL_ERROR "LAME headers not found")
endif()

# Find libmp3lame library
find_library(LAME_LIBRARY NAMES mp3lame)
if(NOT LAME_LIBRARY)
    message(FATAL_ERROR "LAME library not found")
endif()

add_executable(converter main.cpp)

target_include_directories(converter PRIVATE ${LAME_INCLUDE_DIR})
target_link_libraries(converter PRIVATE ${LAME_LIBRARY})
