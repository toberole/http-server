# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zhouwei/code/cpp/server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zhouwei/code/cpp/server/build

# Include any dependencies generated for this target.
include CMakeFiles/server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/server.dir/flags.make

CMakeFiles/server.dir/example/main.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/example/main.cpp.o: ../example/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhouwei/code/cpp/server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/server.dir/example/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/example/main.cpp.o -c /home/zhouwei/code/cpp/server/example/main.cpp

CMakeFiles/server.dir/example/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/example/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhouwei/code/cpp/server/example/main.cpp > CMakeFiles/server.dir/example/main.cpp.i

CMakeFiles/server.dir/example/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/example/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhouwei/code/cpp/server/example/main.cpp -o CMakeFiles/server.dir/example/main.cpp.s

CMakeFiles/server.dir/src/HttpServer.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/src/HttpServer.cpp.o: ../src/HttpServer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhouwei/code/cpp/server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/server.dir/src/HttpServer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/src/HttpServer.cpp.o -c /home/zhouwei/code/cpp/server/src/HttpServer.cpp

CMakeFiles/server.dir/src/HttpServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/src/HttpServer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhouwei/code/cpp/server/src/HttpServer.cpp > CMakeFiles/server.dir/src/HttpServer.cpp.i

CMakeFiles/server.dir/src/HttpServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/src/HttpServer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhouwei/code/cpp/server/src/HttpServer.cpp -o CMakeFiles/server.dir/src/HttpServer.cpp.s

CMakeFiles/server.dir/src/http_msg_handler.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/src/http_msg_handler.c.o: ../src/http_msg_handler.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhouwei/code/cpp/server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/server.dir/src/http_msg_handler.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/server.dir/src/http_msg_handler.c.o -c /home/zhouwei/code/cpp/server/src/http_msg_handler.c

CMakeFiles/server.dir/src/http_msg_handler.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/src/http_msg_handler.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/zhouwei/code/cpp/server/src/http_msg_handler.c > CMakeFiles/server.dir/src/http_msg_handler.c.i

CMakeFiles/server.dir/src/http_msg_handler.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/src/http_msg_handler.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/zhouwei/code/cpp/server/src/http_msg_handler.c -o CMakeFiles/server.dir/src/http_msg_handler.c.s

CMakeFiles/server.dir/third/parser/http_parser.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/third/parser/http_parser.c.o: ../third/parser/http_parser.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhouwei/code/cpp/server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/server.dir/third/parser/http_parser.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/server.dir/third/parser/http_parser.c.o -c /home/zhouwei/code/cpp/server/third/parser/http_parser.c

CMakeFiles/server.dir/third/parser/http_parser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/third/parser/http_parser.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/zhouwei/code/cpp/server/third/parser/http_parser.c > CMakeFiles/server.dir/third/parser/http_parser.c.i

CMakeFiles/server.dir/third/parser/http_parser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/third/parser/http_parser.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/zhouwei/code/cpp/server/third/parser/http_parser.c -o CMakeFiles/server.dir/third/parser/http_parser.c.s

# Object files for target server
server_OBJECTS = \
"CMakeFiles/server.dir/example/main.cpp.o" \
"CMakeFiles/server.dir/src/HttpServer.cpp.o" \
"CMakeFiles/server.dir/src/http_msg_handler.c.o" \
"CMakeFiles/server.dir/third/parser/http_parser.c.o"

# External object files for target server
server_EXTERNAL_OBJECTS =

libserver.so: CMakeFiles/server.dir/example/main.cpp.o
libserver.so: CMakeFiles/server.dir/src/HttpServer.cpp.o
libserver.so: CMakeFiles/server.dir/src/http_msg_handler.c.o
libserver.so: CMakeFiles/server.dir/third/parser/http_parser.c.o
libserver.so: CMakeFiles/server.dir/build.make
libserver.so: CMakeFiles/server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zhouwei/code/cpp/server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX shared library libserver.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/server.dir/build: libserver.so

.PHONY : CMakeFiles/server.dir/build

CMakeFiles/server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/server.dir/clean

CMakeFiles/server.dir/depend:
	cd /home/zhouwei/code/cpp/server/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zhouwei/code/cpp/server /home/zhouwei/code/cpp/server /home/zhouwei/code/cpp/server/build /home/zhouwei/code/cpp/server/build /home/zhouwei/code/cpp/server/build/CMakeFiles/server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/server.dir/depend

