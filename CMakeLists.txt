cmake_minimum_required (VERSION 2.6)
project (MakeSharp)
set (MakeSharp_MINOR 0)
set (MakeSharp_MAJOR 0)
#configure_file (
#    "${PROJECT_SOURCE_DIR}/Config.h.in"
#    "${PROJECT_SOURCE_DIR}/Config.h"
#)
add_executable (MakeSharp src/main.cpp)
