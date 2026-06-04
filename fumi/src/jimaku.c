#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", display_texture);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", iosCdvdBackGroundReadJimaku);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", jimakuHandler);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", jimakuMgrBegin);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", jimakuMgrNext);

extern void *D_00629DE8;

void jimakuMgrJump(int a0) {
    if (D_00629DE8) {
        void *p = *(void **)((char *)D_00629DE8 + 0x164);
        void *q = *(void **)((char *)p + 0x678);
        *(int *)((char *)q + 0x3A4) = a0;
    }
}

void jimakuMgrEnd(void) {
    if (D_00629DE8) {
        void *p = *(void **)((char *)D_00629DE8 + 0x164);
        void *q = *(void **)((char *)p + 0x678);
        *(int *)((char *)q + 0x3A4) = 0;
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", jimakuBegin);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", jimakuNext);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", jimakuJump);

int jimakuEnd(void *a0, void *a1) {
    return (int)(*(float *)((char *)a0 + 0x20) - *(float *)((char *)a1 + 0x20));
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", jimakuDisp);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", jimakuManager);

void jimakuUndisp(void *a0) {
    void *volatile q = a0;
    int *p = *(int **)((char *)q + 0x15C);
    *(int *)((char *)p + 0x624) = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", func_00173D00);

extern void ACTLookTargetSystem_Exec(void);
void func_00173D48(void *a0) {
    void *volatile q = a0;
    ACTLookTargetSystem_Exec();
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", func_00173D68);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", func_00173DB0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", func_00173F48);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", func_00173FA8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", func_001741B0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", func_001743B8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", func_00174580);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", func_00174650);

extern int D_00286810[];
extern void iosMsgSend(void *a0, void *a1, int a2);

void func_00174698(void *a0) {
    *(int *)a0 = 0;
    iosMsgSend(D_00286810, a0, 1);
}

extern int D_00271268[];

void func_001746B8(int *a0) {
    if (D_00271268[0]) {
        a0[0] = 1;
        iosMsgSend(D_00286810, a0, 0);
    }
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_C;  /* 0x0C */
    unsigned int       f_10;  /* 0x10 */
} S_006A5900;  /* stride 0x18 */

/* end struct shapes */
