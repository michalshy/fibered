cmake_minimum_required(VERSION 3.20)

# Configure project
set(CMAKE_CXX_STANDARD 17)
project(fibered_test)

# Include directiories
include_directories(fibered)

Include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.4.0 # or a later release
)
FetchContent_MakeAvailable(Catch2)

set(SOURCE_FILES 
    main.cpp
    fibered/Fibered.hpp)

add_executable(fibered_test ${SOURCE_FILES})

# TESTS

# Search for project files
file(GLOB_RECURSE TestsSRCs
       ${PROJECT_SOURCE_DIR}/test/*.cpp)

add_executable(tests 
    ${TestsSRCs}
    )
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
include(CTest)
include(Catch)
catch_discover_tests(tests)