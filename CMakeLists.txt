cmake_minimum_required(VERSION 3.13)
project(philosopher C)

set(CMAKE_C_STANDARD 99)

add_executable(philosopher main.c src/philosopher/philosopher.c src/init/util.c src/philosopher/philosopher.h src/init/util.h src/config.h src/input/input.c src/input/input.h)
find_package(Threads REQUIRED)
target_link_libraries(philosopher Threads::Threads)