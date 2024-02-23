set(SRC_LISTS
 log.cc
)

link_directories("${PROJECT_SOURCE_DIR}/lib")

add_executable(log ${SRC_LISTS})
target_link_libraries(log sunwar_base)