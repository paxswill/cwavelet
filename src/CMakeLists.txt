# src

# Include the definitions file
include_directories(${CMAKE_SOURCE_DIR})

# Add libraries
add_library(haar haar)
add_library(daubechies daubechies)
add_library(wavelet wavelet)
add_library(circ_array circ_array)
