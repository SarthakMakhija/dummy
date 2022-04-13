cmake_minimum_required(VERSION 3.14)

project(skiplist_client)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-g)

include(FetchContent)
set(TESTS_USE_VALGRIND OFF CACHE INTERNAL "")  # Forces the value

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
        googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG        v1.6.1
)
FetchContent_MakeAvailable(googlebenchmark)

#FetchContent_Declare(
#        pmdk
#        GIT_REPOSITORY https://github.com/pmem/pmdk.git
#        GIT_TAG        1.11.1
#)
#FetchContent_MakeAvailable(pmdk)

#install(TARGETS pmdk DESTINATION /usr/local/lib/)

FetchContent_Declare(
        libpmemobjcpp
        GIT_REPOSITORY https://github.com/pmem/libpmemobj-cpp.git
        GIT_TAG        1.13.0
)
FetchContent_MakeAvailable(libpmemobjcpp)

FetchContent_GetProperties(libpmemobjcpp)
message(STATUS "libpmemobjcpp source dir: ${libpmemobjcpp_SOURCE_DIR}")
message(STATUS "libpmemobjcpp binary dir: ${libpmemobjcpp_BINARY_DIR}")
message(STATUS "libpmemobj source dir: ${libpmemobj_SOURCE_DIR}")

find_path(LIBPMEMOBJ_INCLUDE_DIR libpmemobj.h)
find_path(LIBPMEMOBJ_CPP_INCLUDE_DIR make_persistent.hpp)
find_path(LIBPMEM_INCLUDE_DIR libpmem.h)

message(STATUS "LIBPMEMOBJ_INCLUDE_DIR: ${LIBPMEMOBJ_INCLUDE_DIR}")
message(STATUS "LIBPMEM_INCLUDE_DIR: ${LIBPMEM_INCLUDE_DIR}")
message(STATUS "LIBPMEMOBJ_CPP_INCLUDE_DIR: ${LIBPMEMOBJ_CPP_INCLUDE_DIR}")


find_library(LIBPMEM_LIBRARY NAMES pmem libpmem)
find_library(LIBPMEMOBJ_LIBRARY NAMES pmemobj libpmemobj)

# https://google.github.io/googletest/quickstart-cmake.html

add_executable(skiplist_client src/main.cpp)
target_include_directories(skiplist_client PRIVATE ${LIBPMEMOBJ_INCLUDE_DIR} ${LIBPMEM_INCLUDE_DIR})

target_link_libraries(skiplist_client PRIVATE gtest_main benchmark::benchmark benchmark::benchmark_main ${LIBPMEM_LIBRARY} ${LIBPMEMOBJ_LIBRARY})

enable_testing()
add_test(
        NAME skiplist_client
        COMMAND $<TARGET_FILE:skiplist_client>
)