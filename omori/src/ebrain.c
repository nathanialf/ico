#include "common.h"

/* eBrain 0x7F0 view (local) */
typedef struct { char _0[0x74]; int f_74; char _pad78[0x50]; float f_C8; char f_CC; unsigned char f_CD; } EGeo;

extern float *ContinueCorrectPosition(void *a0);

void eBrainProcess(void *a0, float *a1) {
    a1[0] = ContinueCorrectPosition(a0)[0];
    a1[1] = ContinueCorrectPosition(a0)[1];
    a1[2] = ContinueCorrectPosition(a0)[2];
    a1[1] -= 50.0f;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/ebrain", eBrainGetTargetGeneratorFromLabel);

void eBrainGetTarget(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    EGeo *q = *(EGeo **)((char *)p + 0x7F0);
    q->f_CC = 1;
}

void eBrainInit(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    EGeo *q = *(EGeo **)((char *)p + 0x7F0);
    q->f_CC = 0;
}

float eBrainStatusSet(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    EGeo *q = *(EGeo **)((char *)p + 0x7F0);
    return q->f_C8;
}

float eBrainSendMes(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    EGeo *q = *(EGeo **)((char *)p + 0x7F0);
    return (float)(q->f_74 - 1) * 50.0f;
}

void GetStageFromLabel(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    EGeo *q = *(EGeo **)((char *)p + 0x7F0);
    q->f_CD = 1;
}

void eBrainGetTargetGeneratorFromLabelStage(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    EGeo *q = *(EGeo **)((char *)p + 0x7F0);
    q->f_CD = 0;
}

int func_0018DFA8(void *a0) {
    void *p = *(void **)((char *)a0 + 0x15C);
    EGeo *q = *(EGeo **)((char *)p + 0x7F0);
    return q->f_CD;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/ebrain", func_0018DFB8);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/ebrain", func_0018E0E0);

extern void _OrientXZGV(char *elem, char *base, int a2, float a, float b);

void func_0018E2B8(char *base, int n, int a2)
{
    char *p;
    int i = 0;
    if (n < 0) {
        return;
    }
    p = base;
    do {
        _OrientXZGV(p, base, a2, (float)i, (float)(n - i));
        i++;
        p += 0x20;
    } while (i <= n);
}

extern float HandyCamera_TargetMoveType(void *a0, void *a1);
extern float D_0062C8C8_a[] __asm__("D_0062C8C8");

int func_0018E348(float *out, int a1, void *a2) {
    int geo = *(int *)(*(int *)(a1 + 0x15C) + 0x7F0);
    float best = D_0062C8C8_a[0];
    int ret = 0;
    int i;

    for (i = 2; i <= *(int *)(geo + 0x74) - 1; i++) {
        int off = i << 5;
        float v = HandyCamera_TargetMoveType(a2, (void *)(*(int *)(geo + 0xD0) + off));
        if (v < best) {
            float *elem = (float *)(off + *(int *)(geo + 0xD0));
            best = v;
            ret = 1;
            out[0] = elem[0];
            out[1] = elem[1];
            out[2] = elem[2];
        }
    }
    return ret;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/ebrain", func_0018E430);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/ebrain", func_0018E670);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/ebrain", func_0018E830);

extern int D_0062AA50;
extern int D_0062AA4C;
extern int D_0062C09C;
extern int D_0062C0A0;
extern int D_006C9FF0[];

void func_0018F1A8(void)
{
    int *p = D_006C9FF0;
    int i;
    D_0062AA50 = 0;
    D_0062AA4C = 0;
    D_0062C09C = 0;
    p = (int *)((char *)p + 0x37C);
    D_0062C0A0 = 0;
    i = 0x1F;
    do {
        *p = 0;
        p = (int *)((char *)p - 0x1C);
        i--;
    } while (i >= 0);
}

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
