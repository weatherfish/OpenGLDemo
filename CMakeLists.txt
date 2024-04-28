cmake_minimum_required(VERSION 3.12)
project(CGL3DDemo)

set(GLM_H /opt/homebrew/Cellar/glm/1.0.1/include)
set(GLEW_H /opt/homebrew/Cellar/glew/2.2.0_1/include)
set(GLFW_H /opt/homebrew/Cellar/glfw/3.4/include)
# set(GLM_H /usr/local/Cellar/glm/1.0.1/include)
# set(GLEW_H /usr/local/Cellar/glew/2.2.0_1/include)
# set(GLFW_H /usr/local/Cellar/glfw/3.4/include)

include_directories(${GLM_H} ${GLEW_H} ${GLFW_H})

set(GLEW_LINK /opt/homebrew/Cellar/glew/2.2.0_1/lib/libGLEW.2.2.dylib)
set(GLFW_LINK /opt/homebrew/Cellar/glfw/3.4/lib/libglfw.3.dylib)
# set(GLEW_LINK /usr/local/Cellar/glew/2.2.0_1/lib/libGLEW.2.2.dylib)
# set(GLFW_LINK /usr/local/Cellar/glfw/3.4/lib/libglfw.3.dylib)
link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK})

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_BUILD_TYPE Debug CACHE STRING "Set build type to debug")

add_definitions(-DDEBUG)

add_subdirectory(wrapper)
add_subdirectory(applicaiton)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(GLOB SOURCE_FILES "*.cpp")

add_executable(CGL3DDemo ${SOURCE_FILES})

target_link_libraries(CGL3DDemo "-framework OpenGL")
target_link_libraries(CGL3DDemo "-framework GLUT")
target_link_libraries(CGL3DDemo wrapper applicaiton)
