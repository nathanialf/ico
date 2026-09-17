#include "common.h"
#include "sugiCommon.h"
#include "debug.h"
#include "pad.h"
#include "particleEffect.h"
#include "stageMultiBgaManager.h"
#include "weapon.h"
#include "geometryManager.h"
#include "typedef.h"
#include "matrixDrive.h"

typedef struct {
    int se[2];
    int id;
} SePackage;

extern SePackage D_005339C0[];
extern GsysObjInfo D_005D6DB0[];
extern int D_0063B14C;
extern char D_0061F878[];
extern char D_0061F798[];
/* kept local: the declaration in s_init.h changes this TU codegen */
extern int soundSeDefPlay(int se, unsigned int a1, int a2, int a3);
extern char *D_0063B8AC;
extern void *D_0063B8A4;
extern float D_0063B8B0;
extern int D_0063B8B4;
extern char D_0061F740[];
extern char D_0061F770[];
extern int soundSeDefPlayWithVolumeRate(int se, unsigned int a1, int a2, int a3, float rate);
/* kept local: seMail has no header; this matches its definition in
 * ico2/fumi/src/seMail.c, one prototype per symbol. */
extern void seMail(int self, int id);

int playSE(int no)
{
    int ret;

    if (no != 0) {
        if (((GObj *)D_0063B8AC)->f50 != 0) {
            if (D_0063B8A4 != 0 && ((int *)D_0063B8A4)[0x1E8 / 4] != 0) {
                debug_StdPrintfDummy(D_0061F740, D_0063B8AC);
                return 1;
            }

            if (D_0063B8B0 > 0.95f) {
                ret = soundSeDefPlay(no, D_0063B8B4, GOBJ_SUB(D_0063B8AC)->f_C + 0x30, 1);
            } else {
                ret = soundSeDefPlayWithVolumeRate(no, D_0063B8B4, GOBJ_SUB(D_0063B8AC)->f_C + 0x30,
                                                   1, D_0063B8B0);
            }

            seMail((int)D_0063B8AC, no);
            if (ret == -2) {
                if (D_0063B14C != 0) {
                    debug_StdPrintfDummy(D_0061F770, &D_005D6DB0[no]);
                }
                return 0;
            }
            if (ret < 0) {
                return 1;
            }
            if (D_0063B14C != 0) {
                debug_StdPrintfDummy(D_0061F798, &D_005D6DB0[no], D_0063B8B4);
            }
        }
    }
    return 1;
}

typedef struct { /* 0x08 */
    int se;      /* 0x00 */
    float rate;  /* 0x04 */
} SERandEntry;

extern SERandEntry D_00627910[];
/* kept local: the declaration in frameDependSequence.h changes this TU codegen */
extern int execSE(int a0, void *a1);

int playSERandomID(int no, void *entry)
{
    float rest;
    float rnd;
    float share;
    float acc;
    int nshare;
    int n;
    int i;

    rest = 100.0f;
    nshare = 0;
    for (n = 0; n < D_00627910[no + n].se; n++) {
        if (D_00627910[no + n].rate < 0.0f) {
            nshare++;
        } else {
            rest -= D_00627910[no + n].rate;
        }
    }
    rnd = crt_random_unit() * 0.99999f;
    acc = 0.0f;
    share = 0.0f;
    if (acc <= rest && nshare != 0) {
        share = rest < acc ? acc : rest / (float)nshare;
    }
    for (i = 0; i < n; i++) {
        float w = D_00627910[no + i].rate;
        if (w < 0.0f) {
            w = share;
        }
        acc += w * 0.01f;
        if (rnd < acc) {
            return execSE(D_00627910[no + i].se, entry);
        }
    }
    return execSE(D_00627910[no].se, entry);
}

typedef struct SECondEntry { /* 0x0C */
    int kind;                /* 0x00 */
    int cond;                /* 0x04 */
    int se;                  /* 0x08 */
} SECondEntry;

