#include "common.h"

typedef union { unsigned long ll; unsigned int i; } GVBits;
typedef struct { char _0[0x42]; short f42; unsigned short f44; unsigned char f46; char _47; unsigned int f48; } GVGeo2;
extern int D_0063A438;
extern char D_00555640[];
extern void *iosMallocDebug(int heap, int size, char *file, int line);
extern void _ApplyRyGV(void *a0, float a1);
extern int InitMultiBgaManager(int a0);
typedef struct StageLabelRange {
    char pad0[0x128];
    int labelTop;               /* 0x128 */
    int labelEnd;               /* 0x12C */
    char pad130[0x194 - 0x130];
} StageLabelRange;
extern StageLabelRange D_005F5D50[];
extern GVGeo2 D_002C2DC8[];
extern int stage_no;
extern int D_006E6D80[];
extern void iosOmSendMail(void *a0, int a1, void *a2);
extern void debug_StdPrintfDummy(char *fmt, ...);
extern int fptodp(float f);
extern void actEnemyRestart(char *gobj, float *pos, int a2, int a3, char *mother);
extern void ACTGame_SaveActorInformation(char *gobj);
extern char D_00555650[];
extern char D_00555670[];
extern char D_0063AC08[];
extern char D_00555688[];
extern char D_00555698[];
extern char D_00308924[];
/* prototypes: their order is the inline tail's emission order */
char *InitGeneratorGeo(char *gobj, char *src);
void Generator_Call(char *a0);
void Generator_ResetCount(char *a0);
void Generator_Mask(char *a0);
void Generator_MaskOff(char *a0);
void SetMotherGenerator(int no, int label);
void Generator_Init(void);
int *GetbufpGeneratorPacket(void);
int GetsizeGeneratorPacket(void);
int RestoreGeneratorGeo(float *dst, float *src);
int RestoreGeneratorExtGeo(char *a0, short *a1);
int MemoryGenerator(short *a0, char *a1);
void *IsEnableCallEnemy(char *self);
char *DirectCallEnemy(char *gobj, char *mother, float *pos, int a3, int a4);
void LockEnemyGenerate(int *self);
void UnlockEnemyGenerate(void *a0);
void RestoreReviveCount(char *gobj);
void ReturnEnemyToGenerator(int a0);
int GeneratorWorkEnd(char *a0);
int SearchActiveGenerator(void);
void ResetReviveCountEnemy(int a0);
void SetInfoSpKidnapGenerator(short *a0);
void SetInfoSpKidnapEnemy(void);
int IsOpenGenerator(char *gobj);
int IsEnableCallEnemyByTargetGObj(void *a0);
inline int SearchActiveGenerator(void)
{
    char *g;

    g = (char *)isysGObjSearchFromObjKindID_begin(0x21);
    while (g != 0) {
        char *w = *(char **)(*(char **)(g + 0x15C) + 0x830);

        if (*(int *)(g + 0x16C) != 0) {
            if (*(int *)(w + 0x50) == 1) {
                return 1;
            }
        }
        g = (char *)isysGObjSearchFromObjKindID_next(g);
    }
    return 0;
}
INCLUDE_ASM("asm/nonmatchings/src/generator", CheckGeneratorCollision);
INCLUDE_ASM("asm/nonmatchings/src/generator", GetGeneratorSafePosition);
INCLUDE_ASM("asm/nonmatchings/src/generator", switch_MainStatus);
INCLUDE_ASM("asm/nonmatchings/src/generator", endfunc_BGA);
INCLUDE_ASM("asm/nonmatchings/src/generator", IsNeedGeneratorHard);
inline int IsEnableCallEnemyByTargetGObj(void *a0) {
    GVGeo2 *g = &D_002C2DC8[*(int *)((char *)a0 + 0x8)];
    void *p = *(void **)((char *)a0 + 0x164);
    if (g->f44 != 0) {
        return 0;
    }
    if ((unsigned int)(*(unsigned long long *)((char *)p + 0x18) >> 34) & 1) {
        return 0;
    }
    if (((g->f48 >> 21) & 1) == 0 && (g->f42 == -1 || g->f42 > 0)) {
        return 1;
    }
    return 0;
}
inline void *IsEnableCallEnemy(char *self)
{
    char *g;

    for (g = (char *)isysGObjSearchFromObjKindID_begin(4); g != 0;
         g = (char *)isysGObjSearchFromObjKindID_next(g)) {
        char *p = *(char **)(g + 0x164);
        int no = *(int *)(g + 8);
        GVGeo2 *gg = &D_002C2DC8[no];

        if (self != 0 && *(int *)(self + 8) == 0xEAE && no != 0xEAD) {
            continue;
        }
        if (D_002C2DC8[no].f44 != 0 && self != 0 && D_002C2DC8[no].f44 != *(int *)(self + 8)) {
            continue;
        }
        if ((unsigned int)(*(unsigned long long *)(p + 0x18) >> 34) & 1) {
            continue;
        }
        if ((gg->f48 >> 21) & 1) {
            continue;
        }
        if (gg->f42 == -1 || gg->f42 > 0) {
            return g;
        }
    }
    return 0;
}
inline char *DirectCallEnemy(char *gobj, char *mother, float *pos, int a3, int a4)
{
    GVGeo2 *gg = &D_002C2DC8[*(int *)(gobj + 8)];

    gg->f48 = (gg->f48 | 0x200000)
            & 0xFFFBFFFF;

    debug_StdPrintfDummy(D_00555650, *(int *)(gobj + 8), mother, (mother != 0) ? *(int *)(mother + 8) : -1);
    debug_StdPrintfDummy(D_00555670, D_0063AC08, fptodp(pos[0]), fptodp(pos[1]), fptodp(pos[2]), fptodp(pos[3]));
    if (mother != 0) {
        SetMotherGenerator(*(int *)(gobj + 8), *(int *)(mother + 8));
    }
    if (gg->f42 != -1) {
        gg->f42--;
    }
    actEnemyRestart(gobj, pos, a3, a4, mother);
    ACTGame_SaveActorInformation(gobj);
    return gobj;
}
INCLUDE_ASM("asm/nonmatchings/src/generator", CallEnemy);
inline void LockEnemyGenerate(int *self)
{
    int *p;
    p = (int *)self[0x164 / 4];
    debug_StdPrintfDummy(D_00555688, self[0x8 / 4]);
    *(long long *)((char *)p + 0x18) = *(long long *)((char *)p + 0x18) | 0x400000000LL;
}
inline void UnlockEnemyGenerate(void *a0) {
    void *p = *(void **)((char *)a0 + 0x164);
    GVGeo2 *g = &D_002C2DC8[*(int *)((char *)a0 + 0x8)];
    debug_StdPrintfDummy(D_00555698, *(int *)((char *)a0 + 0x8));
    ((GVBits *)((char *)p + 0x18))->ll &= ~((unsigned long)0x8000 << 19);
    g->f48 = (g->f48 | 0x200000) & 0xFFFBFFFF;
}
inline void RestoreReviveCount(char *gobj)
{
    GVGeo2 *g = (GVGeo2 *)((char *)D_002C2DC8 + *(int *)(gobj + 8) * 0x4C);
    if (g->f42 != -1) {
        int n = (short)(g->f42 + 1);
        int lim = ((g->f48 >> 5) & 0x1F) + 1;
        n = (lim < n) ? lim : n;
        g->f42 = n;
        if (*(int *)(gobj + 8) == 0xEAD) {
            g->f42 = (g->f42 < 0) ? 0 : ((g->f42 > 1) ? 1 : g->f42);
        }
    }
}
INCLUDE_ASM("asm/nonmatchings/src/generator", Generator_QuickCall);
inline void Generator_Call(char *a0) {
    *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 8) += 1;
}
inline void Generator_ResetCount(char *a0) {
    *(char *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x12) = 1;
}
inline void Generator_Mask(char *a0) {
    *(char *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x10) = 1;
}
inline void Generator_MaskOff(char *a0) {
    *(char *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x10) = 0;
}
void Generator_Delete(void *a0) {
    switch_MainStatus(a0, 0);
}
INCLUDE_ASM("asm/nonmatchings/src/generator", GetMotherGenerator);
inline void SetMotherGenerator(int no, int label)
{
    int i;
    int cnt;

    if (no == 0xEAD) {
        return;
    }
    cnt = 0;
    for (i = D_005F5D50[stage_no].labelTop; i < D_005F5D50[stage_no].labelEnd; i++) {
        GVGeo2 *g = &D_002C2DC8[i];
        if (g->f46 == 0x21) {
            if (i == label) {
                GVGeo2 *m = &D_002C2DC8[no];
                m->f48 = ((int)m->f48 & ~0x3C00) | ((cnt & 0xF) << 10);
                return;
            }
            cnt++;
        }
    }
}
inline void Generator_Init(void)
{
    int i;

    for (i = 0; i < 3759; i++) {
        GVGeo2 *g = &D_002C2DC8[i];
        unsigned int x = g->f48 & 0xFFDFFFFF;
        unsigned int y = x & 0xFFFBFFFF;

        y |= ((x >> 19) & 1) << 18;
        g->f48 = y;
        g->f42 = (y >> 5) & 0x1F;
        if ((y >> 19) & 1) {
            unsigned int z = y | 0x40000;
            g->f48 = z;
            if ((int)((z >> 5) & 0x1F) != -1) {
                g->f42++;
            }
        }
    }
}
inline void ReturnEnemyToGenerator(int a0) {
    GVGeo2 *g = &D_002C2DC8[a0];
    unsigned int x = g->f48 & 0xFFDFFFFF;
    unsigned int y = x & 0xFFFBFFFF;
    y |= ((x >> 19) & 1) << 18;
    g->f48 = y;
    if ((y >> 19) & 1) {
        unsigned int z = y | 0x40000;
        g->f48 = z;
        if ((int)((z >> 5) & 0x1F) != -1) {
            g->f42++;
        }
    }
}
inline int *GetbufpGeneratorPacket(void) {
    return D_006E6D80;
}
inline int GetsizeGeneratorPacket(void) {
    return 11277;
}
INCLUDE_ASM("asm/nonmatchings/src/generator", ReadGeneratorPacket);
INCLUDE_ASM("asm/nonmatchings/src/generator", MakeGeneratorPacket);
inline void ResetReviveCountEnemy(int a0)
{
    int idx = *(int *)(a0 + 0x8);
    char *base = (char *)D_002C2DC8 + idx * 0x4C;
    *(short *)(base + 0x42) = 0;
}
inline void SetInfoSpKidnapEnemy(void)
{
  int new_var;
  new_var = 0x42;
  *((short *) (D_00308924 + new_var)) = 0;
  *((int *) (D_00308924 + 0x48)) = ((*((int *) (D_00308924 + 0x48))) | 0x200000) & (~0x40000);
}
inline void SetInfoSpKidnapGenerator(short *a0) {
    a0[0] = 1;
    a0[1] = 1;
}
inline int RestoreGeneratorGeo(float *dst, float *src) {
    dst[0] = src[4];
    dst[1] = src[5];
    dst[2] = src[6];
    return 1;
}
inline int RestoreGeneratorExtGeo(char *a0, short *a1) {
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    *(int *)(p + 0x50) = a1[0x18];
    *(int *)(p + 8) = a1[0x19];
    if (a1[0x18] == 1) {
        *(int *)(p + 0x54) = 2;
        iosOmSendMail(a0, 1, a0);
    }
    return 1;
}
inline int MemoryGenerator(short *a0, char *a1) {
    char *p = *(char **)(*(char **)(a1 + 0x15C) + 0x830);
    a0[0] = *(unsigned short *)(p + 0x50);
    a0[1] = *(unsigned short *)(p + 8);
    return 1;
}
INCLUDE_ASM("asm/nonmatchings/src/generator", generatorBeforeFunc);
inline char *InitGeneratorGeo(char *gobj, char *src)
{
    char *p = iosMallocDebug(D_0063A438, 0x70, D_00555640, 1230);
    int i;

    *(int *)(p + 0x0) = 0;
    *(int *)(p + 0x4) = 0;
    *(int *)(p + 0x8) = 0;
    *(char *)(p + 0x10) = 0;
    *(char *)(p + 0x12) = 0;
    *(int *)(p + 0x14) = *(int *)(src + 0x30);
    *(int *)(p + 0xC) = 0;

    *(int *)(p + 0x50) = 0;
    *(int *)(p + 0x54) = 0;
    *(int *)(p + 0x58) = -1;
    *(int *)(p + 0x5C) = -1;
    *(int *)(p + 0x60) = -1;
    *(int *)(p + 0x64) = 0;

    *(float *)(p + 0x20) = 0.0f; *(float *)(p + 0x24) = 0.0f; *(float *)(p + 0x28) = 1.0f; *(float *)(p + 0x2C) = 0.0f;
    _ApplyRyGV(p + 0x20, *(float *)(src + 0x14));

    {
        char *r = p + 0x34;
        int *q = (int *)(p + 0x30);

        for (i = 0; i < 4; i++) {
            *q = InitMultiBgaManager(1);
            *r = 0;
            q += 2;
            r += 8;
        }
    }

    return p;
}
INCLUDE_ASM("asm/nonmatchings/src/generator", GeneratorGeo);
INCLUDE_ASM("asm/nonmatchings/src/generator", GeneratorDL);
inline int GeneratorWorkEnd(char *a0) {
    return *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 8) == 0;
}
inline int IsOpenGenerator(char *gobj)
{
    char *w = *(char **)(*(char **)(gobj + 0x15C) + 0x830);
    int ret = 0;
    if (*(int *)(w + 0x50) == 1) {
        GVGeo2 *g = (GVGeo2 *)(*(int *)(gobj + 8) * sizeof(GVGeo2) + (char *)D_002C2DC8);
        ret = (((int)(g->f48 << 27) >> 27) == -2) ? 0 : *(int *)(w + 0x50);
    }
    return ret;
}
