cmake_minimum_required(VERSION 3.5)
project(partical_system)

find_package(OpenCL REQUIRED)
include_directories(${OpenCL_INCLUDE_DIRS})
link_directories(${OpenCL_LIBRARY})

add_subdirectory(libs/nanogui)
include_directories(libs/nanogui/include)
include_directories(libs/nanogui/ext/glad/include)
include_directories(${NANOGUI_EXTRA_INCS})
add_definitions(${NANOGUI_EXTRA_DEFS})

set(
	SOURCE_FILES
	src/main.cpp
	src/Shader.cpp
	src/OpenGLWindow.cpp
	src/GUI.cpp
	libs/nanogui/ext/glad/src/glad.c
	src/ExceptionMsg.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_executable(partical_system ${SOURCE_FILES})

target_include_directories(partical_system PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(partical_system nanogui ${NANOGUI_EXTRA_LIBS})
target_link_libraries(partical_system OpenCL::OpenCL)