extern SECondEntry D_00626F28[];
/* kept local: this TU's uses of CheckFloorAttribute do not fit the prototype in motionManager2.h */
extern int CheckFloorAttribute(void *self, int id);
/* kept local: this TU's uses of CheckWallAttribute do not fit the prototype in motionManager2.h */
extern int CheckWallAttribute(void *self, int id);
/* Declared before the three predicates: gcc 2.9 emits deferred inline bodies
   in first-declaration order, and the ROM has execSE before them. */
/* kept local: the declaration in frameDependSequence.h changes this TU codegen */
extern int checkWaterDepth(void *a0, int a1);
/* kept local: the declaration in frameDependSequence.h changes this TU codegen */
extern int checkModelDataID(void *a0, int a1);
/* kept local: the declaration in frameDependSequence.h changes this TU codegen */
extern int checkWeaponType(void *a0, int a1);

int playSEConditionID(int no, void *entry)
{
    int (*fn)(void *, int);
    SECondEntry *p;

    switch (D_00626F28[no].kind) {
    case 0:
    default:
        fn = CheckFloorAttribute;
        break;
    case 1:
        fn = CheckWallAttribute;
        break;
    case 2:
        fn = checkWaterDepth;
        break;
    case 3:
        fn = checkModelDataID;
        break;
    case 4:
        fn = checkWeaponType;
        break;
    }
    if (D_00626F28[no].kind != -1) {
        p = &D_00626F28[no];
        do {
            if (p->cond == -1 || fn(D_0063B8AC, p->cond) != 0) {
                if (execSE(p->se, entry) != 0) {
                    return 1;
                }
            }
            p++;
        } while (p->kind != -1);
    }
    return 0;
}

typedef struct EffEntry { /* 0x24 */
    float x;              /* 0x00 */
    float y;              /* 0x04 */
    float z;              /* 0x08 */
    float rx;             /* 0x0C */
    float ry;             /* 0x10 */
    float rz;             /* 0x14 */
    int eff;              /* 0x18 */
    int node;             /* 0x1C */
    unsigned int flags;   /* 0x20 */
} EffEntry;

extern EffEntry D_00626278[];
extern int stage_no;
extern char D_0061F810[];
/* kept local: this TU's uses of GetSkeltonFocusNode do not fit the prototype in motionManager2.h */
extern int GetSkeltonFocusNode(void *gobj, int node);
/* kept local: this TU's uses of RotQuaternionX do not fit the prototype in quaternion.h */
extern void RotQuaternionX(float *q, short a);
/* kept local: this TU's uses of RotQuaternionY do not fit the prototype in quaternion.h */
extern void RotQuaternionY(float *q, short a);
/* kept local: this TU's uses of RotQuaternionZ do not fit the prototype in quaternion.h */
extern void RotQuaternionZ(float *q, short a);

void playEff(int no)
{
    float q[4];
    float pos[4];
    EffEntry *p;
    int node;
    unsigned int flags;

    if (D_00626278[no].node == -1) {
        GetRootQuaternion(q, D_0063B8AC);
        GetRootMatrix(MatrixDrive_GetMatrix(), D_0063B8AC);
    } else {
        node = GetSkeltonFocusNode(D_0063B8AC, D_00626278[no].node);
        if (no == -1) {
            GetRootQuaternion(q, D_0063B8AC);
            GetRootMatrix(MatrixDrive_GetMatrix(), D_0063B8AC);
            debug_StdPrintfDummy(D_0061F810);
        } else {
            GetRootQuaternion(q, D_0063B8AC);
            CopyMatrix(MatrixDrive_GetMatrix(),
                       *(char **)((char *)GOBJ_SUB(D_0063B8AC) + 0xC) + (node << 6));
        }
    }
    MatrixDrive_TransMatrix(-D_00626278[no].x, -D_00626278[no].y, -D_00626278[no].z);
    CopyVector(pos, (float *)(MatrixDrive_GetMatrix() + 0x30));
    RotQuaternionY(q, D_00626278[no].ry * -32768.0f / 180.0f);
    RotQuaternionX(q, D_00626278[no].rx * -32768.0f / 180.0f);
    RotQuaternionZ(q, D_00626278[no].rz * -32768.0f / 180.0f);
    /* The record pointer is taken here, and gcc shares its `addu` with the
     * position read above: ROM keeps that one address in $16 across the six
     * calls and reads the flag word off it. */
    p = &D_00626278[no];
    flags = p->flags;
    if ((flags >> 1) & 1) {
        pos[1] = GOBJ_SUB(D_0063B8AC)->f_640;
    }
    if (flags & 1) {
        EntryStageMultiBgaManager(D_00626278[no].eff, pos, q);
    } else {
        if (stage_no == 0x21 && pos[0] < -4500.0f) {
            return;
        }
        SetParticleEffect(D_00626278[no].eff, pos, q);
    }
}

