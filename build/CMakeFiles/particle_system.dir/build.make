# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.11

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Users/jwalsh/.brew/Cellar/cmake/3.11.0/bin/cmake

# The command to remove a file.
RM = /Users/jwalsh/.brew/Cellar/cmake/3.11.0/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/jwalsh/Documents/42/particle_system

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jwalsh/Documents/42/particle_system/build

# Include any dependencies generated for this target.
include CMakeFiles/particle_system.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/particle_system.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/particle_system.dir/flags.make

CMakeFiles/particle_system.dir/src/main.cpp.o: CMakeFiles/particle_system.dir/flags.make
CMakeFiles/particle_system.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jwalsh/Documents/42/particle_system/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/particle_system.dir/src/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/particle_system.dir/src/main.cpp.o -c /Users/jwalsh/Documents/42/particle_system/src/main.cpp

CMakeFiles/particle_system.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/particle_system.dir/src/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jwalsh/Documents/42/particle_system/src/main.cpp > CMakeFiles/particle_system.dir/src/main.cpp.i

CMakeFiles/particle_system.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/particle_system.dir/src/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jwalsh/Documents/42/particle_system/src/main.cpp -o CMakeFiles/particle_system.dir/src/main.cpp.s

CMakeFiles/particle_system.dir/src/Shader.cpp.o: CMakeFiles/particle_system.dir/flags.make
CMakeFiles/particle_system.dir/src/Shader.cpp.o: ../src/Shader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jwalsh/Documents/42/particle_system/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/particle_system.dir/src/Shader.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/particle_system.dir/src/Shader.cpp.o -c /Users/jwalsh/Documents/42/particle_system/src/Shader.cpp

CMakeFiles/particle_system.dir/src/Shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/particle_system.dir/src/Shader.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jwalsh/Documents/42/particle_system/src/Shader.cpp > CMakeFiles/particle_system.dir/src/Shader.cpp.i

CMakeFiles/particle_system.dir/src/Shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/particle_system.dir/src/Shader.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jwalsh/Documents/42/particle_system/src/Shader.cpp -o CMakeFiles/particle_system.dir/src/Shader.cpp.s

CMakeFiles/particle_system.dir/src/OpenGLWindow.cpp.o: CMakeFiles/particle_system.dir/flags.make
CMakeFiles/particle_system.dir/src/OpenGLWindow.cpp.o: ../src/OpenGLWindow.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jwalsh/Documents/42/particle_system/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/particle_system.dir/src/OpenGLWindow.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/particle_system.dir/src/OpenGLWindow.cpp.o -c /Users/jwalsh/Documents/42/particle_system/src/OpenGLWindow.cpp

CMakeFiles/particle_system.dir/src/OpenGLWindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/particle_system.dir/src/OpenGLWindow.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jwalsh/Documents/42/particle_system/src/OpenGLWindow.cpp > CMakeFiles/particle_system.dir/src/OpenGLWindow.cpp.i

CMakeFiles/particle_system.dir/src/OpenGLWindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/particle_system.dir/src/OpenGLWindow.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jwalsh/Documents/42/particle_system/src/OpenGLWindow.cpp -o CMakeFiles/particle_system.dir/src/OpenGLWindow.cpp.s

CMakeFiles/particle_system.dir/src/OpenCLContext.cpp.o: CMakeFiles/particle_system.dir/flags.make
CMakeFiles/particle_system.dir/src/OpenCLContext.cpp.o: ../src/OpenCLContext.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jwalsh/Documents/42/particle_system/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/particle_system.dir/src/OpenCLContext.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/particle_system.dir/src/OpenCLContext.cpp.o -c /Users/jwalsh/Documents/42/particle_system/src/OpenCLContext.cpp

CMakeFiles/particle_system.dir/src/OpenCLContext.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/particle_system.dir/src/OpenCLContext.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jwalsh/Documents/42/particle_system/src/OpenCLContext.cpp > CMakeFiles/particle_system.dir/src/OpenCLContext.cpp.i

CMakeFiles/particle_system.dir/src/OpenCLContext.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/particle_system.dir/src/OpenCLContext.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jwalsh/Documents/42/particle_system/src/OpenCLContext.cpp -o CMakeFiles/particle_system.dir/src/OpenCLContext.cpp.s

CMakeFiles/particle_system.dir/src/GUI.cpp.o: CMakeFiles/particle_system.dir/flags.make
CMakeFiles/particle_system.dir/src/GUI.cpp.o: ../src/GUI.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jwalsh/Documents/42/particle_system/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/particle_system.dir/src/GUI.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/particle_system.dir/src/GUI.cpp.o -c /Users/jwalsh/Documents/42/particle_system/src/GUI.cpp

CMakeFiles/particle_system.dir/src/GUI.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/particle_system.dir/src/GUI.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jwalsh/Documents/42/particle_system/src/GUI.cpp > CMakeFiles/particle_system.dir/src/GUI.cpp.i

CMakeFiles/particle_system.dir/src/GUI.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/particle_system.dir/src/GUI.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jwalsh/Documents/42/particle_system/src/GUI.cpp -o CMakeFiles/particle_system.dir/src/GUI.cpp.s

CMakeFiles/particle_system.dir/src/Camera.cpp.o: CMakeFiles/particle_system.dir/flags.make
CMakeFiles/particle_system.dir/src/Camera.cpp.o: ../src/Camera.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jwalsh/Documents/42/particle_system/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/particle_system.dir/src/Camera.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/particle_system.dir/src/Camera.cpp.o -c /Users/jwalsh/Documents/42/particle_system/src/Camera.cpp

