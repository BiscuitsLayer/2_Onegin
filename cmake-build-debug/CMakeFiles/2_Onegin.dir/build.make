# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.14

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2019.2.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2019.2.1\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Admin\CLionProjects\2_Onegin

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Admin\CLionProjects\2_Onegin\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/2_Onegin.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/2_Onegin.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/2_Onegin.dir/flags.make

CMakeFiles/2_Onegin.dir/main.cpp.obj: CMakeFiles/2_Onegin.dir/flags.make
CMakeFiles/2_Onegin.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Admin\CLionProjects\2_Onegin\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/2_Onegin.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\2_Onegin.dir\main.cpp.obj -c C:\Users\Admin\CLionProjects\2_Onegin\main.cpp

CMakeFiles/2_Onegin.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/2_Onegin.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Admin\CLionProjects\2_Onegin\main.cpp > CMakeFiles\2_Onegin.dir\main.cpp.i

CMakeFiles/2_Onegin.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/2_Onegin.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Admin\CLionProjects\2_Onegin\main.cpp -o CMakeFiles\2_Onegin.dir\main.cpp.s

# Object files for target 2_Onegin
2_Onegin_OBJECTS = \
"CMakeFiles/2_Onegin.dir/main.cpp.obj"

# External object files for target 2_Onegin
2_Onegin_EXTERNAL_OBJECTS =

2_Onegin.exe: CMakeFiles/2_Onegin.dir/main.cpp.obj
2_Onegin.exe: CMakeFiles/2_Onegin.dir/build.make
2_Onegin.exe: CMakeFiles/2_Onegin.dir/linklibs.rsp
2_Onegin.exe: CMakeFiles/2_Onegin.dir/objects1.rsp
2_Onegin.exe: CMakeFiles/2_Onegin.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Admin\CLionProjects\2_Onegin\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 2_Onegin.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\2_Onegin.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/2_Onegin.dir/build: 2_Onegin.exe

.PHONY : CMakeFiles/2_Onegin.dir/build

CMakeFiles/2_Onegin.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\2_Onegin.dir\cmake_clean.cmake
.PHONY : CMakeFiles/2_Onegin.dir/clean

CMakeFiles/2_Onegin.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Admin\CLionProjects\2_Onegin C:\Users\Admin\CLionProjects\2_Onegin C:\Users\Admin\CLionProjects\2_Onegin\cmake-build-debug C:\Users\Admin\CLionProjects\2_Onegin\cmake-build-debug C:\Users\Admin\CLionProjects\2_Onegin\cmake-build-debug\CMakeFiles\2_Onegin.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/2_Onegin.dir/depend
