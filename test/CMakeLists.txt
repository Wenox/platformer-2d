cmake_minimum_required(VERSION 3.16)

project(Tests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall")


include_directories(lib/googletest/googletest/include
        lib/googletest/googlemock/include)

set(TEST_SOURCE_FILES tests.cpp
        myTest.cpp)

add_subdirectory(lib/googletest)
link_libraries(gmock)

add_executable(Tests_run ${TEST_SOURCE_FILES})