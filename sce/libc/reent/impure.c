/* libc.a member impure.o (newlib libc/reent/impure.c): no code, the default
 * reentrancy record and the pointer every reentrant wrapper reads (MAIN.MAP
 * lines 552, 6253-6254: .data 0x2F0, _impure_ptr the one global; .rodata 0x2
 * the locale name "C").  _REENT_INIT's initialiser, spelled out: the three
 * standard streams, an empty emergency buffer, the "C" locale and a rand
 * seed of 1. */
#include <reent.h>

static Reent impure_data = {
    0, &impure_data.sf[0], &impure_data.sf[1], &impure_data.sf[2], 0, "", 0, "C", 0, 0, {0}, 1,
};

Reent *_impure_ptr = &impure_data;
