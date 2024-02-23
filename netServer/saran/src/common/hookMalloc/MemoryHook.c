#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <jemalloc/jemalloc.h>

extern void* __libc_calloc(size_t, size_t);

static void* (*hookMalloc)(size_t) = NULL;
static void* (*hookCalloc)(size_t, size_t) = NULL;
static void* (*hookRealloc)(void *, size_t) = NULL;
static void (*hookFree)(void *) = NULL;

static void initHookMalloc() {
    hookMalloc = dlsym(RTLD_NEXT, "je_malloc");
    
    if (!hookMalloc) {
        fprintf(stderr, "initHookMalloc failed!\n");
        exit(1);
    }

    fprintf(stderr, "initHookMalloc successfully!\n");
}

static void initHookCalloc() {
    hookCalloc = dlsym(RTLD_NEXT, "je_calloc");
    
    if (!hookCalloc) {
        fprintf(stderr, "initHookCalloc failed!\n");
        exit(1);
    }

    fprintf(stderr, "initHookCalloc successfully!\n");
}

static void initHookRealloc() {
    hookRealloc = dlsym(RTLD_NEXT, "je_realloc");
    
    if (!hookRealloc) {
        fprintf(stderr, "initHookRealloc failed!\n");
        exit(1);
    }

    fprintf(stderr, "initHookRealloc successfully!\n");
}

static void initHookFree() {
    hookFree = dlsym(RTLD_NEXT, "je_free");
    
    if (!hookFree) {
        fprintf(stderr, "initHookFree failed!\n");
        exit(1);
    }

    fprintf(stderr, "initHookFree successfully!\n");
}

void *malloc(size_t size) {
    if (!hookMalloc) {
        initHookMalloc();
    }
    void *ret = hookMalloc(size);
    // fprintf(stderr, "hookMalloc: size = %ld, pointer = %p\n", size, ret);                    // 如果打印，一定要用fprintf(stderr)，否则会产生无限循环，因为fprintf(stdout)也会使用malloc！

    return ret;
}

void *calloc(size_t nitems, size_t size) {
    if (!hookMalloc) {
        return __libc_calloc(nitems, size);
    }

    if (!hookCalloc) {
        initHookCalloc();
    }
    void *ret = hookCalloc(nitems, size);
    // fprintf(stderr, "hookCalloc: size = %ld, pointer = %p\n", size, ret);                    // 如果打印，一定要用fprintf(stderr)，否则会产生无限循环，因为fprintf(stdout)也会使用malloc！

    return ret;
}

void *realloc(void *ptr, size_t size) {
    if (!hookRealloc) {
        initHookRealloc();
    }
    void *ret = hookRealloc(ptr, size);
    // fprintf(stderr, "hookRealloc: size = %ld, pointer = %p\n", size, ret);                    // 如果打印，一定要用fprintf(stderr)，否则会产生无限循环，因为fprintf(stdout)也会使用malloc！

    return ret;
}

void free(void *ptr) {
    if (!hookFree) {
        initHookFree();
    }

    hookFree(ptr);
    // fprintf(stderr, "hookFree: pointer = %p\n", ptr);                                        // 如果打印，一定要用fprintf(stderr)，否则会产生无限循环，因为fprintf(stdout)也会使用malloc！
}

