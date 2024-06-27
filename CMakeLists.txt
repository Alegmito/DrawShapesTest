# CMakeList.txt : CMake project for DrawShapesTest, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
  if(NOT WIN32)
    set(GLAD_LIBRARIES dl)
  endif()
endif()


project ("DrawShapesTest")
# set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(libs)
add_subdirectory(src)

# Add source to this project's executable.
add_executable (${PROJECT_NAME} src/DrawShapesTest.cpp src/DrawShapestest.h)

add_custom_target(copy_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/src/Shaders
        ${PROJECT_BINARY_DIR}/Shaders
        COMMENT "Copying resources into binary directory")

add_dependencies(${PROJECT_NAME} copy_resources)

target_link_libraries (${PROJECT_NAME}
                       glfw
                       glm
                       glad
                       Controls
                       LoadShaders
                       Shapes
)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET DrawShapesTest PROPERTY CXX_STANDARD 20)
endif()
