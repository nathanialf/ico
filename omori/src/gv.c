#include "common.h"

/* gv 0x7F0 view (local; 0x8/0x50 also read as ushort in _InterRotGV) */
typedef struct { char _0[8]; int f_8; } GVGeo;

typedef struct { char _0[0x42]; short f42; unsigned short f44; unsigned int f48; } GVGeo2;
extern GVGeo2 D_002A0A90[];

int RestoreGeneratorGeo(void *a0, void *a1) {
    *(float *)a0 = *(float *)((char *)a1 + 0x10);
    *(float *)((char *)a0 + 4) = *(float *)((char *)a1 + 0x14);
    *(float *)((char *)a0 + 8) = *(float *)((char *)a1 + 0x18);
    return 1;
}

extern int iosOmSendMail(void *a0, int a1, void *a2);

int GetMatrixDirectionToZ(void *a0, void *a1) {
    void *p = *(void **)((char *)a0 + 0x15C);
    void *q = *(void **)((char *)p + 0x7F0);
    int h = *(short *)((char *)a1 + 0x30);
    *(int *)((char *)q + 0x50) = h;
    *(int *)((char *)q + 0x8) = *(short *)((char *)a1 + 0x32);
    if (h == 1) {
        *(int *)((char *)q + 0x54) = 2;
        iosOmSendMail(a0, 1, a0);
    }
    return 1;
}

int _InterRotGV(void *a0, void *a1) {
    int *p = *(int **)((char *)a1 + 0x15C);
    unsigned short *q = *(unsigned short **)((char *)p + 0x7F0);
    *(unsigned short *)a0 = *(unsigned short *)((char *)q + 0x50);
    *(unsigned short *)((char *)a0 + 2) = *(unsigned short *)((char *)q + 0x8);
    return 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/gv", _DistxzSqGV);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/gv", DirectCallEnemy);

extern void debug_StdPrintfDummy(char *a0, int a1);
extern char D_005550A8[];

void _DistGV(void *a0) {
    void *p = *(void **)((char *)a0 + 0x164);
    debug_StdPrintfDummy(D_005550A8, *(int *)((char *)a0 + 0x8));
    *(unsigned long *)((char *)p + 0x18) |= (unsigned long)0x8000 << 19;
}

extern char D_005550B8[];

typedef union { unsigned long ll; unsigned int i; } GVBits;

void UnlockEnemyGenerate(void *a0) {
    void *p = *(void **)((char *)a0 + 0x164);
    GVGeo2 *g = &D_002A0A90[*(int *)((char *)a0 + 0x8)];
    debug_StdPrintfDummy(D_005550B8, *(int *)((char *)a0 + 0x8));
    ((GVBits *)((char *)p + 0x18))->ll &= ~((unsigned long)0x8000 << 19);
    g->f48 = (g->f48 | 0x200000) & 0xFFFBFFFF;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/gv", _MoveGV);

void ReturnEnemyToGenerator(int a0) {
    GVGeo2 *g = &D_002A0A90[a0];
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

int _AbsRotyGV(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    GVGeo *q = *(GVGeo **)((char *)p + 0x7F0);
    return q->f_8 == 0;
}

extern void *isysGObjSearchFromObjLayoutID(int a0);
extern void *isysGObjSearchFromObjKindID_next(void *a0);

int _ApplyRyGV(void) {
    void *g = isysGObjSearchFromObjLayoutID(0x21);
    while (g != 0) {
        void *p = *(void **)((char *)g + 0x15C);
        void *q = *(void **)((char *)p + 0x7F0);
        if (*(int *)((char *)g + 0x16C) != 0) {
            if (*(int *)((char *)q + 0x50) == 1) {
                return 1;
            }
        }
        g = isysGObjSearchFromObjKindID_next(g);
    }
    return 0;
}

void SetInfoSpKidnapGenerator(short *a0) {
    a0[0] = 1;
    a0[1] = 1;
}

typedef struct { char _[0x48]; int f48; } GVState;
extern GVState D_002E0064;

void _RotGV(void) {
    D_002E0064.f48 = (D_002E0064.f48 | 0x200000) & 0xFFFBFFFF;
}

int IsEnableCallEnemyByTargetGObj(void *a0) {
    GVGeo2 *g = &D_002A0A90[*(int *)((char *)a0 + 0x8)];
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

extern void assertMsg1(char *a0) __asm__("debug_StdPrintfDummy");
extern char D_0062C900[];
extern void sceVu0InterVector(void *a0, void *a1, void *a2, float a3);

void _InterGV(void *a0, void *a1, void *a2, float a3, float a4) {
    if (a0 == 0 || a1 == 0 || a2 == 0) {
        assertMsg1(D_0062C900);
    }
    sceVu0InterVector(a0, a1, a2, a4 / (a3 + a4));
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/gv", _OrientGV);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/gv", _FrontGV);
