# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(cpp_test VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(cpp_test src/main.cpp)

# Include directories (if needed)
# target_include_directories(cpp_test PRIVATE include)

# Link libraries (if needed)
# target_link_libraries(cpp_test PRIVATE some_library)