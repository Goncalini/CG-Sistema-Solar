# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/emamartins12/GIT/CG-2324/Fase 2/src"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/emamartins12/GIT/CG-2324/Fase 2/src/Build"

# Include any dependencies generated for this target.
include CMakeFiles/figures_lib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/figures_lib.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/figures_lib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/figures_lib.dir/flags.make

CMakeFiles/figures_lib.dir/generator/plane.cpp.o: CMakeFiles/figures_lib.dir/flags.make
CMakeFiles/figures_lib.dir/generator/plane.cpp.o: ../generator/plane.cpp
CMakeFiles/figures_lib.dir/generator/plane.cpp.o: CMakeFiles/figures_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/emamartins12/GIT/CG-2324/Fase 2/src/Build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/figures_lib.dir/generator/plane.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/figures_lib.dir/generator/plane.cpp.o -MF CMakeFiles/figures_lib.dir/generator/plane.cpp.o.d -o CMakeFiles/figures_lib.dir/generator/plane.cpp.o -c "/home/emamartins12/GIT/CG-2324/Fase 2/src/generator/plane.cpp"

CMakeFiles/figures_lib.dir/generator/plane.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/figures_lib.dir/generator/plane.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/emamartins12/GIT/CG-2324/Fase 2/src/generator/plane.cpp" > CMakeFiles/figures_lib.dir/generator/plane.cpp.i

CMakeFiles/figures_lib.dir/generator/plane.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/figures_lib.dir/generator/plane.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/emamartins12/GIT/CG-2324/Fase 2/src/generator/plane.cpp" -o CMakeFiles/figures_lib.dir/generator/plane.cpp.s

CMakeFiles/figures_lib.dir/generator/box.cpp.o: CMakeFiles/figures_lib.dir/flags.make
CMakeFiles/figures_lib.dir/generator/box.cpp.o: ../generator/box.cpp
CMakeFiles/figures_lib.dir/generator/box.cpp.o: CMakeFiles/figures_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/emamartins12/GIT/CG-2324/Fase 2/src/Build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/figures_lib.dir/generator/box.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/figures_lib.dir/generator/box.cpp.o -MF CMakeFiles/figures_lib.dir/generator/box.cpp.o.d -o CMakeFiles/figures_lib.dir/generator/box.cpp.o -c "/home/emamartins12/GIT/CG-2324/Fase 2/src/generator/box.cpp"

CMakeFiles/figures_lib.dir/generator/box.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/figures_lib.dir/generator/box.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/emamartins12/GIT/CG-2324/Fase 2/src/generator/box.cpp" > CMakeFiles/figures_lib.dir/generator/box.cpp.i

CMakeFiles/figures_lib.dir/generator/box.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/figures_lib.dir/generator/box.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/emamartins12/GIT/CG-2324/Fase 2/src/generator/box.cpp" -o CMakeFiles/figures_lib.dir/generator/box.cpp.s

CMakeFiles/figures_lib.dir/generator/sphere.cpp.o: CMakeFiles/figures_lib.dir/flags.make
CMakeFiles/figures_lib.dir/generator/sphere.cpp.o: ../generator/sphere.cpp
CMakeFiles/figures_lib.dir/generator/sphere.cpp.o: CMakeFiles/figures_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/emamartins12/GIT/CG-2324/Fase 2/src/Build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/figures_lib.dir/generator/sphere.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/figures_lib.dir/generator/sphere.cpp.o -MF CMakeFiles/figures_lib.dir/generator/sphere.cpp.o.d -o CMakeFiles/figures_lib.dir/generator/sphere.cpp.o -c "/home/emamartins12/GIT/CG-2324/Fase 2/src/generator/sphere.cpp"

CMakeFiles/figures_lib.dir/generator/sphere.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/figures_lib.dir/generator/sphere.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/emamartins12/GIT/CG-2324/Fase 2/src/generator/sphere.cpp" > CMakeFiles/figures_lib.dir/generator/sphere.cpp.i

CMakeFiles/figures_lib.dir/generator/sphere.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/figures_lib.dir/generator/sphere.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/emamartins12/GIT/CG-2324/Fase 2/src/generator/sphere.cpp" -o CMakeFiles/figures_lib.dir/generator/sphere.cpp.s

CMakeFiles/figures_lib.dir/generator/cone.cpp.o: CMakeFiles/figures_lib.dir/flags.make
CMakeFiles/figures_lib.dir/generator/cone.cpp.o: ../generator/cone.cpp
CMakeFiles/figures_lib.dir/generator/cone.cpp.o: CMakeFiles/figures_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/emamartins12/GIT/CG-2324/Fase 2/src/Build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/figures_lib.dir/generator/cone.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/figures_lib.dir/generator/cone.cpp.o -MF CMakeFiles/figures_lib.dir/generator/cone.cpp.o.d -o CMakeFiles/figures_lib.dir/generator/cone.cpp.o -c "/home/emamartins12/GIT/CG-2324/Fase 2/src/generator/cone.cpp"

CMakeFiles/figures_lib.dir/generator/cone.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/figures_lib.dir/generator/cone.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/emamartins12/GIT/CG-2324/Fase 2/src/generator/cone.cpp" > CMakeFiles/figures_lib.dir/generator/cone.cpp.i

