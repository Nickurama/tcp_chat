# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_SOURCE_DIR = /home/luna/Documents/code/tcp_chat

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/luna/Documents/code/tcp_chat/build

# Include any dependencies generated for this target.
include CMakeFiles/tcp_chat.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/tcp_chat.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/tcp_chat.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tcp_chat.dir/flags.make

CMakeFiles/tcp_chat.dir/src/Client.cpp.o: CMakeFiles/tcp_chat.dir/flags.make
CMakeFiles/tcp_chat.dir/src/Client.cpp.o: /home/luna/Documents/code/tcp_chat/src/Client.cpp
CMakeFiles/tcp_chat.dir/src/Client.cpp.o: CMakeFiles/tcp_chat.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/luna/Documents/code/tcp_chat/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tcp_chat.dir/src/Client.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/tcp_chat.dir/src/Client.cpp.o -MF CMakeFiles/tcp_chat.dir/src/Client.cpp.o.d -o CMakeFiles/tcp_chat.dir/src/Client.cpp.o -c /home/luna/Documents/code/tcp_chat/src/Client.cpp

CMakeFiles/tcp_chat.dir/src/Client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/tcp_chat.dir/src/Client.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/luna/Documents/code/tcp_chat/src/Client.cpp > CMakeFiles/tcp_chat.dir/src/Client.cpp.i

CMakeFiles/tcp_chat.dir/src/Client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/tcp_chat.dir/src/Client.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/luna/Documents/code/tcp_chat/src/Client.cpp -o CMakeFiles/tcp_chat.dir/src/Client.cpp.s

CMakeFiles/tcp_chat.dir/src/Main.cpp.o: CMakeFiles/tcp_chat.dir/flags.make
CMakeFiles/tcp_chat.dir/src/Main.cpp.o: /home/luna/Documents/code/tcp_chat/src/Main.cpp
CMakeFiles/tcp_chat.dir/src/Main.cpp.o: CMakeFiles/tcp_chat.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/luna/Documents/code/tcp_chat/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/tcp_chat.dir/src/Main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/tcp_chat.dir/src/Main.cpp.o -MF CMakeFiles/tcp_chat.dir/src/Main.cpp.o.d -o CMakeFiles/tcp_chat.dir/src/Main.cpp.o -c /home/luna/Documents/code/tcp_chat/src/Main.cpp

CMakeFiles/tcp_chat.dir/src/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/tcp_chat.dir/src/Main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/luna/Documents/code/tcp_chat/src/Main.cpp > CMakeFiles/tcp_chat.dir/src/Main.cpp.i

CMakeFiles/tcp_chat.dir/src/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/tcp_chat.dir/src/Main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/luna/Documents/code/tcp_chat/src/Main.cpp -o CMakeFiles/tcp_chat.dir/src/Main.cpp.s

CMakeFiles/tcp_chat.dir/src/NetworkError.cpp.o: CMakeFiles/tcp_chat.dir/flags.make
CMakeFiles/tcp_chat.dir/src/NetworkError.cpp.o: /home/luna/Documents/code/tcp_chat/src/NetworkError.cpp
CMakeFiles/tcp_chat.dir/src/NetworkError.cpp.o: CMakeFiles/tcp_chat.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/luna/Documents/code/tcp_chat/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/tcp_chat.dir/src/NetworkError.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/tcp_chat.dir/src/NetworkError.cpp.o -MF CMakeFiles/tcp_chat.dir/src/NetworkError.cpp.o.d -o CMakeFiles/tcp_chat.dir/src/NetworkError.cpp.o -c /home/luna/Documents/code/tcp_chat/src/NetworkError.cpp

CMakeFiles/tcp_chat.dir/src/NetworkError.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/tcp_chat.dir/src/NetworkError.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/luna/Documents/code/tcp_chat/src/NetworkError.cpp > CMakeFiles/tcp_chat.dir/src/NetworkError.cpp.i

CMakeFiles/tcp_chat.dir/src/NetworkError.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/tcp_chat.dir/src/NetworkError.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/luna/Documents/code/tcp_chat/src/NetworkError.cpp -o CMakeFiles/tcp_chat.dir/src/NetworkError.cpp.s

