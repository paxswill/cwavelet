# tests

# Testing
enable_testing()

# include the source
include_directories(${CMAKE_SOURCE_DIR}/src)

# Build the testing executables
add_executable(testLogBase2 logBase2)
target_link_libraries(testLogBase2 wavelet daubechies haar circ_array m)
add_executable(testHaar haarTest testingCommon.h)
target_link_libraries(testHaar wavelet daubechies haar circ_array m)
add_executable(testCircularArray circ_arrayTest)
target_link_libraries(testCircularArray circ_array m)
add_executable(testDaubechies daubechiesTest)
target_link_libraries(testDaubechies wavelet daubechies haar circ_array m)

# Testing stuff
add_test(logBase2 testLogBase2)
add_test(haar testHaar)
add_test(circularArray testCircularArray)
add_test(daubechies testDaubechies)
