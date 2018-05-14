cmake_minimum_required(VERSION 3.5)
project(particle_system)

find_package(OpenCL REQUIRED)
include_directories(${OpenCL_INCLUDE_DIRS})
link_directories(${OpenCL_LIBRARY})

add_subdirectory(libs/nanogui)
include_directories(libs/nanogui/include)
include_directories(libs/nanogui/ext/glad/include)
include_directories(${NANOGUI_EXTRA_INCS})
include_directories(include)
add_definitions(${NANOGUI_EXTRA_DEFS})

set(
	SOURCE_FILES
	src/main.cpp
	src/Shader.cpp
	src/OpenGLWindow.cpp
	src/OpenCLContext.cpp
	src/GUI.cpp
	src/FPS.cpp
	src/Camera.cpp
	src/Forces.cpp
	src/ParticleSystem.cpp
	libs/nanogui/ext/glad/src/glad.c
	src/ExceptionMsg.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g")

add_executable(particle_system ${SOURCE_FILES})

target_include_directories(particle_system PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(particle_system nanogui ${NANOGUI_EXTRA_LIBS})
target_link_libraries(particle_system OpenCL::OpenCL)