CMakeFiles/particle_system.dir/src/Camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/particle_system.dir/src/Camera.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jwalsh/Documents/42/particle_system/src/Camera.cpp > CMakeFiles/particle_system.dir/src/Camera.cpp.i

CMakeFiles/particle_system.dir/src/Camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/particle_system.dir/src/Camera.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jwalsh/Documents/42/particle_system/src/Camera.cpp -o CMakeFiles/particle_system.dir/src/Camera.cpp.s

CMakeFiles/particle_system.dir/libs/nanogui/ext/glad/src/glad.c.o: CMakeFiles/particle_system.dir/flags.make
CMakeFiles/particle_system.dir/libs/nanogui/ext/glad/src/glad.c.o: ../libs/nanogui/ext/glad/src/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jwalsh/Documents/42/particle_system/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/particle_system.dir/libs/nanogui/ext/glad/src/glad.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/particle_system.dir/libs/nanogui/ext/glad/src/glad.c.o   -c /Users/jwalsh/Documents/42/particle_system/libs/nanogui/ext/glad/src/glad.c

CMakeFiles/particle_system.dir/libs/nanogui/ext/glad/src/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/particle_system.dir/libs/nanogui/ext/glad/src/glad.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/jwalsh/Documents/42/particle_system/libs/nanogui/ext/glad/src/glad.c > CMakeFiles/particle_system.dir/libs/nanogui/ext/glad/src/glad.c.i

CMakeFiles/particle_system.dir/libs/nanogui/ext/glad/src/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/particle_system.dir/libs/nanogui/ext/glad/src/glad.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/jwalsh/Documents/42/particle_system/libs/nanogui/ext/glad/src/glad.c -o CMakeFiles/particle_system.dir/libs/nanogui/ext/glad/src/glad.c.s

CMakeFiles/particle_system.dir/src/ExceptionMsg.cpp.o: CMakeFiles/particle_system.dir/flags.make
CMakeFiles/particle_system.dir/src/ExceptionMsg.cpp.o: ../src/ExceptionMsg.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jwalsh/Documents/42/particle_system/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/particle_system.dir/src/ExceptionMsg.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/particle_system.dir/src/ExceptionMsg.cpp.o -c /Users/jwalsh/Documents/42/particle_system/src/ExceptionMsg.cpp

CMakeFiles/particle_system.dir/src/ExceptionMsg.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/particle_system.dir/src/ExceptionMsg.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jwalsh/Documents/42/particle_system/src/ExceptionMsg.cpp > CMakeFiles/particle_system.dir/src/ExceptionMsg.cpp.i

CMakeFiles/particle_system.dir/src/ExceptionMsg.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/particle_system.dir/src/ExceptionMsg.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jwalsh/Documents/42/particle_system/src/ExceptionMsg.cpp -o CMakeFiles/particle_system.dir/src/ExceptionMsg.cpp.s

# Object files for target particle_system
particle_system_OBJECTS = \
"CMakeFiles/particle_system.dir/src/main.cpp.o" \
"CMakeFiles/particle_system.dir/src/Shader.cpp.o" \
"CMakeFiles/particle_system.dir/src/OpenGLWindow.cpp.o" \
"CMakeFiles/particle_system.dir/src/OpenCLContext.cpp.o" \
"CMakeFiles/particle_system.dir/src/GUI.cpp.o" \
"CMakeFiles/particle_system.dir/src/Camera.cpp.o" \
"CMakeFiles/particle_system.dir/libs/nanogui/ext/glad/src/glad.c.o" \
"CMakeFiles/particle_system.dir/src/ExceptionMsg.cpp.o"

# External object files for target particle_system
particle_system_EXTERNAL_OBJECTS =

particle_system: CMakeFiles/particle_system.dir/src/main.cpp.o
particle_system: CMakeFiles/particle_system.dir/src/Shader.cpp.o
particle_system: CMakeFiles/particle_system.dir/src/OpenGLWindow.cpp.o
particle_system: CMakeFiles/particle_system.dir/src/OpenCLContext.cpp.o
particle_system: CMakeFiles/particle_system.dir/src/GUI.cpp.o
particle_system: CMakeFiles/particle_system.dir/src/Camera.cpp.o
particle_system: CMakeFiles/particle_system.dir/libs/nanogui/ext/glad/src/glad.c.o
particle_system: CMakeFiles/particle_system.dir/src/ExceptionMsg.cpp.o
particle_system: CMakeFiles/particle_system.dir/build.make
particle_system: libs/nanogui/libnanogui.dylib
particle_system: CMakeFiles/particle_system.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jwalsh/Documents/42/particle_system/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable particle_system"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/particle_system.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/particle_system.dir/build: particle_system

.PHONY : CMakeFiles/particle_system.dir/build

CMakeFiles/particle_system.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/particle_system.dir/cmake_clean.cmake
.PHONY : CMakeFiles/particle_system.dir/clean

CMakeFiles/particle_system.dir/depend:
	cd /Users/jwalsh/Documents/42/particle_system/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jwalsh/Documents/42/particle_system /Users/jwalsh/Documents/42/particle_system /Users/jwalsh/Documents/42/particle_system/build /Users/jwalsh/Documents/42/particle_system/build /Users/jwalsh/Documents/42/particle_system/build/CMakeFiles/particle_system.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/particle_system.dir/depend

