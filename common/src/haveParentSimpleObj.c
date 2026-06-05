#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/haveParentSimpleObj", ParentSimpleObjGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/haveParentSimpleObj", ParentSimpleObjDL);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/haveParentSimpleObj", InitParentSimpleObjGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/haveParentSimpleObj", func_001AA268);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/haveParentSimpleObj", func_001AA680);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/haveParentSimpleObj", func_001AAAD0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/haveParentSimpleObj", func_001AAC60);

void func_001AACD8(void) {
}

void func_001AACE0(void) {
    for (;;) {
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/haveParentSimpleObj", func_001AAD00);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/haveParentSimpleObj", func_001AAD88);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/haveParentSimpleObj", func_001AAE80);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/haveParentSimpleObj", func_001AAFA0);

extern int D_0062C14C;
extern int D_0062C150;
extern int D_0062C154;

void func_001AB108(void) {
    D_0062C14C = 0;
    D_0062C150 = 1;
    D_0062C154 = 0;
}

extern void *AllocPObj(void);
extern char D_0029F060[];

char *func_001AB120(void) {
    int idx = *(int *)((char *)AllocPObj() + 0xC);
    return D_0029F060 + idx * 0x64;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/haveParentSimpleObj", func_001AB158);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/haveParentSimpleObj", func_001AB1B0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/haveParentSimpleObj", func_001AB248);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/haveParentSimpleObj", func_001AB298);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/haveParentSimpleObj", func_001AB470);

extern unsigned short D_004AF010[];
extern int D_0062B234;
extern short D_0062B238;
extern void backStageSave(void);

void func_001AB720(void) {
    if (D_004AF010[0x21] == 0x82) {
        D_0062B238 = D_004AF010[0x22];
    }
    D_0062B234++;
    backStageSave();
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/haveParentSimpleObj", func_001AB750);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/haveParentSimpleObj", func_001AB7A8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/haveParentSimpleObj", func_001AB7F0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/haveParentSimpleObj", func_001AB858);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/haveParentSimpleObj", func_001AB8A0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/haveParentSimpleObj", func_001AB908);

void func_001AB948(void) {
    long long *p = (long long *)D_004AF010;
    long long mask = -2;
    int i;
    for (i = 0xB5; i >= 0; i--) {
        *p &= mask;
        p = (long long *)((char *)p + 0x40);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/haveParentSimpleObj", func_001AB980);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/haveParentSimpleObj", func_001AB9B8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/haveParentSimpleObj", func_001AB9F8);


/* recovered struct shapes */
typedef struct {
    unsigned short     f_2;  /* 0x02 */
    unsigned long long f_40;  /* 0x40 */
    unsigned short     f_42;  /* 0x42 */
    unsigned short     f_44;  /* 0x44 */
} S_004AF010;  /* stride 0x40 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_4;  /* 0x04 */
} S_004AE610;  /* stride 0x8 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_004AEE68;  /* stride 0x4 */

/* end struct shapes */
