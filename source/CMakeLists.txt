cmake_minimum_required(VERSION 3.5)
project (snaze VERSION 1.0.0 LANGUAGES CXX )

# Currently CMake (since 2.8.5) supports generation of compilation databases
# for Unix Makefile builds (Ninja builds in the works) with the option
# CMAKE_EXPORT_COMPILE_COMMANDS.
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

#=== SETTING VARIABLES ===#
# Compiling flags
set( GCC_COMPILE_FLAGS "-Wall" )
#set( PREPROCESSING_FLAGS  "-D PRINT -D DEBUG -D CASE="WORST" -D ALGO="QUAD"')
set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS} ${PREPROCESSING_FLAGS}" )

#=== Main App ===

#Include dir
add_executable(snaze
    "0_main.cpp"
    "1.2_snakegame.cpp"
    "1.3_snkgm_msgs.cpp"
    "2.1_level.cpp")

target_compile_features( snaze PUBLIC cxx_std_17 )