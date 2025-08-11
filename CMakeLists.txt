cmake_minimum_required(VERSION 3.16)
project(myVector)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(vector_main src/main.cpp)
target_include_directories(vector_main PUBLIC ${CMAKE_SOURCE_DIR}/include)

enable_testing()

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)  # 👈 Only needed for Windows users (safe to keep)
FetchContent_MakeAvailable(googletest)

add_executable(vector_tests
    tests/test_construction.cpp
    tests/test_assignment.cpp
    tests/test_access.cpp
    tests/test_utilities.cpp
    tests/test_iterators.cpp
)

target_include_directories(vector_tests PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(vector_tests PRIVATE gtest_main)

include(GoogleTest)
gtest_discover_tests(vector_tests)