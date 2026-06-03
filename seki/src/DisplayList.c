#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayList", dl_Init);

int dl_Clear(void) {
    return 0x14;
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayList", dl_Swap);

extern int D_0062BAE0, D_0062BAE4, D_0062BAE8, D_0062BAEC, D_0062BAF0;

void dl_PushPriority(void) {
    D_0062BAE0 = 0;
    D_0062BAF0 = 0x80;
    D_0062BAEC = 0x80;
    D_0062BAE8 = 0x80;
    D_0062BAE4 = 0x80;
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayList", dl_PopPriority);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayList", dl_Debug);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayList", dl_CloseDma);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayList", dl_Out);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayList", dl_SetDLPriority);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayList", dl_OpenDma);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayList", dl_GetPri);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayList", func_001F8660);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_4;  /* 0x04 */
    unsigned long long f_8;  /* 0x08 */
    unsigned int       f_10;  /* 0x10 */
    unsigned long long f_18;  /* 0x18 */
    unsigned int       f_24;  /* 0x24 */
} S_0070A5C0;  /* stride 0x28 */

typedef struct {
    char               f_0;  /* 0x00 */
    char               f_1;  /* 0x01 */
} S_004C3750;  /* stride 0x2 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0070A830;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00613750;  /* stride 0x4 */

/* end struct shapes */
