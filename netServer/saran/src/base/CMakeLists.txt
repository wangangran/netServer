
set(SRC_LIST
 Log.cc
 LogAppender.cc
 LogBuffer.cc
 LogFile.cc
 Condition.cc
 RBNode.cc
 RBTree.cc
 Thread.cc
 ThreadPool.cc
)

add_library(sunwar_base SHARED ${SRC_LIST})
install(TARGETS sunwar_base DESTINATION ${PROJECT_SOURCE_DIR}/lib)

file(GLOB HEADERS "*.h")
install(FILES ${HEADERS} DESTINATION ${PROJECT_SOURCE_DIR}/include)