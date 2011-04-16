# Top level
cmake_minimum_required(VERSION 2.6)
project(cWavelet)

# Build environment
set(CMAKE_C_FLAGS "-std=c99 -Wall -Wextra -pendantic")
set(CMAKE_C_FLAGS_DEBUG "-O0 -ggdb")
set(CMAKE_C_FLAGS_RELEASE "-Os")
set(CMAKE_C_COMPILER gcc)
set(CMAKE_SHARED_LINKER_FLAGS "-lm")

# Set paths
add_subdirectory(src)
add_subdirectory(tests)

# Testing
enable_testing()

# Configuration options
option(USE_OPENMP "Use OpenMP for threading" YES)

if(USE_OPENMP)
	include(FindOpenMP)
	if(OPENMP_FOUND)
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
	endif()
endif(USE_OPENMP)

# Output the configuration
configure_file(${PROJECT_SOURCE_DIR}/cwavelet-config.h.in ${PROJECT_SOURCE_DIR}/cwavelet-config.h)