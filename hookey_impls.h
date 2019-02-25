#ifndef HOOKY_IMPLS_H
#define HOOKY_IMPLS_H

#include "hookey_common.h"
#include "subhook/subhook.h"

#define Mangle(n) \
    inline I##n* Hookey_##n () { fprintf(stderr, "Hookey Steam Abort %s:%i %s\n", __FILE__, __LINE__, #n); abort(); }
#include "hookey_overrides_uimpld.h"
#undef Mangle

#define Mangle(n) I##n* Hookey_##n ();
#include "hookey_overrides_impld.h"
#undef Mangle

#define Mangle(n) extern subhook_t n##_hook;
#include "hookey_overrides.h"
#undef Mangle

#endif
