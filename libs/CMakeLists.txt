#
# GLFW options
#
option (GLFW_INSTALL OFF)
option (GLFW_BUILD_DOCS OFF)
option (GLFW_BUILD_EXAMPLES OFF)
option (GLFW_BUILD_TESTS OFF)
add_subdirectory (glfw)
add_subdirectory (glm)
add_library(glad STATIC glad/src/glad.c)
#
# Set include paths
#

target_include_directories(glad PUBLIC glad/include)