#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act2", BeforeFunc2);

void actDummy(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x164);
    if (p) {
        p[0x10E] = a1;
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act2", func_002013B0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act2", func_00201470);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act2", func_002015C8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act2", func_002015F8);

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
