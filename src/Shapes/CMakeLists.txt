add_library(Shapes Shapes.cpp)

target_link_libraries(Shapes glm glfw glad)
target_include_directories(Shapes INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})