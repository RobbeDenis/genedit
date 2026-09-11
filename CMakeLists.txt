# CMakeList.txt : CMake project for genedit, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.14)
project("genedit")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Third-party dependancies ---
include(FetchContent)

# FTXUI
FetchContent_Declare(ftxui
    GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
    GIT_TAG v7.0.3
)
FetchContent_MakeAvailable(ftxui)

# --- Setup genedit as library ---
file(GLOB_RECURSE GENEDIT_SOURCES "src/*.cpp")
add_library(genedit_lib ${GENEDIT_SOURCES})
target_include_directories(genedit_lib PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/include/genedit"
)

# --- Project executable ---
add_executable(genedit main.cpp)
target_link_libraries(genedit PRIVATE 
    genedit_lib
    ftxui::ftxui
)

# --- Testing ---
include(CTest)

if(BUILD_TESTING)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest
        GIT_TAG v1.18.0
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    add_subdirectory(tests)
endif()

# --- Benchmarking ---
option(BUILD_BENCHMARKS "Build benchmark executables" ON)

if(BUILD_BENCHMARKS)
    FetchContent_Declare(
        benchmark
        GIT_REPOSITORY https://github.com/google/benchmark
        GIT_TAG v1.9.5
    )
    # Disable internal benchmark tests
    set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(benchmark)

    add_subdirectory(benchmarks)
endif()