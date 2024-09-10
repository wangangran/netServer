cmake_minimum_required(VERSION 3.15)

project(saran)

option(SARAN_BUILD_TESTS "Build Saran's unit tests" ON)

set(CXX_FLAGS
    -g
    -Wall
    -std=c++20
    -pthread
    -fcoroutines
)

enable_testing()

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
message(STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")

# 通过调用外部cmake文件夹的FindGTest.cmake找到googletest需要的头文件路径和库文件
if(${SARAN_BUILD_TESTS})
    find_package(GTest)
endif()

set(HEADERS_PATH
    ${GTEST_INCLUDE_DIR}
    ${GMOCK_INCLUDE_DIR}
)

string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

if(${CMAKE_BUILD_TYPE} MATCHES "Release")
    set(BuildType "Release")
else()
    set(BuildType "Debug")
endif()

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib/)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/${BuildType})

include_directories("${PROJECT_SOURCE_DIR}/src")

add_subdirectory("${PROJECT_SOURCE_DIR}/src/base")
#add_subdirectory("${PROJECT_SOURCE_DIR}/src/net")
#add_subdirectory("${PROJECT_SOURCE_DIR}/src/common/hookMalloc")
#add_subdirectory("${PROJECT_SOURCE_DIR}/src/dataStruct")
