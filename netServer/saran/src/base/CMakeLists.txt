
set(SRC_LIST
 Log.cc
 LogAppender.cc
 LogBuffer.cc
 LogFile.cc
 Condition.cc
 Thread.cc
 ThreadPool.cc
)

add_library(saranBase SHARED ${SRC_LIST})


if (SARAN_BUILD_TESTS)
    add_executable(saranBaseTest "")
    target_sources(saranBaseTest
    PRIVATE
        RBTreeTest.cpp
    )

    target_link_libraries(saranBaseTest saranBase ${GTEST_LIBRARIES} ${GMOCK_LIBRARIES} gtest_main)
    add_test(NAME "saranBaseTest" COMMAND "saranBaseTest")
endif()

install(TARGETS saranBase DESTINATION ${PROJECT_SOURCE_DIR}/lib)
file(GLOB HEADERS "*.h")
install(FILES ${HEADERS} DESTINATION ${PROJECT_SOURCE_DIR}/include)