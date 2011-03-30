# tests

# include the source
include_directories(${CMAKE_SOURCE_DIR}/src)

# Build the testing executable
add_executable(testing tests)
target_link_libraries(testing wavelet haar daubechies circ_array)
