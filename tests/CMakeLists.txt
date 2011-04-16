# tests

# Testing
enable_testing()

# include the source
include_directories(${CMAKE_SOURCE_DIR}/src)

# Include the definitions file
include_directories(${CMAKE_SOURCE_DIR})

# Build the testing executables
add_executable(testLogBase2 logBase2)
target_link_libraries(testLogBase2 wavelet circ_array)
add_executable(testHaar haarTest testingCommon.h)
target_link_libraries(testHaar wavelet haar circ_array)
add_executable(testCircularArray circ_arrayTest)
target_link_libraries(testCircularArray circ_array)
add_executable(testDaubechies daubechiesTest)
target_link_libraries(testDaubechies wavelet daubechies haar circ_array m)
add_executable(testLiftSplit splitTest)
target_link_libraries(testLiftSplit wavelet circ_array)


# Testing stuff
add_test(logBase2 testLogBase2)
add_test(haar testHaar)
add_test(circularArray testCircularArray)
add_test(daubechies testDaubechies)
add_test(liftSplit testLiftSplit)
