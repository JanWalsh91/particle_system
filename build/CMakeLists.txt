cmake_minimum_required(VERSION 3.5)
project(particle_system)

find_package(OpenCL REQUIRED)
include_directories(${OpenCL_INCLUDE_DIRS})
include_directories(include)
include_directories(include/glad/include)
include_directories(libs/glfw/include)
link_directories(${OpenCL_LIBRARY})
link_directories(libs/glfw/src)
FIND_LIBRARY(COCOA_LIBRARY Cocoa)
FIND_LIBRARY(CORE_VIDEO CoreVideo)
FIND_LIBRARY(IO_KIT IOKit)

set(
	SOURCE_FILES
	src/main.cpp
	src/Shader.cpp
	src/OpenGLWindow.cpp
	src/OpenCLContext.cpp
	src/FPS.cpp
	src/Camera.cpp
	src/Forces.cpp
	src/ParticleSystem.cpp
	include/glad/src/glad.c
	src/ExceptionMsg.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g")

add_executable(particle_system ${SOURCE_FILES})

target_include_directories(particle_system PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(particle_system OpenCL::OpenCL)
target_link_libraries(particle_system glfw3)
target_link_libraries(particle_system ${COCOA_LIBRARY})
target_link_libraries(particle_system ${CORE_VIDEO})
target_link_libraries(particle_system ${IO_KIT})
