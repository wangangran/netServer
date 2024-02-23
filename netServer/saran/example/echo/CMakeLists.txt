set(SRC_LISTS
        echo.cc
        ../../../c++/reflection.h)

link_directories("${PROJECT_SOURCE_DIR}/lib")

add_executable(echo ${SRC_LISTS})
target_link_libraries(echo sunwar_net)