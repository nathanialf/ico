#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/adpcm_init", AdpcmStreamInit);

typedef struct { char p[0x34]; void *f34; void *f38; char p2[4]; unsigned char f40; char p3[3]; int f44; } AdpT;
extern void func_001F8C30(void *a0);
extern AdpT *D_0062A4D8;
void adpcmTickProc2(AdpT *a0, AdpT *a1) {
    func_001F8C30(a0);
    a0->f40 = a1->f40;
    a0->f38 = a1;
    a0->f34 = a1->f34;
    a1->f34 = a0;
    a0->f44 = a1->f44;
    if (a0->f34 == 0) {
        D_0062A4D8 = a0;
    }
}

extern int D_0062A4D4;

void adpcmDataSet(char *a0, char *a1) {
    int next;
    func_001F8C30(a0);
    *(unsigned char *)(a0 + 0x40) = *(unsigned char *)(a1 + 0x40);
    next = *(int *)(a1 + 0x38);
    *(int *)(a0 + 0x34) = (int)a1;
    *(int *)(a0 + 0x38) = next;
    *(int *)(a1 + 0x38) = (int)a0;
    *(int *)(a0 + 0x44) = *(int *)(a1 + 0x44);
    if (*(int *)(a0 + 0x38) == 0) {
        D_0062A4D4 = (int)a0;
    }
}

extern int func_00259E68(int);
extern void func_0025A080(void);
extern int new_mblock_node(int, void *, int);
extern void debug_assertMessage();
extern int D_0070A970[];
extern char D_00613820[];
extern char D_00613838[];
extern int D_0062C268;
extern int D_0062C274;
extern char D_0070A8C0_b[] __asm__("D_0070A8C0");

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/adpcm_init", AdpcmPlay);


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/adpcm_init", AdpcmStop);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/adpcm_init", AdpcmOpen);

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

extern int D_0062C270[2];
extern char *soundDataAreaGet(int *key);
extern int iosCdvdChgFileName();
extern char D_006151D8[];
extern char D_00613888[], D_00613858[], D_0062D9B0[];
extern void CheckWallAttributeEdegWall();
extern void func_001FA070();

typedef struct {
    char _0[4];
    int unk4, unk8, unkC, unk10, unk14;
} AdpcmIL;

void AdpcmInterLeaveVolumeSet(AdpcmIL *a0, int a1, int a2, int a3) {
    int key;
    char *r;
    int i;
    int result;

    debug_assertMessage(D_00613888);
    key = (a1 & 0xFFFF) | 0x110000;
    r = soundDataAreaGet(&key);
    if (r != 0) {
        a0->unk14 = 0;
        return;
    }
    a0->unk8 = a2;
    a0->unk4 = a1;
    i = 0;
    do {
        if (D_0062C270[i] == 0) goto found;
        i++;
    } while (i < 2);
    debug_assertMessage(D_00613858);
    result = 0;
    goto check;
found:
    D_0062C270[i] = 1;
    result = D_0062C268 + i * 0x5C000;
check:
    a0->unkC = result;
    if (result != 0) {
        a0->unk14 = iosCdvdChgFileName(&D_006151D8[a1 * 0x40], CheckWallAttributeEdegWall, a0, func_001FA070, 0, a0, 0, 0);
    } else {
        a0->unk14 = 0;
        debug_assertMessage(D_0062D9B0, &D_006151D8[a1 * 0x40]);
    }
    a0->unk10 = a3;
}


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