CMakeFiles/tcp_chat.dir/src/Server.cpp.o: CMakeFiles/tcp_chat.dir/flags.make
CMakeFiles/tcp_chat.dir/src/Server.cpp.o: /home/luna/Documents/code/tcp_chat/src/Server.cpp
CMakeFiles/tcp_chat.dir/src/Server.cpp.o: CMakeFiles/tcp_chat.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/luna/Documents/code/tcp_chat/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/tcp_chat.dir/src/Server.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/tcp_chat.dir/src/Server.cpp.o -MF CMakeFiles/tcp_chat.dir/src/Server.cpp.o.d -o CMakeFiles/tcp_chat.dir/src/Server.cpp.o -c /home/luna/Documents/code/tcp_chat/src/Server.cpp

CMakeFiles/tcp_chat.dir/src/Server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/tcp_chat.dir/src/Server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/luna/Documents/code/tcp_chat/src/Server.cpp > CMakeFiles/tcp_chat.dir/src/Server.cpp.i

CMakeFiles/tcp_chat.dir/src/Server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/tcp_chat.dir/src/Server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/luna/Documents/code/tcp_chat/src/Server.cpp -o CMakeFiles/tcp_chat.dir/src/Server.cpp.s

CMakeFiles/tcp_chat.dir/src/UniqueSocket.cpp.o: CMakeFiles/tcp_chat.dir/flags.make
CMakeFiles/tcp_chat.dir/src/UniqueSocket.cpp.o: /home/luna/Documents/code/tcp_chat/src/UniqueSocket.cpp
CMakeFiles/tcp_chat.dir/src/UniqueSocket.cpp.o: CMakeFiles/tcp_chat.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/luna/Documents/code/tcp_chat/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/tcp_chat.dir/src/UniqueSocket.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/tcp_chat.dir/src/UniqueSocket.cpp.o -MF CMakeFiles/tcp_chat.dir/src/UniqueSocket.cpp.o.d -o CMakeFiles/tcp_chat.dir/src/UniqueSocket.cpp.o -c /home/luna/Documents/code/tcp_chat/src/UniqueSocket.cpp

CMakeFiles/tcp_chat.dir/src/UniqueSocket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/tcp_chat.dir/src/UniqueSocket.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/luna/Documents/code/tcp_chat/src/UniqueSocket.cpp > CMakeFiles/tcp_chat.dir/src/UniqueSocket.cpp.i

CMakeFiles/tcp_chat.dir/src/UniqueSocket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/tcp_chat.dir/src/UniqueSocket.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/luna/Documents/code/tcp_chat/src/UniqueSocket.cpp -o CMakeFiles/tcp_chat.dir/src/UniqueSocket.cpp.s

# Object files for target tcp_chat
tcp_chat_OBJECTS = \
"CMakeFiles/tcp_chat.dir/src/Client.cpp.o" \
"CMakeFiles/tcp_chat.dir/src/Main.cpp.o" \
"CMakeFiles/tcp_chat.dir/src/NetworkError.cpp.o" \
"CMakeFiles/tcp_chat.dir/src/Server.cpp.o" \
"CMakeFiles/tcp_chat.dir/src/UniqueSocket.cpp.o"

# External object files for target tcp_chat
tcp_chat_EXTERNAL_OBJECTS =

tcp_chat: CMakeFiles/tcp_chat.dir/src/Client.cpp.o
tcp_chat: CMakeFiles/tcp_chat.dir/src/Main.cpp.o
tcp_chat: CMakeFiles/tcp_chat.dir/src/NetworkError.cpp.o
tcp_chat: CMakeFiles/tcp_chat.dir/src/Server.cpp.o
tcp_chat: CMakeFiles/tcp_chat.dir/src/UniqueSocket.cpp.o
tcp_chat: CMakeFiles/tcp_chat.dir/build.make
tcp_chat: CMakeFiles/tcp_chat.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/luna/Documents/code/tcp_chat/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable tcp_chat"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tcp_chat.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tcp_chat.dir/build: tcp_chat
.PHONY : CMakeFiles/tcp_chat.dir/build

CMakeFiles/tcp_chat.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tcp_chat.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tcp_chat.dir/clean

CMakeFiles/tcp_chat.dir/depend:
	cd /home/luna/Documents/code/tcp_chat/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/luna/Documents/code/tcp_chat /home/luna/Documents/code/tcp_chat /home/luna/Documents/code/tcp_chat/build /home/luna/Documents/code/tcp_chat/build /home/luna/Documents/code/tcp_chat/build/CMakeFiles/tcp_chat.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/tcp_chat.dir/depend