/* The shared condition table: execEff reads its `cond`/`actId` pair as an
 * effect id, execVibCondition reads `actId` as a pad actuator id. */
typedef struct VibCondEntry { /* 0x0C */
    int kind;                 /* 0x00 */
    int cond;                 /* 0x04 */
    int actId;                /* 0x08 */
} VibCondEntry;

extern VibCondEntry D_00626010[];
extern int D_00626600[];

int execEff(int no, void *entry)
{
    int (*fn)(void *, int);
    VibCondEntry *p;
    int idx;
    int j;
    int eff;
    int k;
    int n;

    if (no <= 0xFFFF) {
        if (no == 0x18) {
            goto done;
        }
        if (no == 0) {
            goto done;
        }
        playEff(no);
        goto done;
    }
    if (no <= 0x1FFFF) {
        idx = no - 0x10000;
        k = idx + 1;
        n = 0;
        if (D_00626600[idx] != 0x18) {
            do {
                n++;
            } while (D_00626600[k++] != 0x18);
        }
        execEff(D_00626600[idx + (int)(((float)n - 1e-05f) * crt_random_unit())], entry);
        goto done;
    }
    j = no - 0x20000;
    switch (D_00626010[j].kind) {
    case 0:
    default:
        fn = CheckFloorAttribute;
        break;
    case 2:
        fn = checkWaterDepth;
        break;
    }
    if (D_00626010[j].kind != -1) {
        p = &D_00626010[j];
        do {
            if (p->cond == -1 || fn(D_0063B8AC, p->cond) != 0) {
                eff = p->actId;
                goto call;
            }
            p++;
        } while (p->kind != -1);
    }
    eff = 0x18;
call:
    execEff(eff, entry);
done:
    return 1;
}

extern void *D_00639EA0;
extern int D_00639EB0;
extern char D_0061F858[];
extern void *D_0063B89C;
/* kept local: the declaration in frameDependSequence.h changes this TU codegen */
extern void StopFDSVibration(void *a0);

void execVibCondition(int no, int *entry)
{
    if (D_00639EA0 != 0) {
        debug_StdPrintfDummy(D_0061F858);
        if (D_00626010[no].kind != 0) {
            if (D_0063B89C != 0) {
                StopFDSVibration(D_0063B89C);
            }
        } else {
            *entry = iosPadActRequest(D_00639EB0, D_00626010[no].actId);
        }
    }
}

typedef struct FDSSlot { /* 0x08 */
    float t;             /* 0x00 */
    int no;              /* 0x04 */
} FDSSlot;

typedef struct FDSRecord { /* 0x194 */
    FDSSlot eff[12];       /* 0x000 */
    FDSSlot se[12];        /* 0x060 */
    char _C0[0x30];        /* 0x0C0 */
    FDSSlot vib[2];        /* 0x0F0 */
    char _100[0x38];       /* 0x100 */
    FDSSlot weapon;        /* 0x138 */
} FDSRecord;

typedef struct FDSFlags { /* 0x74 */
    int vibDone[2];       /* 0x00 */
    int effDone[12];      /* 0x08 */
    int seDone[12];       /* 0x38 */
    int weaponDone;       /* 0x68 */
    int vibEntry[2];      /* 0x6C */
} FDSFlags;

