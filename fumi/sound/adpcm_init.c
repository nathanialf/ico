#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/adpcm_init", AdpcmStreamInit);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/adpcm_init", adpcmTickProc2);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/adpcm_init", adpcmDataSet);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/adpcm_init", AdpcmPlay);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/adpcm_init", AdpcmStop);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/adpcm_init", AdpcmOpen);

extern void debug_assertMessage(void *a0);
extern char D_00613878[];
extern void func_0025A280(long long a0);

void AdpcmClose(void *a0) {
    debug_assertMessage(D_00613878);
    func_0025A280(*(long long *)((char *)a0 + 0x30));
}

extern void func_0025A2E0(long long a0);

void AdpcmInterStereoVolumeSet(int a0) {
    func_0025A2E0(*(long long *)(a0 + 0x30));
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/adpcm_init", AdpcmInterLeaveVolumeSet);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/adpcm_init", AdpcmVolumeSet);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/adpcm_init", adpcmPauseRequest);

extern void adpcmPauseRequest(void *a0, int a1, int a2);

void AdpcmIopBuffAlloc(int a0, int a1, int a2) {
    char *b = *(char **)(a0 + 0x2C);
    short *q = (short *)(b + (a1 * 2 + 1) * 2);
    short *r = (short *)(b + a1 * 4);
    q[0x20] = a2;
    r[0x1E] = a2;
    adpcmPauseRequest(b, a1 * 2, a2);
}

void AdpcmOpenSync(int a0, int a1) {
    AdpcmIopBuffAlloc(a0, 0, a1);
}

extern int D_0062C278;

void AdpcmFadeCloseAll(int a0) {
    D_0062C278 = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/adpcm_init", AdpcmUseAreaGet);

extern void iosCdvdBackGroundMgrEntryNum(int x);
extern int *AdpcmOpen(int a0, int a1, int a2, int a3, int a4, int a5, int a6);
extern void huft_build(int a, int b);

extern char D_006138A0[];

extern char D_006138B0[];

int *AdpcmFreeAreaGet(int *self)
{
    int *r;
    debug_assertMessage((int *)D_006138A0);
    if (self[5] != 0) goto body;
    return 0;
body:
    if (((int *)self[5])[0x40] != 0) {
        return (int *)-1;
    }
    debug_assertMessage((int *)D_006138B0);
    iosCdvdBackGroundMgrEntryNum(self[5]);
    r = AdpcmOpen(0, self[1], 0x11, self[2], 0, self[3], self[4]);
    huft_build(((int *)r[11])[10], 0x5C000);
    return r;
}

typedef struct { int f0; char pad[0x40]; short f44; char pad2[0x12]; } AdpcmVolEntry;
extern AdpcmVolEntry D_0070A8C0[];

void AdpcmInterStereoVolumeSetAll(short a0) {
    int i;
    for (i = 0; i < 2; i++) {
        if (D_0070A8C0[i].f0 != 0) {
            D_0070A8C0[i].f44 = a0;
        }
    }
}

extern int D_0062C270[2];

int AdpcmInterLeaveVolumeGet(void) {
    int count = 0;
    int *p = D_0062C270;
    int i = 1;
    do {
        if (*p) {
            count++;
        }
        p++;
    } while (--i >= 0);
    return count;
}

int AdpcmVolumeGet(void) {
    int count = 0;
    int *p = D_0062C270;
    int i = 1;
    do {
        if (!*p) {
            count++;
        }
        p++;
    } while (--i >= 0);
    return count;
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_30;  /* 0x30 */
    unsigned int       f_34;  /* 0x34 */
    unsigned int       f_38;  /* 0x38 */
    unsigned int       f_3C;  /* 0x3C */
} S_006151D8;

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0070A970;  /* stride 0x4 */

/* end struct shapes */
