cmake_minimum_required(VERSION 3.15)
project(AdvRendering)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra")

set(PROJECT_NAME AdvRendering )

add_subdirectory(libs/glm)

add_executable(${PROJECT_NAME}
                src/main.cpp
        src/Objects.hpp
        src/Polysolv.c
        src/Polysolv.h
        src/RT.cpp
        libs/lodepng/lodepng.h
        libs/lodepng/lodepng.cc
        src/environment.cpp src/environment.h)

target_link_libraries(${PROJECT_NAME} glm)