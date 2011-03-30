# Top level
cmake_minimum_required(VERSION 2.6)
project(cWavelet)

# Build environment
set(CMAKE_C_FLAGS "-std=c99 -Wall -Wextra -pendantic")
set(CMAKE_C_FLAGS_DEBUG "-O0 -ggdb")
set(CMAKE_C_FLAGS_RELEASE "-Os")

# Set paths
add_subdirectory(src)
add_subdirectory(tests)

