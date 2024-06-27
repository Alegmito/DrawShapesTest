add_library(Controls controls.cpp)

target_link_libraries(Controls glm glfw)
target_include_directories(Controls INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})