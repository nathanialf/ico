#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/ebrain", eBrainProcess);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/ebrain", eBrainGetTargetGeneratorFromLabel);

void eBrainGetTarget(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    *((char *)q + 0xCC) = 1;
}

void eBrainInit(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    *((char *)q + 0xCC) = 0;
}

float eBrainStatusSet(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    return *(float *)((char *)q + 0xC8);
}

float eBrainSendMes(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    return (float)(q[0x1D] - 1) * 50.0f;
}

void GetStageFromLabel(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    *((char *)q + 0xCD) = 1;
}

void eBrainGetTargetGeneratorFromLabelStage(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    *((char *)q + 0xCD) = 0;
}

int func_0018DFA8(void *a0) {
    void *p = *(void **)((char *)a0 + 0x15C);
    void *q = *(void **)((char *)p + 0x7F0);
    return *(unsigned char *)((char *)q + 0xCD);
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/ebrain", func_0018DFB8);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/ebrain", func_0018E0E0);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/ebrain", func_0018E2B8);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/ebrain", func_0018E348);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/ebrain", func_0018E430);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/ebrain", func_0018E670);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/ebrain", func_0018E830);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/ebrain", func_0018F1A8);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/ebrain", func_0018F1F0);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/ebrain", func_0018F2A0);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/ebrain", func_0018F3A0);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/ebrain", func_0018F470);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/ebrain", func_0018F580);

extern int D_0062C0A4;
extern int D_0062C0A8;
extern int D_0062C0AC;

int func_0018F608(void) {
    D_0062C0A4 = 0;
    D_0062C0A8 = -1;
    D_0062C0AC = 0;
    return 0;
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_006CA370;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_006CA3F0;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00555000;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00555020;  /* stride 0x4 */

/* end struct shapes */
