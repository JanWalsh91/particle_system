# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_COMMAND = /Users/tgros/.brew/Cellar/cmake/3.11.0/bin/cmake

# The command to remove a file.
RM = /Users/tgros/.brew/Cellar/cmake/3.11.0/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/tgros/Projects/human_gl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/tgros/Projects/human_gl

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target install/local
install/local: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	/Users/tgros/.brew/Cellar/cmake/3.11.0/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local

# Special rule for the target install/local
install/local/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	/Users/tgros/.brew/Cellar/cmake/3.11.0/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local/fast

# Special rule for the target install/strip
install/strip: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	/Users/tgros/.brew/Cellar/cmake/3.11.0/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip

# Special rule for the target install/strip
install/strip/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	/Users/tgros/.brew/Cellar/cmake/3.11.0/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip/fast

# Special rule for the target install
install: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/Users/tgros/.brew/Cellar/cmake/3.11.0/bin/cmake -P cmake_install.cmake
.PHONY : install

# Special rule for the target install
install/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/Users/tgros/.brew/Cellar/cmake/3.11.0/bin/cmake -P cmake_install.cmake
.PHONY : install/fast

# Special rule for the target list_install_components
list_install_components:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Available install components are: \"Unspecified\""
.PHONY : list_install_components

# Special rule for the target list_install_components
list_install_components/fast: list_install_components

.PHONY : list_install_components/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/Users/tgros/.brew/Cellar/cmake/3.11.0/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/Users/tgros/.brew/Cellar/cmake/3.11.0/bin/ccmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/tgros/Projects/human_gl/CMakeFiles /Users/tgros/Projects/human_gl/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/tgros/Projects/human_gl/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named nanogui_test

# Build rule for target.
nanogui_test: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 nanogui_test
.PHONY : nanogui_test

# fast build rule for target.
nanogui_test/fast:
	$(MAKE) -f CMakeFiles/nanogui_test.dir/build.make CMakeFiles/nanogui_test.dir/build
.PHONY : nanogui_test/fast

#=============================================================================
# Target rules for targets named nanogui-obj

# Build rule for target.
nanogui-obj: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 nanogui-obj
.PHONY : nanogui-obj

# fast build rule for target.
nanogui-obj/fast:
	$(MAKE) -f libs/nanogui/CMakeFiles/nanogui-obj.dir/build.make libs/nanogui/CMakeFiles/nanogui-obj.dir/build
.PHONY : nanogui-obj/fast

#=============================================================================
# Target rules for targets named nanogui-python-obj

# Build rule for target.
nanogui-python-obj: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 nanogui-python-obj
.PHONY : nanogui-python-obj

# fast build rule for target.
nanogui-python-obj/fast:
	$(MAKE) -f libs/nanogui/CMakeFiles/nanogui-python-obj.dir/build.make libs/nanogui/CMakeFiles/nanogui-python-obj.dir/build
.PHONY : nanogui-python-obj/fast

#=============================================================================
# Target rules for targets named nanogui

# Build rule for target.
nanogui: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 nanogui
.PHONY : nanogui

# fast build rule for target.
nanogui/fast:
	$(MAKE) -f libs/nanogui/CMakeFiles/nanogui.dir/build.make libs/nanogui/CMakeFiles/nanogui.dir/build
.PHONY : nanogui/fast

#=============================================================================
# Target rules for targets named example_icons

# Build rule for target.
example_icons: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 example_icons
.PHONY : example_icons

# fast build rule for target.
example_icons/fast:
	$(MAKE) -f libs/nanogui/CMakeFiles/example_icons.dir/build.make libs/nanogui/CMakeFiles/example_icons.dir/build
.PHONY : example_icons/fast

#=============================================================================
# Target rules for targets named example1

# Build rule for target.
example1: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 example1
.PHONY : example1

