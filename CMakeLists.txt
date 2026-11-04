cmake_minimum_required(VERSION 3.14)
project(Project1 C)
set(CMAKE_C_STANDARD 11)

# 1. Automatically find all .c files inside the sources directory
file(GLOB SOURCES "sources/*.c")

# 2. Include main.c along with all gathered source files
add_executable(main main.c ${SOURCES})

# 3. Tell the compiler where to look for your header files (.h)
target_include_directories(main PRIVATE headers)