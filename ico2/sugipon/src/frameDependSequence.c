#include "sugiCommon.h"
#include "debug.h"
#include "pad.h"
#include "particleEffect.h"
#include "stageMultiBgaManager.h"
#include "weapon.h"
#include "geometryManager.h"
#include "typedef.h"
#include "matrixDrive.h"
#include "quaternion.h"
#include "main.h"
#include "motionManager2.h"
#include "frameDependSequence.h"

extern GsysObjInfo seDef[];
/* kept local: int (int, unsigned int, int, int) here, int (int, int, int, int) in s_init.h */
extern int soundSeDefPlay(int se, unsigned int a1, int a2, int a3);

/* The TU's .sdata (MAIN.MAP names nothing in it), in ROM order: the sequence
   being run's flag block, work, layout record and motion record, its owner, the
   SE volume rate and the SE group. */
static void *fdsFlags = 0; /* derived name */

static void *fdsWork = 0; /* derived name */

static void *fdsLayout = 0; /* derived name */

static void *fdsRecord = 0; /* derived name */

/* the sequence's owner object, held as a char pointer: setSEEnvironment's
   store of it keeps its place behind the owner's display-object reads only as
   a char pointer store (a GObj pointer, a void pointer or a union all let it
   rise), so the TU's uses convert it */
static char *fdsGObj = 0; /* derived name */

static float fdsVolume = 1.0f; /* derived name */

static int fdsGroup = 0; /* derived name */

/* kept local: int (int, unsigned int, int, int, float) here, int (int, int, int, int) in s_init.h */
extern int soundSeDefPlayWithVolumeRate(int se, unsigned int a1, int a2, int a3, float rate);
/* kept local: seMail has no header; this matches its definition in
 * ico2/fumi/src/seMail.c, one prototype per symbol. */
extern void seMail(int self, int id);

int playSE(int no)
{
    int ret;

    if (no != 0) {
        if (((GObj *)fdsGObj)->drawMask != 0) {
            if (fdsLayout != 0 && ((int *)fdsLayout)[0x1E8 / 4] != 0) {
                /* EUC-JP: "gObj:(%p) has its motion SE stopped" */
                debug_StdPrintfDummy("gObj:(%p) はモーションSEが停止しています\n", fdsGObj);
                return 1;
            }

            if (fdsVolume > 0.95f) {
                ret = soundSeDefPlay(no, fdsGroup, GOBJ_SUB(fdsGObj)->nodeMtx + 0x30, 1);
            } else {
                ret = soundSeDefPlayWithVolumeRate(no, fdsGroup, GOBJ_SUB(fdsGObj)->nodeMtx + 0x30,
                                                   1, fdsVolume);
            }

            seMail((int)fdsGObj, no);
            if (ret == -2) {
                if (debug_seslotdisp_flag != 0) {
                    /* EUC-JP: "SE \"%s\" is not loaded" */
                    debug_StdPrintfDummy("SE \033[36m\"%s\"\033[m はロードされていません\n",
                                         &seDef[no]);
                }
                return 0;
            }
            if (ret < 0) {
                return 1;
            }
            if (debug_seslotdisp_flag != 0) {
                debug_StdPrintfDummy("SE \033[33m\"%s\"\033[m CALLED with GROUP:\033[33m%d\033[m\n",
                                     &seDef[no], fdsGroup);
            }
        }
    }
    return 1;
}

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
    for (n = 0; n < randomSEKind[no + n].se; n++) {
        if (randomSEKind[no + n].rate < 0.0f) {
            nshare++;
        } else {
            rest -= randomSEKind[no + n].rate;
        }
    }
    rnd = crt_random_unit() * 0.99999f;
    acc = 0.0f;
    share = 0.0f;
    if (acc <= rest && nshare != 0) {
        share = rest < acc ? acc : rest / (float)nshare;
    }
    for (i = 0; i < n; i++) {
        float w = randomSEKind[no + i].rate;
        if (w < 0.0f) {
            w = share;
        }
        acc += w * 0.01f;
        if (rnd < acc) {
            return execSE(randomSEKind[no + i].se, entry);
        }
    }
    return execSE(randomSEKind[no].se, entry);
}

