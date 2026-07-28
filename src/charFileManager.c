#include "common.h"

typedef struct { int _0, _4, _8, _C, _10, f14; } Entry;

typedef struct { long long a, b, c; } __attribute__((packed)) Blk24;


extern int D_00633E28;
void InitCharFileManager(void) {
    D_00633E28 = 0;
}

void ResetCharFileManager(void) {}

extern Blk24 D_004B2FD0;
extern int D_00632898;
extern Blk24 D_006E4890[];
extern void chain_simulate_term_loop(void);
extern void func_0018B2F8(void);

void ReadModelFile(void) {
    int j;
    D_00632898 = 0;
    for (j = 0; j < 1582; j++) {
        D_006E4890[j] = D_004B2FD0;
    }
    func_0018B2F8();
    chain_simulate_term_loop();
}

void ReadVolumeModelFile(void) {
    Entry *e = (Entry *)D_006E4890;
    int j;
    D_00632898 = 0;
    for (j = 0; j < 1582; j++) {
        if (e[j].f14 == 1) {
            *(Blk24 *)&e[j] = D_004B2FD0;
        }
    }
    func_0018B2F8();
    chain_simulate_term_loop();
}

INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadShadowModelFile);

INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadTextureFile);

INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadSkeltonFile);

INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadCollisionFile);

INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadStageAnimationFile);

INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadMotionFile);

extern int D_00274EC0[];
extern char D_00612A70[];
extern char D_00612E18[];
extern char D_006328A8[];
extern void debug_assertMessage();
extern int freeseki(char *q);
extern void func_001AD768(char *a0, int a1);
extern void func_00263FF0(char *a0, int a1, char *a2);
extern void iosCdvdLoad(int *self, int p, char *q);
extern void malloc_GetPartition(int a0);
extern void stage_PlayBgAnimationDissolve(int a1, int p);

void ReadParticleEffectFile(int *self, int a1, char *q, int a3, int a4, int a5, int flag) {
    int p;

    D_00274EC0[8]++;
    if (q == 0) {
        return;
    }
    if (flag == 0) {
        malloc_GetPartition(0);
        func_001AD768(D_00612A70, 0x1DA);
        func_00263FF0(D_00612A70, 0x1DA, D_006328A8);
    } else {
        malloc_GetPartition(1);
    }
    p = freeseki(q);
    iosCdvdLoad(self, p, q);
    debug_assertMessage(D_00612E18, a3, a1, q);
    stage_PlayBgAnimationDissolve(a1, p);
}

INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadSoundBdFile);

extern int D_00632010;
extern void InitParticleEffects(int a0, int p, char *q);
extern int func_0013A0F8(int a0, char *q, const char *src, int code);
extern void iosMallocCheckLeak2(int p);

void ReadSoundHdFile(int *self, int unused, char *q, int a3) {
    int p = func_0013A0F8(D_00632010, q, D_00612A70, 0x21B);
    D_00274EC0[8]++;
    iosCdvdLoad(self, p, q);
    InitParticleEffects(a3, p, q);
    iosMallocCheckLeak2(p);
}

INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadShockFile);

INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadCamerasetFile);

INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadEndCheckFile);

extern char D_00613020[];
extern int D_00632028;
extern void func_0018B248(void *a0, int a1);

void ReadStageSettingFile(int *a0, int a1, char *a2, void *a3) {
    int p = func_0013A0F8(D_00632028, a2, D_00612A70, 0x327);
    if (p == 0) {
        debug_assertMessage(D_00613020);
        func_001AD768(D_00612A70, 0x32C);
        func_00263FF0(D_00612A70, 0x32C, D_006328A8);
    }
    D_00274EC0[8]++;
    iosCdvdLoad(a0, p, a2);
    func_0018B248(a3, p);
    iosMallocCheckLeak2(p);
}

void CSVSYSTEM_ReadCharFiles(int *self, int unused, char *q)
{
    int p = func_0013A0F8(D_00632028, q, D_00612A70, 0x349);
    D_00274EC0[8]++;
    iosCdvdLoad(self, p, q);
    iosMallocCheckLeak2(p);
}

INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadSoundSqFile);

INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadSoundAdpcmFile);

INCLUDE_ASM("asm/nonmatchings/src/charFileManager", GetPObjAddress);

INCLUDE_ASM("asm/nonmatchings/src/charFileManager", func_001A2C18);

/* .data — carved VMA 0x4B2FD0..0x4B2FE8 (1 symbol, Blk24), bytes verified against baserom/baseelf.rom */
Blk24 D_004B2FD0 = { 0, 0, 0x0000000100000000LL };

