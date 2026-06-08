#include "common.h"

/* act2 0x164 actor-state view (local) */
typedef struct { char _0[0x438]; int f_438; } Act2State;

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act2", BeforeFunc2);

void actDummy(void *a0, int a1) {
    Act2State *p = *(Act2State **)((char *)a0 + 0x164);
    if (p) {
        p->f_438 = a1;
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act2", func_002013B0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act2", func_00201470);

extern void actInitialize(int a0);
extern void _ACTWait(int a0);

void func_002015C8(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
}

extern void debug_assertMessage(void *a0);
extern char D_00613C00[];

void func_002015F8(int a0, int *a1, int *a2) {
    int idx = a2[0];
    if (idx < 0x10) {
        a2[0] = idx + 1;
        a1[idx] = a0;
        return;
    }
    debug_assertMessage(D_00613C00);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act2", func_00201628);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act2", func_002017A0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act2", func_00201840);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act2", func_002018E0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act2", func_00201AF0);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0070B520;  /* stride 0x8 */

/* end struct shapes */
