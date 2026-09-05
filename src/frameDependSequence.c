#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/frameDependSequence", playSE);
INCLUDE_ASM("asm/nonmatchings/src/frameDependSequence", playSERandomID);
INCLUDE_ASM("asm/nonmatchings/src/frameDependSequence", playSEConditionID);
INCLUDE_ASM("asm/nonmatchings/src/frameDependSequence", playEff);
INCLUDE_ASM("asm/nonmatchings/src/frameDependSequence", execEff);
INCLUDE_ASM("asm/nonmatchings/src/frameDependSequence", execVibCondition);
INCLUDE_ASM("asm/nonmatchings/src/frameDependSequence", ExecFrameDependSequence);
INCLUDE_ASM("asm/nonmatchings/src/frameDependSequence", executeSEPackageByGObj);
typedef struct { int se[2]; int id; } SePackage;
typedef struct { char _0[0x20]; int f_20; char _24[0x18]; } GsysObjInfo;

extern SePackage D_005339C0[];
extern GsysObjInfo D_005D6DB0[];
extern int D_0063B14C;
extern char D_0061F878[];
extern char D_0061F798[];
extern void debug_StdPrintfDummy();
extern int soundSeDefPlay(int se, unsigned int a1, int a2, int a3);

/* static helper the listing places at frameDependSequence.c lines 533-542; never
 * emitted out of line, so it has no MAIN.MAP symbol and this name is ours. */
static inline int *findSEPackage(int no, int id) {
    while (D_005339C0[no].id != -1 && D_005339C0[no].id != id) {
        no++;
    }
    if (D_0063B14C != 0) {
        debug_StdPrintfDummy(D_0061F878);
    }
    return D_005339C0[no].se;
}

void executeSEPackageWithNoGObj(int no) {
    int *p;
    int i;

    p = findSEPackage(no, -1);
    for (i = 0; i < 2; i++) {
        if (p[i] != 0) {
            soundSeDefPlay(p[i], 0xFFFFFFFF, 0, 1);
            if (D_0063B14C != 0) {
                debug_StdPrintfDummy(D_0061F798, &D_005D6DB0[p[i]], 0xFFFFFFFF);
            }
        }
    }
}
extern float D_0063B8B0;
extern void executeSEPackageWithNoGObj(int a0);
void ExecuteSEPackageWithGroupVariation(void *a0, int a1, int a2) {
    D_0063B8B0 = 1.0f;
    if (a0 != 0) {
        executeSEPackageByGObj(a0, a1, a2);
    } else {
        executeSEPackageWithNoGObj(a1);
    }
}
extern void ExecuteSEPackageWithGroupVariation(void *a0, int a1, int a2);

void ExecuteSEPackage(int a0, int a1) {
    ExecuteSEPackageWithGroupVariation(a0, a1, 0);
}
extern float D_0063B8B0;
extern void executeSEPackageByGObj();

void ExecuteSEPackageWithVolumeRate(int a0, int a1, float f)
{
    D_0063B8B0 = f;
    executeSEPackageByGObj(a0, a1, 0);
}
extern void soundSeGroupStop(int a0);

void StopSEPackageWithGroupVariation(int a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    p += a1;
    soundSeGroupStop(p[0x187]);
}
void StopSEPackage(int a0) {
    StopSEPackageWithGroupVariation(a0, 0);
}
void InitFrameDependSequence(void *a0) {
    int *p = (int *)a0;
    int *se = (int *)((char *)a0 + 0x8);
    int *eff = (int *)((char *)a0 + 0x38);
    int *vib = (int *)((char *)a0 + 0x6C);
    int i;

    for (i = 0; i < 2; i++) {
        p[i] = 0;
    }
    for (i = 0; i < 12; i++) {
        se[i] = 0;
    }
    for (i = 0; i < 12; i++) {
        eff[i] = 0;
    }
    p[0x68 / 4] = 0;
    for (i = 0; i < 2; i++) {
        vib[i] = -1;
    }
}
extern int playSE(int no);
extern int playSEConditionID(int no, void *entry);
extern int playSERandomID(int no, void *entry);

inline int execSE(int a0, void *a1) {
    if (a0 <= 0xFFFF) {
        return playSE(a0);
    } else if (a0 <= 0x1FFFF) {
        return playSERandomID(a0 - 0x10000, a1);
    } else {
        return playSEConditionID(a0 - 0x20000, a1);
    }
}
extern char D_0055FE58[];
extern void *D_0063B89C;
extern void *D_0063B8A0;
extern void *D_0063B8A4;
extern void *D_0063B8A8;
extern char *D_0063B8AC;
extern int D_0063B8B4;

/* static helper the listing places at frameDependSequence.c lines 549-564; never
 * emitted out of line, so it has no MAIN.MAP symbol and this name is ours. */
static inline int setSEEnvironment(void *gobj, int id) {
    char *w;
    char *p;
    int no;

    w = *(char **)((char *)gobj + 0x15C);
    D_0063B8AC = gobj;
    if (w != 0) {
        no = *(int *)(w + 0x84);
        p = w + 0x470;
        D_0063B8A0 = w + 0xA0;
        D_0063B89C = w + 0x740;
        D_0063B8A8 = D_0055FE58 + *(int *)(p + 0x30) * 0x194;
        D_0063B8B4 = *(int *)(w + (id << 2) + 0x61C);
        D_0063B8A4 = p;
    } else {
        no = -1;
        D_0063B8A4 = 0;
        D_0063B8A0 = 0;
        D_0063B89C = 0;
        D_0063B8A8 = 0;
        D_0063B8B4 = no;
    }
    return no;
}

int ExecuteDirectSEWithGroupVariation(void *gobj, int id, int grp) {
    setSEEnvironment(gobj, id);
    return execSE(id, 0);
}
int ExecuteDirectSE(void *gobj, int id) {
    setSEEnvironment(gobj, id);
    return execSE(id, 0);
}
extern void iosPadActStop(int key);

void StopFDSVibration(void *a0) {
    int *p = (int *)((char *)a0 + 0x6C);
    int i;

    for (i = 0; i < 2; i++) {
        if (p[i] != -1) {
            iosPadActStop(p[i]);
            p[i] = -1;
        }
    }
}
inline int checkWaterDepth(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    return (int)(*(float *)((char *)p + 0x644)) < a1;
}
inline int checkModelDataID(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    return p[0x21] == a1;
}
extern int CheckWeaponKind(char *self);

inline int checkWeaponType(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    char *w = (char *)p[0x630 / 4];
    if (w != 0 && CheckWeaponKind(w) == a1) {
        return 1;
    }
    return 0;
}
extern int D_00639EAC;
extern void iosPadActRequest(int port, int id);
extern int execVibCondition(int id, void *entry);

inline int execVib(int a0, void *a1) {
    if (a0 <= 0xFFFF) {
        if (a0 > 0) {
            iosPadActRequest(D_00639EAC, a0);
        }
    } else if (a0 > 0x1FFFF) {
        execVibCondition(a0 - 0x20000, a1);
    }
    return 1;
}
extern int CheckWeaponKind(char *self);
extern void LightTorchOffOfWeapon(int *self);

inline int execWeaponLightOff(void)
{
    int *p;
    int *q;
    p = (int *)((int *)D_0063B8AC)[0x15C/4];
    q = (int *)p[0x630/4];
    if (q != 0) {
        if (CheckWeaponKind(q) == 1) {
            int *r = (int *)((int *)D_0063B8AC)[0x15C/4];
            LightTorchOffOfWeapon((int *)r[0x630/4]);
        }
    }
    return 1;
}