CMakeFiles/figures_lib.dir/generator/cone.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/figures_lib.dir/generator/cone.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/emamartins12/GIT/CG-2324/Fase 2/src/generator/cone.cpp" -o CMakeFiles/figures_lib.dir/generator/cone.cpp.s

CMakeFiles/figures_lib.dir/generator/ring.cpp.o: CMakeFiles/figures_lib.dir/flags.make
CMakeFiles/figures_lib.dir/generator/ring.cpp.o: ../generator/ring.cpp
CMakeFiles/figures_lib.dir/generator/ring.cpp.o: CMakeFiles/figures_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/emamartins12/GIT/CG-2324/Fase 2/src/Build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/figures_lib.dir/generator/ring.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/figures_lib.dir/generator/ring.cpp.o -MF CMakeFiles/figures_lib.dir/generator/ring.cpp.o.d -o CMakeFiles/figures_lib.dir/generator/ring.cpp.o -c "/home/emamartins12/GIT/CG-2324/Fase 2/src/generator/ring.cpp"

CMakeFiles/figures_lib.dir/generator/ring.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/figures_lib.dir/generator/ring.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/emamartins12/GIT/CG-2324/Fase 2/src/generator/ring.cpp" > CMakeFiles/figures_lib.dir/generator/ring.cpp.i

CMakeFiles/figures_lib.dir/generator/ring.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/figures_lib.dir/generator/ring.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/emamartins12/GIT/CG-2324/Fase 2/src/generator/ring.cpp" -o CMakeFiles/figures_lib.dir/generator/ring.cpp.s

CMakeFiles/figures_lib.dir/generator/torus.cpp.o: CMakeFiles/figures_lib.dir/flags.make
CMakeFiles/figures_lib.dir/generator/torus.cpp.o: ../generator/torus.cpp
CMakeFiles/figures_lib.dir/generator/torus.cpp.o: CMakeFiles/figures_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/emamartins12/GIT/CG-2324/Fase 2/src/Build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/figures_lib.dir/generator/torus.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/figures_lib.dir/generator/torus.cpp.o -MF CMakeFiles/figures_lib.dir/generator/torus.cpp.o.d -o CMakeFiles/figures_lib.dir/generator/torus.cpp.o -c "/home/emamartins12/GIT/CG-2324/Fase 2/src/generator/torus.cpp"

CMakeFiles/figures_lib.dir/generator/torus.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/figures_lib.dir/generator/torus.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/emamartins12/GIT/CG-2324/Fase 2/src/generator/torus.cpp" > CMakeFiles/figures_lib.dir/generator/torus.cpp.i

CMakeFiles/figures_lib.dir/generator/torus.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/figures_lib.dir/generator/torus.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/emamartins12/GIT/CG-2324/Fase 2/src/generator/torus.cpp" -o CMakeFiles/figures_lib.dir/generator/torus.cpp.s

# Object files for target figures_lib
figures_lib_OBJECTS = \
"CMakeFiles/figures_lib.dir/generator/plane.cpp.o" \
"CMakeFiles/figures_lib.dir/generator/box.cpp.o" \
"CMakeFiles/figures_lib.dir/generator/sphere.cpp.o" \
"CMakeFiles/figures_lib.dir/generator/cone.cpp.o" \
"CMakeFiles/figures_lib.dir/generator/ring.cpp.o" \
"CMakeFiles/figures_lib.dir/generator/torus.cpp.o"

# External object files for target figures_lib
figures_lib_EXTERNAL_OBJECTS =

libfigures_lib.a: CMakeFiles/figures_lib.dir/generator/plane.cpp.o
libfigures_lib.a: CMakeFiles/figures_lib.dir/generator/box.cpp.o
libfigures_lib.a: CMakeFiles/figures_lib.dir/generator/sphere.cpp.o
libfigures_lib.a: CMakeFiles/figures_lib.dir/generator/cone.cpp.o
libfigures_lib.a: CMakeFiles/figures_lib.dir/generator/ring.cpp.o
libfigures_lib.a: CMakeFiles/figures_lib.dir/generator/torus.cpp.o
libfigures_lib.a: CMakeFiles/figures_lib.dir/build.make
libfigures_lib.a: CMakeFiles/figures_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/emamartins12/GIT/CG-2324/Fase 2/src/Build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX static library libfigures_lib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/figures_lib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/figures_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/figures_lib.dir/build: libfigures_lib.a
.PHONY : CMakeFiles/figures_lib.dir/build

CMakeFiles/figures_lib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/figures_lib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/figures_lib.dir/clean

CMakeFiles/figures_lib.dir/depend:
	cd "/home/emamartins12/GIT/CG-2324/Fase 2/src/Build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/emamartins12/GIT/CG-2324/Fase 2/src" "/home/emamartins12/GIT/CG-2324/Fase 2/src" "/home/emamartins12/GIT/CG-2324/Fase 2/src/Build" "/home/emamartins12/GIT/CG-2324/Fase 2/src/Build" "/home/emamartins12/GIT/CG-2324/Fase 2/src/Build/CMakeFiles/figures_lib.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/figures_lib.dir/depend

