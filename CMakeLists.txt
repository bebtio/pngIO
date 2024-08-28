cmake_minimum_required(VERSION 3.28)

set(projectName pngio)

project(${projectName})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SRCS src/*.cpp)

include_directories(include)

add_library(${projectName} ${SRCS})

add_compile_options(-Wall -Wextra -Wpedantic -Werror)

add_subdirectory(test)