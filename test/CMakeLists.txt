
set(projectName test)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(GTest REQUIRED)

# Create a variable to your test input file directory.
set(INPUT_DIR "${CMAKE_SOURCE_DIR}/test/input")
set(OUTPUT_DIR "${CMAKE_SOURCE_DIR}/test/output")
file(GLOB SRCS *.cpp)

add_executable(${projectName} ${SRCS})

target_link_libraries(${projectName} gtest::gtest pngio)

# Pass the input path directory to the test program.
target_compile_definitions(${projectName} PUBLIC 
                            INPUT_DIR="${INPUT_DIR}"
                            OUTPUT_DIR="${OUTPUT_DIR}")
