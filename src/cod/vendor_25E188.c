#include "common.h"

#include "r5900.h"
#include "vu0.h"
#include "math_private.h"
#include "math_private.h"

extern int D_0054A320[];

int sceDmaGetChan(unsigned int a0) {
    if (a0 < 0xA) {
        return D_0054A320[a0];
    }
    return 0;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E188", sceDmaReset);
extern int D_0054A348[];

int sceDmaDebug(int a0) {
    int old = D_0054A348[0];
    D_0054A348[0] = a0;
    return old;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E188", sceDmaPutEnv);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E188", sceDmaGetEnv);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E188", sceDmaPutStallAddr);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E188", sceDmaSend);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E188", sceDmaSendN);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E188", sceDmaSendI);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E188", sceDmaRecv);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E188", sceDmaRecvN);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E188", sceDmaRecvI);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E188", sceDmaSync);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E188", sceDmaWatch);
int sceDmaPause(void *a0) {
    int v = *(int *)a0;
    *(int *)a0 = v & ~0x100;
    return ((unsigned int)v >> 8) & 1;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E188", sceDmaRestart);
