add_executable(ClassStudyExample myClassStudyApp.cpp)
target_link_libraries(ClassStudyExample PUBLIC ClassStudyExampleLib)

add_executable(atomichanApp myApp.cpp)
target_link_libraries(atomichanApp PUBLIC atomichanLib)
target_include_directories(atomichanApp PUBLIC "${CMAKE_SOURCE_DIR}/model/include")

#[original]
#[add_executable(ImageReconstructor ImageReconstructor.cpp)]
#[target_link_libraries(ImageReconstructor PUBLIC OptimisationLib]
#[add_executable(FrequencyReconstructor FrequencyReconstructor.cpp)]
#[target_link_libraries(FrequencyReconstructor PUBLIC OptimisationLib)]