int playSEConditionID(int no, void *entry)
{
    int (*fn)(GObj *, int);
    const SECondEntry *p;

    switch (motSECondKind[no].kind) {
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
    if (motSECondKind[no].kind != -1) {
        p = &motSECondKind[no];
        do {
            if (p->cond == -1 || fn((GObj *)fdsGObj, p->cond) != 0) {
                if (execSE(p->se, entry) != 0) {
                    return 1;
                }
            }
            p++;
        } while (p->kind != -1);
    }
    return 0;
}

inline int execSE(int a0, void *a1)
{
    if (a0 <= 0xFFFF) {
        return playSE(a0);
    } else if (a0 <= 0x1FFFF) {
        return playSERandomID(a0 - 0x10000, a1);
    } else {
        return playSEConditionID(a0 - 0x20000, a1);
    }
    /* Disabled in retail: the bad-ID report.  What the bytes pin: its text in
       .rodata after playSEConditionID's jump table and before playEff's
       print, with no instruction; the listing gives execSE rows 249-255 and
       its closing brace 259, and 256-258 are empty.  What they cannot: the
       condition that disabled it. */
    if (0) {
        /* EUC-JP: "an SE with a strange ID(%d) was called" */
        debug_StdPrintfDummy("おかしなID(%d)のSEがコールされました\n", a0);
    }
}

void playEff(int no)
{
    float q[4];
    float pos[4];
    const EffEntry *p;
    int node;
    unsigned int flags;

    if (motionEffKind[no].node == -1) {
        GetRootQuaternion(q, (GObj *)fdsGObj);
        GetRootMatrix(MatrixDrive_GetMatrix(), (GObj *)fdsGObj);
    } else {
        node = GetSkeltonFocusNode((GObj *)fdsGObj, motionEffKind[no].node);
        if (no == -1) {
            GetRootQuaternion(q, (GObj *)fdsGObj);
            GetRootMatrix(MatrixDrive_GetMatrix(), (GObj *)fdsGObj);
            /* EUC-JP: "note: the node of a node-specified motion effect was not found" */
            debug_StdPrintfDummy(
                "注意：ノード指定のモーションエフェクトでノードが見つかりませんでした\n");
        } else {
            GetRootQuaternion(q, (GObj *)fdsGObj);
            CopyMatrix(MatrixDrive_GetMatrix(), (char *)GOBJ_SUB(fdsGObj)->nodeMtx + (node << 6));
        }
    }
    MatrixDrive_TransMatrix(-motionEffKind[no].x, -motionEffKind[no].y, -motionEffKind[no].z);
    CopyVector(pos, (float *)(MatrixDrive_GetMatrix() + 0x30));
    RotQuaternionY(q, motionEffKind[no].ry * -32768.0f / 180.0f);
    RotQuaternionX(q, motionEffKind[no].rx * -32768.0f / 180.0f);
    RotQuaternionZ(q, motionEffKind[no].rz * -32768.0f / 180.0f);
    /* The record pointer is taken here, and gcc shares its `addu` with the
     * position read above: ROM keeps that one address in $16 across the six
     * calls and reads the flag word off it. */
    p = &motionEffKind[no];
    flags = p->flags;
    if ((flags >> 1) & 1) {
        pos[1] = GOBJ_SUB(fdsGObj)->waterY;
    }
    if (flags & 1) {
        EntryStageMultiBgaManager(motionEffKind[no].eff, pos, q);
    } else {
        if (stage_no == 0x21 && pos[0] < -4500.0f) {
            return;
        }
        SetParticleEffect(motionEffKind[no].eff, pos, q);
    }
}

int execEff(int no, void *entry)
{
    int (*fn)(GObj *, int);
    const VibCondEntry *p;
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
        if (randomEffKind[idx] != 0x18) {
            do {
                n++;
            } while (randomEffKind[k++] != 0x18);
        }
        execEff(randomEffKind[idx + (int)(((float)n - 1e-05f) * crt_random_unit())], entry);
        goto done;
    }
    j = no - 0x20000;
    switch (motEffCondKind[j].kind) {
    case 0:
    default:
        fn = CheckFloorAttribute;
        break;
    case 2:
        fn = checkWaterDepth;
        break;
    }
    if (motEffCondKind[j].kind != -1) {
        p = &motEffCondKind[j];
        do {
            if (p->cond == -1 || fn((GObj *)fdsGObj, p->cond) != 0) {
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

void execVibCondition(int no, int *entry)
{
    if (girlControlMode != 0) {
        /* EUC-JP: "controller-2 vibration condition detect mode" */
        debug_StdPrintfDummy("2コン振動条件検知モード\n");
        if (motEffCondKind[no].kind != 0) {
            if (fdsFlags != 0) {
                StopFDSVibration(fdsFlags);
            }
        } else {
            *entry = iosPadActRequest(girlPad, motEffCondKind[no].actId);
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

extern char motionKind[];

/* static helper the listing places at frameDependSequence.c lines 414-421; never
 * emitted out of line, so it has no MAIN.MAP symbol and this name is ours. */
static inline void fireFDSSlot(float t, int no, void *entry, int *done, int (*fn)())
{
    if (t < 0.0f) {
        return;
    }
    if (t < *(float *)((char *)fdsLayout + 0x3C)) {
        fn(no, entry);
        *done = 1;
    }
}

void ExecFrameDependSequence(GObj *gobj)
{
    char *w;
    char *p;
    int i;

    w = (char *)GOBJ_SUB(gobj);
    p = w + 0x470;
    fdsGObj = (char *)gobj;
    fdsLayout = p;
    fdsWork = w + 0xA0;
    fdsFlags = w + 0x740;
    fdsRecord = motionKind + *(int *)(p + 0x30) * 0x194;
    fdsVolume = 1.0f;

    for (i = 0; i < 12; i++) {
        if (((FDSFlags *)fdsFlags)->seDone[i] == 0) {
            fireFDSSlot(((FDSRecord *)fdsRecord)->se[i].t, ((FDSRecord *)fdsRecord)->se[i].no, 0,
                        &((FDSFlags *)fdsFlags)->seDone[i], execSE);
        }
    }
    for (i = 0; i < 2; i++) {
        if (((FDSFlags *)fdsFlags)->vibDone[i] == 0) {
            fireFDSSlot(((FDSRecord *)fdsRecord)->vib[i].t, ((FDSRecord *)fdsRecord)->vib[i].no,
                        &((FDSFlags *)fdsFlags)->vibEntry[i], &((FDSFlags *)fdsFlags)->vibDone[i],
                        execVib);
        }
    }
    if (CheckFloorAttribute((GObj *)fdsGObj, 0x40000) == 0) {
        for (i = 0; i < 12; i++) {
            if (((FDSFlags *)fdsFlags)->effDone[i] == 0) {
                fireFDSSlot(((FDSRecord *)fdsRecord)->eff[i].t, ((FDSRecord *)fdsRecord)->eff[i].no,
                            0, &((FDSFlags *)fdsFlags)->effDone[i], execEff);
            }
        }
    }
    if (GOBJ_SUB(gobj)->pickedWeapon != 0) {
        if (((FDSFlags *)fdsFlags)->weaponDone == 0) {
            fireFDSSlot(((FDSRecord *)fdsRecord)->weapon.t, 0, 0,
                        &((FDSFlags *)fdsFlags)->weaponDone, execWeaponLightOff);
        }
    }
}

/* static helper the listing places at frameDependSequence.c lines 533-542; never
 * emitted out of line, so it has no MAIN.MAP symbol and this name is ours. */
static inline int *findSEPackage(int no, int id)
{
    while (progSELink[no].id != -1 && progSELink[no].id != id) {
        no++;
    }
    if (debug_seslotdisp_flag != 0) {
        debug_StdPrintfDummy("\033[36mRequested by program... \033[m");
    }
    return progSELink[no].se;
}

/* static helper the listing places at frameDependSequence.c lines 549-564; never
 * emitted out of line, so it has no MAIN.MAP symbol and this name is ours. */
static inline int setSEEnvironment(GObj *gobj, int id)
{
    char *w;
    char *p;
    int no;

    w = *(char **)((char *)gobj + 0x15C);
    fdsGObj = (char *)gobj;
    if (w != 0) {
        no = *(int *)(w + 0x84);
        p = w + 0x470;
        fdsWork = w + 0xA0;
        fdsFlags = w + 0x740;
        fdsRecord = motionKind + *(int *)(p + 0x30) * 0x194;
        fdsGroup = *(int *)(w + (id << 2) + 0x61C);
        fdsLayout = p;
    } else {
        no = -1;
        fdsLayout = 0;
        fdsWork = 0;
        fdsFlags = 0;
        fdsRecord = 0;
        fdsGroup = no;
    }
    return no;
}

void executeSEPackageByGObj(GObj *gobj, int no, int grp)
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
            if (debug_seslotdisp_flag != 0) {
                debug_StdPrintfDummy("SE \033[33m\"%s\"\033[m CALLED with GROUP:\033[33m%d\033[m\n",
                                     &seDef[p[i]], 0xFFFFFFFF);
            }
        }
    }
}

void ExecuteSEPackageWithGroupVariation(GObj *a0, int a1, int a2)
{
    fdsVolume = 1.0f;
    if (a0 != 0) {
        executeSEPackageByGObj(a0, a1, a2);
    } else {
        executeSEPackageWithNoGObj(a1);
    }
}

void ExecuteSEPackage(GObj *a0, int a1)
{
    ExecuteSEPackageWithGroupVariation(a0, a1, 0);
}

void ExecuteSEPackageWithVolumeRate(GObj *a0, int a1, float f)
{
    fdsVolume = f;
    executeSEPackageByGObj(a0, a1, 0);
}

/* kept local: agrees with s_init.h, which this TU does not include (soundSeDefPlay, soundSeDefPlayWithVolumeRate differ) */
extern void soundSeGroupStop(int a0);

void StopSEPackageWithGroupVariation(GObj *a0, int a1)
{
    int *p = (int *)GOBJ_SUB(a0);
    p += a1;
    soundSeGroupStop(p[0x187]);
}

void StopSEPackage(GObj *a0)
{
    StopSEPackageWithGroupVariation(a0, 0);
}

void InitFrameDependSequence(void *a0)
{
    FDSFlags *f = a0;
    int i;

    for (i = 0; i < 2; i++) {
        f->vibDone[i] = 0;
    }
    for (i = 0; i < 12; i++) {
        f->effDone[i] = 0;
    }
    for (i = 0; i < 12; i++) {
        f->seDone[i] = 0;
    }
    f->weaponDone = 0;
    for (i = 0; i < 2; i++) {
        f->vibEntry[i] = -1;
    }
}

int ExecuteDirectSEWithGroupVariation(GObj *gobj, int id, int grp)
{
    setSEEnvironment(gobj, id);
    return execSE(id, 0);
}

int ExecuteDirectSE(GObj *gobj, int id)
{
    setSEEnvironment(gobj, id);
    return execSE(id, 0);
}

void StopFDSVibration(void *a0)
{
    int *p = ((FDSFlags *)a0)->vibEntry;
    int i;

    for (i = 0; i < 2; i++) {
        if (p[i] != -1) {
            iosPadActStop(p[i]);
            p[i] = -1;
        }
    }
}

inline int checkWaterDepth(GObj *a0, int a1)
{
    return (int)GOBJ_SUB(a0)->waterDepth < a1;
}

inline int checkModelDataID(GObj *a0, int a1)
{
    return GOBJ_SUB(a0)->modelId == a1;
}

inline int checkWeaponType(GObj *a0, int a1)
{
    GObj *w = (GObj *)GOBJ_SUB(a0)->pickedWeapon;
    if (w != 0 && CheckWeaponKind(w) == a1) {
        return 1;
    }
    return 0;
}

inline int execVib(int a0, void *a1)
{
    if (a0 <= 0xFFFF) {
        if (a0 > 0) {
            iosPadActRequest(boyPad, a0);
        }
    } else if (a0 > 0x1FFFF) {
        execVibCondition(a0 - 0x20000, a1);
    }
    return 1;
}

inline int execWeaponLightOff(void)
{
    Sub15C *p;
    GObj *q;
    p = GOBJ_SUB(fdsGObj);
    q = (GObj *)p->pickedWeapon;
    if (q != 0) {
        if (CheckWeaponKind(q) == 1) {
            Sub15C *r = GOBJ_SUB(fdsGObj);
            LightTorchOffOfWeapon((GObj *)r->pickedWeapon);
        }
    }
    return 1;
}
