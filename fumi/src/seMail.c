#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/seMail", setMailTarget);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/seMail", seMail);

extern int D_0062BB64;

int seMailTargetDistCheck(void) {
    return D_0062BB64;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/seMail", func_00202578);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/seMail", func_00202638);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/seMail", func_00202688);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/seMail", func_002026E0);

int func_00202728(int a0, int a1) {
    float x = *(float *)(a0 + 4);
    float y = *(float *)(a1 + 4);
    if (x < y) {
        return -1;
    }
    if (x > y) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/seMail", func_00202760);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/seMail", func_002027F0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/seMail", func_00202868);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/seMail", func_00202900);

extern char D_004C6FF0[];

void func_00202980(int a0) {
    int *elem = (int *)(D_004C6FF0 + a0 * 0x34);
    int *next = (int *)elem[2];
    int *prev = (int *)elem[3];
    elem[5] = 1;
    next[2] = (int)prev;
    prev[3] = (int)next;
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_004C7018;  /* stride 0x34 */

/* end struct shapes */
