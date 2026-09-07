#include "common.h"

typedef struct { int w[6]; } AssertRec;

typedef struct { int f_0; char _4[0x14]; } DbgSlot;

extern char *iosMallocDebug(int heap, int size, char *file, int line);
extern void iosFree(void *p);
extern void iosCdvdHandlerRead(void *h, void *buf, int size);
extern void SetParticleEffectPackage(int a0, void *buf, int size);
extern void debug_StdPrintfDummy(char *fmt, ...);
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);
extern void soundSQDataSet(void *buf, int a3, int kind, int mode, int a6);

INCLUDE_ASM("asm/nonmatchings/src/charFileManager", InitCharFileManager);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ResetCharFileManager);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadModelFile);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadVolumeModelFile);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadShadowModelFile);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadTextureFile);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadSkeltonFile);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadCollisionFile);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadStageAnimationFile);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadMotionFile);
extern int D_0063A438;
extern char D_006193B0[];
extern int D_0028F4C0[];
void ReadParticleEffectFile(void *h, int a1, int size, int a3) {
    char *buf = iosMallocDebug(D_0063A438, size, D_006193B0, 0x228);
    D_0028F4C0[8]++;
    iosCdvdHandlerRead(h, buf, size);
    SetParticleEffectPackage(a3, buf, size);
    iosFree(buf);
}
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadSoundBdFile);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadSoundHdFile);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadShockFile);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadCamerasetFile);
extern char D_006193B0[];
extern int D_0063A450;
extern int D_0028F4C0[];
void ReadEndCheckFile(void *h, int a1, int size) {
    char *buf = iosMallocDebug(D_0063A450, size, D_006193B0, 0x356);
    D_0028F4C0[8]++;
    iosCdvdHandlerRead(h, buf, size);
    iosFree(buf);
}
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadStageSettingFile);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", CSVSYSTEM_ReadCharFiles);
typedef struct { int mode; int bank; } SqInfo;

extern int D_0063A444;
extern int D_0063A458;
extern int D_0063A684;
extern char D_006193B0[];
extern char D_006198D0[];
extern char D_0063AD10[];
extern int D_0028F4C0[];

void ReadSoundSqFile(void *h, int a1, int size, int a3, int kind, int a5, int a6) {
    /* the sound bank/mode pair the switch fills in and soundSQDataSet reads back:
       ROM keeps both words memory-resident and reloads mode at the call. */
    volatile SqInfo info;
    char *buf;

    D_0028F4C0[8]++;
    if (size == 0) {
        return;
    }
    switch (kind) {
    case 11:
        info.mode = 0;
        info.bank = 0;
        break;
    case 10:
        info.mode = 1;
        info.bank = D_0063A684;
        break;
    default:
        debug_assert(D_006193B0, 709);
        __assert(D_006193B0, 709, D_0063AD10);
    }
    if (info.bank == 0) {
        if (a6 == 0) {
            buf = iosMallocDebug(D_0063A444, size, D_006193B0, 715);
        } else {
            buf = iosMallocDebug(D_0063A458, size, D_006193B0, 717);
        }
    } else {
        buf = 0;
    }
    iosCdvdHandlerRead(h, buf, size);
    if (buf != 0) {
        soundSQDataSet(buf, a3, kind, info.mode, a6);
    }
    debug_StdPrintfDummy(D_006198D0, a3, a1, size);
}
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadSoundAdpcmFile);
extern DbgSlot D_006FAD00[];

extern AssertRec D_006FAD00__pn[] __asm__("D_006FAD00");

int GetPObjAddress(int a0) {
    return D_006FAD00__pn[a0].w[0];
}
