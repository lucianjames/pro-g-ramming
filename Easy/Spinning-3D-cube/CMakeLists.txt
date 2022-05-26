cmake_minimum_required(VERSION 3.23.1) # Set based on the current version im using, will probably work on lots of other versions too

project(SPINNING-3D-CUBE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3") # Optimisation!!!
# set(OpenGL_GL_PREFERENCE "GLVND")

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${GLFW3_INCLUDE_DIR})

add_executable(main main.cpp glad/glad.c)
target_link_libraries(main glfw3 GL X11 pthread Xrandr Xi dl)

# A warning to anyone reading this cmake file:
#   I am fucking retarded and I don't know how to use cmake properly. :)