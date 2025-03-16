add_executable(atomichanApp myApp.cpp)
target_link_libraries(atomichanApp PUBLIC atomichanLib)
target_include_directories(atomichanApp PUBLIC "${CMAKE_SOURCE_DIR}/model/include")