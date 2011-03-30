# tests

# include the source
include_directories(${CMAKE_SOURCE_DIR}/src)
link_directories(${CMAKE_BINARY_DIR}/src)

add_executable(testing tests)
target_link_libraries(testing wavelet haar daubechies circ_array)
