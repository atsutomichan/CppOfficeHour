cmake_minimum_required(VERSION 3.16)
project(CppStudyExampleProject
  VERSION 0.0.1
  LANGUAGES CXX
)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# You can set this flag to `-g` when developing to enable debugging
set(CMAKE_CXX_FLAGS "-O3")

find_package(Catch2 3 REQUIRED)
find_package(FFTW3 REQUIRED)

add_subdirectory(app)
add_subdirectory(model)
add_subdirectory(myutils)
add_subdirectory(test)
