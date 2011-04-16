# Top level
cmake_minimum_required(VERSION 2.6)
project(cWavelet)

# Build environment
set(CMAKE_C_FLAGS "-std=c99 -Wall -Wextra -pendantic")
set(CMAKE_C_FLAGS_DEBUG "-O0 -ggdb")
set(CMAKE_C_FLAGS_RELEASE "-Os")
set(CMAKE_C_COMPILER gcc)

# Set paths
add_subdirectory(src)
add_subdirectory(tests)

# Testing
enable_testing()

# Configuration options
option(USE_OPENMP "Use OpenMP for threading" YES)

if(USE_OPENMP)
	set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -fopenmp")
	add_definitions(-DUSE_OPENMP)
	find_library(OMP_LIB_PATH omp)
	# Check for an OpenMP library called libomp
	if(OMP_LIB_PATH)
		set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -L${OMP_LIB_PATH} -lomp")
	else(OMP_LIB_PATH)
		# Try for libgomp (GNU OpenMP)
		find_library(GOMP_LIB_PATH gomp)
		if(GOMP_LIB_PATH)
			set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -L${GOMP_LIB_PATH} -lomp")
		endif(GOMP_LIB_PATH)
	endif(OMP_LIB_PATH)
	
endif(USE_OPENMP)

# Output the configuration
configure_file(${PROJECT_SOURCE_DIR}/cwavelet-config.h.in ${PROJECT_SOURCE_DIR}/cwavelet-config.h)