#include "common.h"

extern int D_0062C118;

void InitCharFileManager(void) {
    D_0062C118 = 0;
}

void ResetCharFileManager(void) {
}

typedef struct { long long a, b, c; } __attribute__((packed)) Blk24;
extern Blk24 D_006DE110[];
extern Blk24 D_004AE2D0;
extern int D_0062AB60;
extern void func_001887D8(void);
extern void chain_simulate_term_loop(void);

void ReadModelFile(void) {
    int j;
    D_0062AB60 = 0;
    for (j = 0; j < 1576; j++) {
        D_006DE110[j] = D_004AE2D0;
    }
    func_001887D8();
    chain_simulate_term_loop();
}

typedef struct { int _0, _4, _8, _C, _10, f14; } Entry;

void ReadVolumeModelFile(void) {
    Entry *e = (Entry *)D_006DE110;
    int j;
    D_0062AB60 = 0;
    for (j = 0; j < 1576; j++) {
        if (e[j].f14 == 1) {
            *(Blk24 *)&e[j] = D_004AE2D0;
        }
    }
    func_001887D8();
    chain_simulate_term_loop();
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/charFileManager", ReadShadowModelFile);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/charFileManager", ReadTextureFile);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/charFileManager", ReadSkeltonFile);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/charFileManager", ReadCollisionFile);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/charFileManager", ReadStageAnimationFile);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/charFileManager", ReadMotionFile);

extern int D_00271240[];
extern void malloc_GetPartition(int a0);
extern int freeseki(char *q);
extern void iosCdvdLoad(int *self, int p, char *q);
extern void func_001AAD00(char *a0, int a1);
extern void __assert(char *a0, int a1, char *a2);
extern void debug_StdPrintfDummy();
extern void stage_PlayBgAnimationDissolve(int a1, int p);
extern char D_0060B4E0[];
extern char D_0060B888[];
extern char D_0062C9F0[];

void ReadParticleEffectFile(int *self, int a1, char *q, int a3, int a4, int a5, int flag) {
    int p;

    D_00271240[8]++;
    if (q == 0) {
        return;
    }
    if (flag == 0) {
        malloc_GetPartition(0);
        func_001AAD00(D_0060B4E0, 0x1DA);
        __assert(D_0060B4E0, 0x1DA, D_0062C9F0);
    } else {
        malloc_GetPartition(1);
    }
    p = freeseki(q);
    iosCdvdLoad(self, p, q);
    debug_StdPrintfDummy(D_0060B888, a3, a1, q);
    stage_PlayBgAnimationDissolve(a1, p);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/charFileManager", ReadSoundBdFile);

extern int D_00271240[];
extern int iosFree(int a0, char *q, const char *src, int code);
extern void iosCdvdLoad(int *self, int p, char *q);
extern void iosMallocCheckLeak2(int p);
extern char D_0060B4E0[];
extern int D_0062A310;
extern void InitParticleEffects(int a0, int p, char *q);

void ReadSoundHdFile(int *self, int unused, char *q, int a3) {
    int p = iosFree(D_0062A310, q, D_0060B4E0, 0x21B);
    D_00271240[8]++;
    iosCdvdLoad(self, p, q);
    InitParticleEffects(a3, p, q);
    iosMallocCheckLeak2(p);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/charFileManager", ReadShockFile);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/charFileManager", ReadCamerasetFile);

extern int iosFree(int a0, char *q, const char *src, int code);
extern void ShockRequestBox_DecodeRequest(int s1, int data);
extern char D_0060BA60[];
extern int D_0062A338;
extern int D_0062A494;
extern int D_0062A498;

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/charFileManager", ReadEndCheckFile);


extern int D_0062A328;
extern int D_00271240[];
extern int iosFree(int a0, char *q, const char *src, int code);
extern void iosCdvdLoad(int *self, int p, char *q);
extern void iosMallocCheckLeak2(int p);
extern char D_0060B4E0[];
extern char D_0060BA90[];
extern char D_0062C9F0[];
extern void debug_StdPrintfDummy();
extern void func_001AAD00(char *a0, int a1);
extern void __assert(char *a0, int a1, char *a2);
extern void func_00188728(void *a0, int a1);

void ReadStageSettingFile(int *a0, int a1, char *a2, void *a3) {
    int p = iosFree(D_0062A328, a2, D_0060B4E0, 0x327);
    if (p == 0) {
        debug_StdPrintfDummy(D_0060BA90);
        func_001AAD00(D_0060B4E0, 0x32C);
        __assert(D_0060B4E0, 0x32C, D_0062C9F0);
    }
    D_00271240[8]++;
    iosCdvdLoad(a0, p, a2);
    func_00188728(a3, p);
    iosMallocCheckLeak2(p);
}

extern int D_0062A328;
extern int D_00271240[];
extern int iosFree(int a0, char *q, const char *src, int code);
extern void iosCdvdLoad(int *self, int p, char *q);
extern void iosMallocCheckLeak2(int p);

extern char D_0060B4E0[];

void CSVSYSTEM_ReadCharFiles(int *self, int unused, char *q)
{
    int p = iosFree(D_0062A328, q, D_0060B4E0, 0x349);
    D_00271240[8]++;
    iosCdvdLoad(self, p, q);
    iosMallocCheckLeak2(p);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/charFileManager", ReadSoundSqFile);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/charFileManager", ReadSoundAdpcmFile);

extern int D_00271240[];
extern int iosFree(int a0, char *q, const char *src, int code);
extern void iosCdvdLoad(int *self, int p, char *q);
extern void func_001AAD00(char *a0, int a1);
extern void __assert(char *a0, int a1, char *a2);
extern void debug_StdPrintfDummy();
extern char *soundSeDefPlay(int a0, int a1, int a2, int a3, int a4);
extern char D_0060B4E0[];
extern char D_0060BA00[];
extern char D_0062C9F0[];
extern int D_0062A31C;
extern int D_0062A330;
extern int D_0062A52C;

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/charFileManager", GetPObjAddress);


extern int D_00271240[];
extern char D_0060B4E0[];
extern char D_0060BA30[];
extern int D_0062A31C;
extern int iosFree(int a0, char *q, const char *src, int code);
extern void iosCdvdLoad(int *self, int p, char *q);
extern void iosMallocCheckLeak2(int p);
extern char *soundDataAreaGet(int *a0);
extern int AdpcmUseAreaGet(void);
extern int *AdpcmOpen(int a0, int a1, int a2, int a3, int a4, int a5, int a6);
extern void AdpcmClose(void *a0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/charFileManager", func_001A01B8);



/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_14;  /* 0x14 */
} S_006DE110;  /* stride 0x18 */

/* end struct shapes */