extern char D_0055FE58[];
extern void *D_0063B8A0;
extern void *D_0063B8A8;
/* kept local: the declaration in frameDependSequence.h changes this TU codegen */
extern int execVib(int a0, void *a1);
/* kept local: the declaration in frameDependSequence.h changes this TU codegen */
extern int execWeaponLightOff(void);

/* static helper the listing places at frameDependSequence.c lines 414-421; never
 * emitted out of line, so it has no MAIN.MAP symbol and this name is ours. */
static inline void fireFDSSlot(float t, int no, void *entry, int *done, int (*fn)())
{
    if (t < 0.0f) {
        return;
    }
    if (t < *(float *)((char *)D_0063B8A4 + 0x3C)) {
        fn(no, entry);
        *done = 1;
    }
}

void ExecFrameDependSequence(void *gobj)
{
    char *w;
    char *p;
    int i;

    w = (char *)GOBJ_SUB(gobj);
    p = w + 0x470;
    D_0063B8AC = gobj;
    D_0063B8A4 = p;
    D_0063B8A0 = w + 0xA0;
    D_0063B89C = w + 0x740;
    D_0063B8A8 = D_0055FE58 + *(int *)(p + 0x30) * 0x194;
    D_0063B8B0 = 1.0f;

    for (i = 0; i < 12; i++) {
        if (((FDSFlags *)D_0063B89C)->seDone[i] == 0) {
            fireFDSSlot(((FDSRecord *)D_0063B8A8)->se[i].t, ((FDSRecord *)D_0063B8A8)->se[i].no, 0,
                        &((FDSFlags *)D_0063B89C)->seDone[i], execSE);
        }
    }
    for (i = 0; i < 2; i++) {
        if (((FDSFlags *)D_0063B89C)->vibDone[i] == 0) {
            fireFDSSlot(((FDSRecord *)D_0063B8A8)->vib[i].t, ((FDSRecord *)D_0063B8A8)->vib[i].no,
                        &((FDSFlags *)D_0063B89C)->vibEntry[i],
                        &((FDSFlags *)D_0063B89C)->vibDone[i], execVib);
        }
    }
    if (CheckFloorAttribute(D_0063B8AC, 0x40000) == 0) {
        for (i = 0; i < 12; i++) {
            if (((FDSFlags *)D_0063B89C)->effDone[i] == 0) {
                fireFDSSlot(((FDSRecord *)D_0063B8A8)->eff[i].t,
                            ((FDSRecord *)D_0063B8A8)->eff[i].no, 0,
                            &((FDSFlags *)D_0063B89C)->effDone[i], execEff);
            }
        }
    }
    if (GOBJ_SUB(gobj)->f_630 != 0) {
        if (((FDSFlags *)D_0063B89C)->weaponDone == 0) {
            fireFDSSlot(((FDSRecord *)D_0063B8A8)->weapon.t, 0, 0,
                        &((FDSFlags *)D_0063B89C)->weaponDone, execWeaponLightOff);
        }
    }
}

/* static helper the listing places at frameDependSequence.c lines 533-542; never
 * emitted out of line, so it has no MAIN.MAP symbol and this name is ours. */
static inline int *findSEPackage(int no, int id)
{
    while (D_005339C0[no].id != -1 && D_005339C0[no].id != id) {
        no++;
    }
    if (D_0063B14C != 0) {
        debug_StdPrintfDummy(D_0061F878);
    }
    return D_005339C0[no].se;
}

/* kept local: the declaration in frameDependSequence.h changes this TU codegen */
extern int playSE(int no);
/* kept local: the declaration in frameDependSequence.h changes this TU codegen */
extern int playSERandomID(int no, void *entry);

inline int execSE(int a0, void *a1)
{
    if (a0 <= 0xFFFF) {
        return playSE(a0);
    } else if (a0 <= 0x1FFFF) {
        return playSERandomID(a0 - 0x10000, a1);
    } else {
        return playSEConditionID(a0 - 0x20000, a1);
    }
}

/* static helper the listing places at frameDependSequence.c lines 549-564; never
 * emitted out of line, so it has no MAIN.MAP symbol and this name is ours. */
