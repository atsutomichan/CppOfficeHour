#[add_library(ClassStudyExampleClassLib STATIC ClsStudyExUtilsA.cpp ClsStudyExUtilsB.cpp)]
#[target_link_libraries(ClassStudyExampleLib PUBLIC FFTW3::fftw3)]
#[target_include_directories(ClassStudyExampleLib PUBLIC "${CMAKE_SOURCE_DIR}/myutils/include")]

add_library(atomichanClassLib STATIC B.cpp)
target_link_libraries(atomichanClassLib PUBLIC FFTW3::fftw3)
target_include_directories(atomichanClassLib PUBLIC "${CMAKE_SOURCE_DIR}/model/include")
target_include_directories(atomichanClassLib PUBLIC "${CMAKE_SOURCE_DIR}/myutils/include")