
set(projectName test)

find_package(GTest REQUIRED)

file(GLOB SRCS *.cpp)

add_executable(${projectName} ${SRCS})

target_link_libraries(${projectName} gtest::gtest pngio)