# fast build rule for target.
example1/fast:
	$(MAKE) -f libs/nanogui/CMakeFiles/example1.dir/build.make libs/nanogui/CMakeFiles/example1.dir/build
.PHONY : example1/fast

#=============================================================================
# Target rules for targets named example4

# Build rule for target.
example4: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 example4
.PHONY : example4

# fast build rule for target.
example4/fast:
	$(MAKE) -f libs/nanogui/CMakeFiles/example4.dir/build.make libs/nanogui/CMakeFiles/example4.dir/build
.PHONY : example4/fast

#=============================================================================
# Target rules for targets named example2

# Build rule for target.
example2: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 example2
.PHONY : example2

# fast build rule for target.
example2/fast:
	$(MAKE) -f libs/nanogui/CMakeFiles/example2.dir/build.make libs/nanogui/CMakeFiles/example2.dir/build
.PHONY : example2/fast

#=============================================================================
# Target rules for targets named example3

# Build rule for target.
example3: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 example3
.PHONY : example3

# fast build rule for target.
example3/fast:
	$(MAKE) -f libs/nanogui/CMakeFiles/example3.dir/build.make libs/nanogui/CMakeFiles/example3.dir/build
.PHONY : example3/fast

#=============================================================================
# Target rules for targets named nanogui-python

# Build rule for target.
nanogui-python: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 nanogui-python
.PHONY : nanogui-python

# fast build rule for target.
nanogui-python/fast:
	$(MAKE) -f libs/nanogui/CMakeFiles/nanogui-python.dir/build.make libs/nanogui/CMakeFiles/nanogui-python.dir/build
.PHONY : nanogui-python/fast

#=============================================================================
# Target rules for targets named glfw_objects

# Build rule for target.
glfw_objects: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 glfw_objects
.PHONY : glfw_objects

# fast build rule for target.
glfw_objects/fast:
	$(MAKE) -f libs/nanogui/ext_build/glfw/src/CMakeFiles/glfw_objects.dir/build.make libs/nanogui/ext_build/glfw/src/CMakeFiles/glfw_objects.dir/build
.PHONY : glfw_objects/fast

#=============================================================================
# Target rules for targets named glfw

# Build rule for target.
glfw: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 glfw
.PHONY : glfw

# fast build rule for target.
glfw/fast:
	$(MAKE) -f libs/nanogui/ext_build/glfw/src/CMakeFiles/glfw.dir/build.make libs/nanogui/ext_build/glfw/src/CMakeFiles/glfw.dir/build
.PHONY : glfw/fast

example3.o: example3.cpp.o

.PHONY : example3.o

# target to build an object file
example3.cpp.o:
	$(MAKE) -f CMakeFiles/nanogui_test.dir/build.make CMakeFiles/nanogui_test.dir/example3.cpp.o
.PHONY : example3.cpp.o

example3.i: example3.cpp.i

.PHONY : example3.i

# target to preprocess a source file
example3.cpp.i:
	$(MAKE) -f CMakeFiles/nanogui_test.dir/build.make CMakeFiles/nanogui_test.dir/example3.cpp.i
.PHONY : example3.cpp.i

example3.s: example3.cpp.s

.PHONY : example3.s

# target to generate assembly for a file
example3.cpp.s:
	$(MAKE) -f CMakeFiles/nanogui_test.dir/build.make CMakeFiles/nanogui_test.dir/example3.cpp.s
.PHONY : example3.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... install/local"
	@echo "... install/strip"
	@echo "... install"
	@echo "... nanogui_test"
	@echo "... list_install_components"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... nanogui-obj"
	@echo "... nanogui-python-obj"
	@echo "... nanogui"
	@echo "... example_icons"
	@echo "... example1"
	@echo "... example4"
	@echo "... example2"
	@echo "... example3"
	@echo "... nanogui-python"
	@echo "... glfw_objects"
	@echo "... glfw"
	@echo "... example3.o"
	@echo "... example3.i"
	@echo "... example3.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

