cmake_minimum_required(VERSION 3.28)

set(projectName pngReader)

project( ${projectName} )

file(GLOB SRCS src/*.cpp)

include_directories(include)

add_executable(${projectName} ${SRCS})