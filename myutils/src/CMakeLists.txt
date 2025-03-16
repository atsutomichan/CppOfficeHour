add_library(ClassStudyExampleLib STATIC ClsStudyExUtilsA.cpp ClsStudyExUtilsB.cpp)
target_link_libraries(ClassStudyExampleLib PUBLIC FFTW3::fftw3)
target_include_directories(ClassStudyExampleLib PUBLIC "${CMAKE_SOURCE_DIR}/myutils/include")

add_library(atomichanLib STATIC atomichanUtils.cpp)
target_link_libraries(atomichanLib PUBLIC FFTW3::fftw3)
target_include_directories(atomichanLib PUBLIC "${CMAKE_SOURCE_DIR}/myutils/include")