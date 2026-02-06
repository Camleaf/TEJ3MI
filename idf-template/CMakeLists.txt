cmake_minimum_required(VERSION 4.2)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# setup IDF
include($ENV{IDF_PATH}/tools/cmake/project.cmake)

idf_build_set_property(CXX_STANDARD 23)

# do project and add compile_commands
project(idf_setup)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# use expressif's script to fix the compile_commands for clangd

if(EXISTS "${CMAKE_SOURCE_DIR}/fix_compile_commands.py")
    add_custom_target(
        fix_clangd ALL
        COMMAND ${CMAKE_COMMAND} -E echo "Running fix_compile_commands.py..."
        COMMAND ${CMAKE_COMMAND} -E env python3 ${CMAKE_SOURCE_DIR}/fix_compile_commands.py
        COMMENT "Cleaning compile_commands.json for clangd"
        VERBATIM
    )
endif()
