cmake_minimum_required(VERSION 3.10)# compiler settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(tcp_chat VERSION 0.05) # project

# if a library was needed (making a folder to organize a certain portion of the project)
# you would type:
# add_library(library_name STATIC library_name/file_name.cpp)
# target_include_directories(library_name PUBLIC %{CMAKE_CURRENT_SOURCE_DIR}/library_name/include)
# you could also insert this in a CMakeLists.txt inside the library itself and then add here:
# add_subdirectory(library_name)

# add_executable(tcp_chat main.cpp) # executable
file(GLOB_RECURSE SRC_FILES src/*.cpp) # recursively finds .cpp files in src and saves them to variable SRC_FILES
add_executable(tcp_chat ${SRC_FILES}) # adds all the .cpp files to be compiled


target_include_directories(tcp_chat PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include) # includes




# testing
project(cmake_test VERSION 0.0.1 LANGUAGES CXX)

file(GLOB_RECURSE TEST_FILES test/*.cpp src/*.cpp)
list(FILTER TEST_FILES EXCLUDE REGEX ".*src/Main.cpp$")
# list(REMOVE_ITEM TEST_FILES "src/Main.cpp")
add_executable(tests ${TEST_FILES})

# target_include_directories(tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/test)
target_include_directories(tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include) # includes
