#include "hookey_common.h"
#include "hookey_impls.h"
#include "hookey_steamapps.h"

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <dlfcn.h>

#define Mangle(n) \
    subhook_t n##_hook; \
    static bool n##_did_hook;
#include "hookey_overrides.h"
#undef Mangle

static bool hooked = false;

S_API bool S_CALLTYPE SteamAPI_Init() {
    if (!hooked) {
#define Mangle(n) \
        void* n##_ptr = dlsym(RTLD_NEXT, #n); \
        if (n##_ptr) { \
            n##_hook = subhook_new(n##_ptr, (void*)Hookey_##n, (subhook_flags)0); \
            fprintf(stderr, "Hookey Hook Pre  %p (%u %u) -> %p %s\n", n##_ptr, *(uint8_t*)n##_ptr, *(uint32_t*)(((uint8_t*)n##_ptr) + 1), (void*)Hookey_##n, #n); \
            assert(subhook_install(n##_hook) >= 0); \
            fprintf(stderr, "Hookey Hook Post %p -> %p (%u %u) %s\n", n##_ptr, (void*)Hookey_##n, *(uint8_t*)n##_ptr, *(uint32_t*)(((uint8_t*)n##_ptr) + 1), #n); \
            n##_did_hook = true; \
        } else { \
            fprintf(stderr, "Hookey Hook Not found ? -> %p %s\n", (void*)Hookey_##n, #n); \
            n##_did_hook = false; \
        }
#include "hookey_overrides.h"
#undef Mangle
        hooked = true;
    }
    PopulateDlc();


    bool (*real)();
    *(void**)(&real) = dlsym(RTLD_NEXT, "SteamAPI_Init");
    return real();
}

S_API void S_CALLTYPE SteamAPI_Shutdown() {
    if (hooked) {
#define Mangle(n) \
        if (n##_did_hook) { \
            assert(subhook_remove(n##_hook) >= 0); \
            subhook_free(n##_hook); \
        }
#include "hookey_overrides.h"
#undef Mangle
        hooked = false;
    }

    WipeSteamApps();

    void (*real)();
    *(void**)(&real) = dlsym(RTLD_NEXT, "SteamAPI_Shutdown");
    real();
    return;
}