static inline int setSEEnvironment(void *gobj, int id)
{
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

void executeSEPackageByGObj(void *gobj, int no, int grp)
{
    int id;
    int *p;
    int i;

    id = setSEEnvironment(gobj, grp);
    p = findSEPackage(no, id);
    for (i = 0; i < 2; i++) {
        execSE(p[i], 0);
    }
}

void executeSEPackageWithNoGObj(int no)
{
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

/* kept local: the declaration in frameDependSequence.h changes this TU codegen */
extern void executeSEPackageWithNoGObj(int a0);

void ExecuteSEPackageWithGroupVariation(void *a0, int a1, int a2)
{
    D_0063B8B0 = 1.0f;
    if (a0 != 0) {
        executeSEPackageByGObj(a0, a1, a2);
    } else {
        executeSEPackageWithNoGObj(a1);
    }
}

/* kept local: the declaration in frameDependSequence.h changes this TU codegen */
extern void ExecuteSEPackageWithGroupVariation(void *a0, int a1, int a2);

void ExecuteSEPackage(int a0, int a1)
{
    ExecuteSEPackageWithGroupVariation(a0, a1, 0);
}

/* kept local: the declaration in frameDependSequence.h changes this TU codegen */
extern void executeSEPackageByGObj();

void ExecuteSEPackageWithVolumeRate(int a0, int a1, float f)
{
    D_0063B8B0 = f;
    executeSEPackageByGObj(a0, a1, 0);
}

/* kept local: this TU's uses of soundSeGroupStop do not fit the prototype in s_init.h */
extern void soundSeGroupStop(int a0);

void StopSEPackageWithGroupVariation(int a0, int a1)
{
    int *p = (int *)GOBJ_SUB(a0);
    p += a1;
    soundSeGroupStop(p[0x187]);
}

void StopSEPackage(int a0)
{
    StopSEPackageWithGroupVariation(a0, 0);
}

void InitFrameDependSequence(void *a0)
{
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

int ExecuteDirectSEWithGroupVariation(void *gobj, int id, int grp)
{
    setSEEnvironment(gobj, id);
    return execSE(id, 0);
}

int ExecuteDirectSE(void *gobj, int id)
{
    setSEEnvironment(gobj, id);
    return execSE(id, 0);
}

void StopFDSVibration(void *a0)
{
    int *p = (int *)((char *)a0 + 0x6C);
    int i;

    for (i = 0; i < 2; i++) {
        if (p[i] != -1) {
            iosPadActStop(p[i]);
            p[i] = -1;
        }
    }
}

inline int checkWaterDepth(void *a0, int a1)
{
    int *p = (int *)GOBJ_SUB(a0);
    return (int)(*(float *)((char *)p + 0x644)) < a1;
}

inline int checkModelDataID(void *a0, int a1)
{
    int *p = (int *)GOBJ_SUB(a0);
    return p[0x21] == a1;
}

inline int checkWeaponType(void *a0, int a1)
{
    int *p = (int *)GOBJ_SUB(a0);
    char *w = (char *)p[0x630 / 4];
    if (w != 0 && CheckWeaponKind(w) == a1) {
        return 1;
    }
    return 0;
}

extern int D_00639EAC;

inline int execVib(int a0, void *a1)
{
    if (a0 <= 0xFFFF) {
        if (a0 > 0) {
            iosPadActRequest(D_00639EAC, a0);
        }
    } else if (a0 > 0x1FFFF) {
        execVibCondition(a0 - 0x20000, a1);
    }
    return 1;
}

inline int execWeaponLightOff(void)
{
    int *p;
    int *q;
    p = (int *)((int *)D_0063B8AC)[0x15C / 4];
    q = (int *)p[0x630 / 4];
    if (q != 0) {
        if (CheckWeaponKind(q) == 1) {
            int *r = (int *)((int *)D_0063B8AC)[0x15C / 4];
            LightTorchOffOfWeapon((int *)r[0x630 / 4]);
        }
    }
    return 1;
}
