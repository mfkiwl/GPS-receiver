cmake_minimum_required(VERSION 3.19)

project(GPS)

file(GLOB test_SRC
     "*.hpp"
     "*.cpp"
)

add_executable(test ${test_SRC})

source_group(src FILES ${test_SRC})

set_target_properties(
    test PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
)
