cmake_minimum_required (VERSION 2.6)
project (MakeSharp)
set (MakeSharp_MINOR 0)
set (MakeSharp_MAJOR 0)
#configure_file (
#    "${PROJECT_SOURCE_DIR}/Config.h.in"
#    "${PROJECT_SOURCE_DIR}/Config.h"
#)

#set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
#add_subdirectory("${SOURCE_DIR}/parser")
#add_subdirectory("${SOURCE_DIR}/script")
#add_subdirectory("${SOURCE_DIR}/generator")
#add_subdirectory("${SOURCE_DIR}/explorer")
#add_subdirectory("${SOURCE_DIR}/macros")
#add_subdirectory("${SOURCE_DIR}/utils")

add_executable(test_profile
    "src/parser/metadata.cpp"
    "test/profile.cpp")

