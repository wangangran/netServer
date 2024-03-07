if ("${GOOGLETEST_ROOT}" STREQUAL "")
    set(GOOGLETEST_ROOT "/usr/local")
endif()

if ("${GOOGLEMOCK_ROOT}" STREQUAL "")
    set(GOOGLEMOCK_ROOT "/usr/local")
endif()
#在${GOOGLETEST_ROOT}/include目录下查找gtest/gtest.h文件，赋值给GTEST_INCLUDE_DIR变量
find_path(GTEST_INCLUDE_DIR
    NAMES gtest/gtest.h
    PATHS ${GOOGLETEST_ROOT}/include)

find_path(GMOCK_INCLUDE_DIR
    NAMES gmock/gmock.h
    PATHS ${GOOGLEMOCK_ROOT}/include)

find_library(GTEST_LIBRARIES
    NAME gtest
    PATHS ${GOOGLETEST_ROOT}/lib)

find_library(GMOCK_LIBRARIES
    NAME gmock
    PATHS ${GOOGLEMOCK_ROOT}/lib)

if(NOT GTEST_LIBRARIES OR NOT GMOCK_LIBRARIES)
    message(STATUS "fetch GTest from https://github.com/google/googletest.git")
    include(FetchContent)
    # 拉取googletest
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.11.0
    )
    # 使用googletest内容
    FetchContent_MakeAvailable(googletest)
    set(GTEST_INCLUDE_DIR ${CMAKE_BINARY_DIR}/_deps/googletest-src/googletest/include/)
    set(GMOCK_INCLUDE_DIR ${CMAKE_BINARY_DIR}/_deps/googletest-src/googlemock/include/)
    set(GTEST_LIBRARIES gtest_main)
    set(GMOCK_LIBRARIES gmock_main)
else()
    message(STATUS "use system GTest")
endif()

message(STATUS "GTest: " ${GTEST_INCLUDE_DIR}, ${GTEST_LIBRARIES})
message(STATUS "GMock: " ${GMOCK_INCLUDE_DIR}, ${GMOCK_LIBRARIES})