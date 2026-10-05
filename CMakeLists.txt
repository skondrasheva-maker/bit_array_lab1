cmake_minimum_required(VERSION 3.14)
project(BitArrayLab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Werror)
endif()

add_library(bit_array
    src/BitArray.cpp
)
target_include_directories(bit_array PUBLIC include)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(bit_array_tests
    tests/BitArrayTest.cpp
)
target_link_libraries(bit_array_tests PRIVATE bit_array GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(bit_array_tests)
