set(SRC_LIST
 Accept.cc
 Channel.cc
 Epoll.cc
 HostAddr.cc
 Socket.cc
 TcpConnect.cc
 TcpServer.cc
)

add_library(sunwar_net SHARED ${SRC_LIST})
install(TARGETS sunwar_net DESTINATION ${PROJECT_SOURCE_DIR}/lib)

file(GLOB HEADERS "*.h")
install(FILES ${HEADERS} DESTINATION ${PROJECT_SOURCE_DIR}/include)