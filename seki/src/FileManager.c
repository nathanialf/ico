#include "common.h"

extern void shadow_RenderVolumeMulti(void *a0);

void file_Init(void *a0) {
    shadow_RenderVolumeMulti(a0);
}

void file_LoadCDFile(void *a0) {
    shadow_RenderVolumeMulti(a0);
}

void file_LoadFile(int a0) {
    file_LoadCDFile(*(void **)(a0 + 0x15C));
}

void func_0010F040(int a0) {
    file_LoadFile(a0);
}

void func_0010F048(int a0) {
    file_Init(*(void **)(a0 + 0x15C));
}

void func_0010F050(int a0) {
    func_0010F048(a0);
}

extern int D_0062BA6C;
extern int D_00272584[];
extern void sceDmaSend(int a0, int a1);

void p2o_TransMicroProgram(void) {
    sceDmaSend(D_0062BA6C, D_00272584[0]);
}

void func_0010F068(void) {
}

extern void debug_StdPrintfDummy(const char *fmt, ...);
extern char D_0054E260[], D_0054E290[], D_0054E2A8[], D_0054E2C0[], D_0054E2D8[];
extern char D_0054E2F0[], D_0054E308[], D_0054E320[], D_0054E338[], D_0054E350[], D_0054E368[];
extern char D_0062BD08[];
extern int D_0062A260;
extern int sceSifRebootIop(void *a0);
extern int sceSifSyncIop(void);
extern int sceSifLoadModule(void *a0, int a1, int a2);
extern void sceSifInitRpc(int a0);
extern void sceCdInit(int a0);
extern void sceCdMmode(int a0);
extern void sceSifLoadFileReset(void);
extern void sceFsReset(void);

void func_0010F070(void) {
    debug_StdPrintfDummy(D_0054E260);
    debug_StdPrintfDummy(D_0054E290);
    sceSifInitRpc(0);
    sceCdInit(0);
    sceCdMmode(D_0062A260);
    debug_StdPrintfDummy(D_0062BD08);
    debug_StdPrintfDummy(D_0054E2A8);
    do { } while (sceSifRebootIop(D_0054E2C0) == 0);
    do { } while (sceSifSyncIop() == 0);
    sceSifInitRpc(0);
    sceSifLoadFileReset();
    sceFsReset();
    sceCdInit(0);
    sceCdMmode(D_0062A260);
    debug_StdPrintfDummy(D_0062BD08);
    debug_StdPrintfDummy(D_0054E2D8);
    do { } while (sceSifLoadModule(D_0054E2F0, 0, 0) < 0);
    do { } while (sceSifLoadModule(D_0054E308, 0, 0) < 0);
    do { } while (sceSifLoadModule(D_0054E320, 0, 0) < 0);
    do { } while (sceSifLoadModule(D_0054E338, 0, 0) < 0);
    do { } while (sceSifLoadModule(D_0054E350, 0, 0) < 0);
    do { } while (sceSifLoadModule(D_0054E368, 0, 0) < 0);
    debug_StdPrintfDummy(D_0062BD08);
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/FileManager", func_0010F220);

extern int func_0010F220(void);

int func_0010F958(void) {
    return func_0010F220();
}

typedef struct {
    /* 0x00 */ int f_0;
    /* 0x04 */ int f_4;
    /* 0x08 */ unsigned int f_8;
    /* 0x0C */ unsigned int base;
    /* 0x10 */ unsigned int cur;
    /* 0x14 */ unsigned int tag;
    /* 0x18 */ unsigned int start;
    /* 0x1C */ unsigned int gif;
} FMGifBuf;
extern FMGifBuf D_004C3850;

void func_0010F978(void) {
    typedef union { unsigned int i; unsigned long long ll; } U;
    unsigned int p;
    p = D_004C3850.cur;
    D_004C3850.start = 0;
    D_004C3850.gif = 0;
    D_004C3850.cur = p + 8;
    D_004C3850.base = p;
    D_004C3850.tag = p;
    ((U *)(p + 8))->i = 0x11000000;
    D_004C3850.start = p + 0xC;
    D_004C3850.gif = p + 0x10;
    D_004C3850.cur = p + 0x18;
    ((U *)(p + 0x18))->ll = 0xE;
    D_004C3850.cur = p + 0x20;
}

extern void dpk_Init(int a0, unsigned int a1, int a2);
extern int dl_GetPri(void);
extern int D_00629EA0;

void func_0010F9D0(void) {
    typedef union { unsigned int i; unsigned long long ll; } U;
    unsigned int p;

    ((U *)D_004C3850.gif)->ll =
        (unsigned int)(((D_004C3850.cur - D_004C3850.gif) >> 4) - 1) | 0x1000000000008000ULL;
    ((U *)D_004C3850.start)->i =
        ((D_004C3850.cur - D_004C3850.start) >> 4) | 0x50000000;
    ((U *)D_004C3850.tag)->ll =
        (unsigned int)((((D_004C3850.cur - D_004C3850.tag) >> 4) - 1) | 0x10000000);
    p = D_004C3850.cur;
    D_004C3850.tag = p;
    ((U *)p)->ll = 0x60000000;
    D_004C3850.cur = p + 8;
    ((U *)(p + 8))->i = 0;
    D_004C3850.cur = p + 12;
    ((U *)(p + 12))->i = 0;
    D_004C3850.cur = p + 16;
    dpk_Init(5, D_004C3850.base, 0);
    dl_GetPri();
    D_00629EA0 = 0;
}


void func_0010FAB0(void) {
    typedef union { unsigned int i; unsigned long long ll; } U;
    unsigned int p;
    p = D_004C3850.cur;
    D_004C3850.start = 0;
    D_004C3850.gif = 0;
    D_004C3850.cur = p + 8;
    D_004C3850.base = p;
    D_004C3850.tag = p;
    ((U *)(p + 8))->i = 0x11000000;
    D_004C3850.start = p + 0xC;
    D_004C3850.gif = p + 0x10;
    D_004C3850.cur = p + 0x18;
    ((U *)(p + 0x18))->ll = 0xE;
    D_004C3850.cur = p + 0x20;
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/FileManager", gif_EndPacketPath1);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/FileManager", func_0010FC20);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/FileManager", func_0010FD48);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/FileManager", gif_MakeSpriteOffset);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/FileManager", gif_MakeSpriteWithStrip);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/FileManager", gif_PointOffset);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/FileManager", gif_Line);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/FileManager", gif_Sprite);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0054E6E0;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0054E710;  /* stride 0x4 */

/* end struct shapes */
