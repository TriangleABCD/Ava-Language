# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Code/cpp/Ava-Language/ava_lexer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Code/cpp/Ava-Language/ava_lexer/build

# Include any dependencies generated for this target.
include CMakeFiles/ava_leer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ava_leer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ava_leer.dir/flags.make

CMakeFiles/ava_leer.dir/src/Grammar.cpp.o: CMakeFiles/ava_leer.dir/flags.make
CMakeFiles/ava_leer.dir/src/Grammar.cpp.o: ../src/Grammar.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Code/cpp/Ava-Language/ava_lexer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ava_leer.dir/src/Grammar.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ava_leer.dir/src/Grammar.cpp.o -c /Code/cpp/Ava-Language/ava_lexer/src/Grammar.cpp

CMakeFiles/ava_leer.dir/src/Grammar.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ava_leer.dir/src/Grammar.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Code/cpp/Ava-Language/ava_lexer/src/Grammar.cpp > CMakeFiles/ava_leer.dir/src/Grammar.cpp.i

CMakeFiles/ava_leer.dir/src/Grammar.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ava_leer.dir/src/Grammar.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Code/cpp/Ava-Language/ava_lexer/src/Grammar.cpp -o CMakeFiles/ava_leer.dir/src/Grammar.cpp.s

CMakeFiles/ava_leer.dir/src/NFA.cpp.o: CMakeFiles/ava_leer.dir/flags.make
CMakeFiles/ava_leer.dir/src/NFA.cpp.o: ../src/NFA.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Code/cpp/Ava-Language/ava_lexer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ava_leer.dir/src/NFA.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ava_leer.dir/src/NFA.cpp.o -c /Code/cpp/Ava-Language/ava_lexer/src/NFA.cpp

CMakeFiles/ava_leer.dir/src/NFA.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ava_leer.dir/src/NFA.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Code/cpp/Ava-Language/ava_lexer/src/NFA.cpp > CMakeFiles/ava_leer.dir/src/NFA.cpp.i

CMakeFiles/ava_leer.dir/src/NFA.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ava_leer.dir/src/NFA.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Code/cpp/Ava-Language/ava_lexer/src/NFA.cpp -o CMakeFiles/ava_leer.dir/src/NFA.cpp.s

CMakeFiles/ava_leer.dir/src/main.cpp.o: CMakeFiles/ava_leer.dir/flags.make
CMakeFiles/ava_leer.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Code/cpp/Ava-Language/ava_lexer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/ava_leer.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ava_leer.dir/src/main.cpp.o -c /Code/cpp/Ava-Language/ava_lexer/src/main.cpp

CMakeFiles/ava_leer.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ava_leer.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Code/cpp/Ava-Language/ava_lexer/src/main.cpp > CMakeFiles/ava_leer.dir/src/main.cpp.i

CMakeFiles/ava_leer.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ava_leer.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Code/cpp/Ava-Language/ava_lexer/src/main.cpp -o CMakeFiles/ava_leer.dir/src/main.cpp.s

# Object files for target ava_leer
ava_leer_OBJECTS = \
"CMakeFiles/ava_leer.dir/src/Grammar.cpp.o" \
"CMakeFiles/ava_leer.dir/src/NFA.cpp.o" \
"CMakeFiles/ava_leer.dir/src/main.cpp.o"

# External object files for target ava_leer
ava_leer_EXTERNAL_OBJECTS =

ava_leer: CMakeFiles/ava_leer.dir/src/Grammar.cpp.o
ava_leer: CMakeFiles/ava_leer.dir/src/NFA.cpp.o
ava_leer: CMakeFiles/ava_leer.dir/src/main.cpp.o
ava_leer: CMakeFiles/ava_leer.dir/build.make
ava_leer: CMakeFiles/ava_leer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Code/cpp/Ava-Language/ava_lexer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable ava_leer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ava_leer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ava_leer.dir/build: ava_leer

.PHONY : CMakeFiles/ava_leer.dir/build

CMakeFiles/ava_leer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ava_leer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ava_leer.dir/clean

CMakeFiles/ava_leer.dir/depend:
	cd /Code/cpp/Ava-Language/ava_lexer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Code/cpp/Ava-Language/ava_lexer /Code/cpp/Ava-Language/ava_lexer /Code/cpp/Ava-Language/ava_lexer/build /Code/cpp/Ava-Language/ava_lexer/build /Code/cpp/Ava-Language/ava_lexer/build/CMakeFiles/ava_leer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ava_leer.dir/depend

