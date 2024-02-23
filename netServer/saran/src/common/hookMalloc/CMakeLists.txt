# gcc -fPIC -shared -o libhookMalloc.so HookMalloc.c -ldl
# 运行时LD_PRELOAD=./libmemoryhook ./xxx
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")

set(SRC_LIST
 MemoryHook.c
)

add_library(memoryhook SHARED ${SRC_LIST})
# install(TARGETS tpmalloc ${PROJECT_SOURCE_DIR}/../../lib)
target_link_libraries(memoryhook dl jemalloc)