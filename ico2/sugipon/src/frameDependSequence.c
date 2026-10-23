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

static inline int execSE(int no);
static inline int checkWaterDepth(struct GObj *gobj, int depth);
static inline int checkModelDataID(struct GObj *gobj, int id);
static inline int execVib(int no);
static inline int execWeaponLightOff(int no);
extern GsysObjInfo seDef[];
/* int (int, unsigned int, int, int) here, int (int, int, int, int) in s_init.h */
extern int soundSeDefPlay(int se, unsigned int owner, int pos, int playMode);

typedef struct FDSFlags { /* field names derived */
    int vibDone[1];       /* 0x00 */
    int effDone[5];       /* 0x04 */
    int seDone[12];       /* 0x18 */
    int weaponDone;       /* 0x48 */
} FDSFlags;               /* derived name */

/* the sequence being run: its flag block, work, layout record and motion
   record, its owner, the SE volume rate and the SE group */
static FDSFlags *fdsFlags = 0; /* derived name */

static void *fdsWork = 0; /* derived name */

static struct MotCtrl *fdsLayout = 0; /* derived name */

static const MotionDef *fdsRecord = 0; /* derived name */

/* the sequence's owner object, held as a char pointer; the file's uses
   convert it */
static char *fdsGObj = 0; /* derived name */

static float fdsVolume = 1.0f; /* derived name */

static int fdsGroup = 0; /* derived name */

/* int (int, unsigned int, int, int, float) here, int (int, int, int, int) in s_init.h */
extern int soundSeDefPlayWithVolumeRate(int se, unsigned int owner, int pos, int playMode,
                                        float rate);
/* seMail has no header; declared as ico2/fumi/src/seMail.c defines it */
extern void seMail(int self, int id);

static int playSE(int no)
{
    if (no == 0) {
        return 1;
    }
    if (((GObj *)fdsGObj)->drawMask != 0) {
        int ret;

        if (fdsVolume > 0.95f) {
            ret = soundSeDefPlay(no, fdsGroup, GOBJ_SUB(fdsGObj)->nodeMtx + 0x30, 1);
        } else {
            ret = soundSeDefPlayWithVolumeRate(no, fdsGroup, GOBJ_SUB(fdsGObj)->nodeMtx + 0x30, 1,
                                               fdsVolume);
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
    return 1;
}

/* .sbss and .bss: the debug tally playSERandomID prints, the number of
   picks so far and how many times each entry was picked. */
static int seRandomPicks; /* derived name */

static int seRandomPickCount[50]; /* derived name */

static int playSERandomID(int no)
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
        float w;

        if (randomSEKind[no + i].rate < 0.0f) {
            w = share;
        } else {
            w = randomSEKind[no + i].rate;
        }
        acc += w * 0.01f;
        if (rnd < acc) {
            /* the draw trace for the random SE 0x1000D */
            if (debug_seslotdisp_flag != 0 && no + 0x10000 == 0x1000D) {
                int j;

                seRandomPickCount[i]++;
                seRandomPicks++;
                /* EUC-JP: "call %d: " */
                debug_StdPrintfDummy("%d回目: ", seRandomPicks);
                for (j = 0; j < n; j++) {
                    debug_StdPrintfDummy(
                        "%s%d(%1.1f%%)\033[m ", j == i ? "\033[36m" : "", seRandomPickCount[j],
                        (float)seRandomPickCount[j] * 100.0f / (float)seRandomPicks);
                }
                debug_StdPrintfDummy("\n");
            }
            return execSE(randomSEKind[no + i].se);
        }
    }
    return execSE(randomSEKind[no].se);
}

static inline int checkWaterDepth(GObj *gobj, int depth)
{
    return (int)GOBJ_SUB(gobj)->ctrl.waterDepth < depth;
}

static inline int checkModelDataID(GObj *gobj, int id)
{
    return GOBJ_SUB(gobj)->modelId == id;
}

static int playSEConditionID(int no)
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
    }
    if (motSECondKind[no].kind != -1) {
        p = &motSECondKind[no];
        do {
            if (p->cond == -1 || fn((GObj *)fdsGObj, p->cond) != 0) {
                if (execSE(p->se) != 0) {
                    return 1;
                }
            }
            p++;
        } while (p->kind != -1);
    }
    return 0;
}

static inline int execSE(int no)
{
    if (no <= 0xFFFF) {
        return playSE(no);
    } else if (no <= 0x1FFFF) {
        return playSERandomID(no - 0x10000);
    } else {
        return playSEConditionID(no - 0x20000);
    }
    /* the bad-ID report, switched off */
    if (0) {
        /* EUC-JP: "an SE with a strange ID(%d) was called" */
        debug_StdPrintfDummy("おかしなID(%d)のSEがコールされました\n", no);
    }
}

static void playEff(int no)
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
    CopyVector(pos, (float *)(MatrixDrive_GetMatrix()[3]));
    RotQuaternionY(q, motionEffKind[no].ry * -32768.0f / 180.0f);
    RotQuaternionX(q, motionEffKind[no].rx * -32768.0f / 180.0f);
    RotQuaternionZ(q, motionEffKind[no].rz * -32768.0f / 180.0f);
    p = &motionEffKind[no];
    flags = p->flags;
    if ((flags >> 1) & 1) {
        pos[1] = GOBJ_SUB(fdsGObj)->ctrl.waterY;
    }
    if (flags & 1) {
        EntryStageMultiBgaManager(motionEffKind[no].eff, pos, q);
    } else {
        SetParticleEffect(motionEffKind[no].eff, pos, q);
    }
}

static int execEff(int no)
{
    int (*fn)(GObj *, int);
    const VibCondEntry *p;
    int idx;
    int j;
    int eff;
    int k;
    int n;

    if (no <= 0xFFFF) {
        if (no == 19) {
            goto done;
        }
        playEff(no);
        goto done;
    }
    if (no <= 0x1FFFF) {
        idx = no - 0x10000;
        k = idx + 1;
        n = 0;
        if (randomEffKind[idx] != 19) {
            do {
                n++;
            } while (randomEffKind[k++] != 19);
        }
        execEff(randomEffKind[idx + (int)(((float)n - 1e-05f) * crt_random_unit())]);
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
    eff = 19;
call:
    execEff(eff);
done:
    return 1;
}

static inline int execVib(int no)
{
    iosPadActRequest(boyPad, no);
    return 1;
}

/* a frame slot's handler: it is passed the slot's number, which it does not read */
static inline int execWeaponLightOff(int no)
{
    Sub15C *p;
    GObj *q;
    p = GOBJ_SUB(fdsGObj);
    q = p->ctrl.pickedWeapon;
    if (q != 0) {
        if (CheckWeaponKind(q) == 1) {
            Sub15C *r = GOBJ_SUB(fdsGObj);
            LightTorchOffOfWeapon(r->ctrl.pickedWeapon);
        }
    }
    return 1;
}

/* declared here: motionOrientManager.h reaches ico2/fumi's files through
   typedef.h, and commonact.c declares the table char [] */
extern const MotionDef motionKind[];

static inline void fireFDSSlot(float t, int (*fn)(int no), int no, int *done) /* derived name */
{
    if (t < 0.0f) {
        return;
    }
    if (t < fdsLayout->animFrame) {
        fn(no);
        *done = 1;
    }
}

static inline void fireSESlots(void) /* derived name */
{
    int i;

    for (i = 0; i < 12; i++) {
        if (fdsFlags->seDone[i] == 0) {
            fireFDSSlot(fdsRecord->se[i].t, execSE, fdsRecord->se[i].no, &fdsFlags->seDone[i]);
        }
    }
}

static inline void fireVibSlots(void) /* derived name */
{
    int i;

    for (i = 0; i < 1; i++) {
        if (fdsFlags->vibDone[i] == 0) {
            fireFDSSlot(fdsRecord->vib[i].t, execVib, fdsRecord->vib[i].no, &fdsFlags->vibDone[i]);
        }
    }
}

static inline void fireEffSlots(void) /* derived name */
{
    int i;

    for (i = 0; i < 5; i++) {
        if (fdsFlags->effDone[i] == 0) {
            fireFDSSlot(fdsRecord->eff[i].t, execEff, fdsRecord->eff[i].no, &fdsFlags->effDone[i]);
        }
    }
}

static inline void fireWeaponSlot(void) /* derived name */
{
    if (fdsFlags->weaponDone == 0) {
        fireFDSSlot(fdsRecord->weaponFrame, execWeaponLightOff, 0, &fdsFlags->weaponDone);
    }
}

inline void InitFrameDependSequence(void *flags)
{
    static FDSFlags clear = {{0}}; /* derived name */

    *(FDSFlags *)flags = clear;
}

void ExecFrameDependSequence(GObj *gobj)
{
    fdsGObj = (char *)gobj;
    fdsLayout = &GOBJ_SUB(gobj)->ctrl;
    fdsWork = &GOBJ_SUB(gobj)->root;
    fdsFlags = (FDSFlags *)GOBJ_SUB(gobj)->fdsFlags;
    fdsRecord = &motionKind[fdsLayout->motion];
    fdsVolume = 1.0f;

    fireSESlots();
    fireVibSlots();
    fireEffSlots();
    if (GOBJ_SUB(gobj)->ctrl.pickedWeapon != 0) {
        fireWeaponSlot();
    }
}

static inline int *findSEPackage(int no, int id) /* derived name */
{
    while (progSELink[no].id != -1 && progSELink[no].id != id) {
        no++;
    }
    if (debug_seslotdisp_flag != 0) {
        debug_StdPrintfDummy("\033[36mRequested by program... \033[m");
    }
    return progSELink[no].se;
}

static inline int setSEEnvironment(GObj *gobj, int id) /* derived name */
{
    char *w;
    char *p;
    int no;

    /* the display object, read as a char pointer like fdsGObj */
    w = *(char **)((char *)gobj + 0x15C);
    fdsGObj = (char *)gobj;
    if (w != 0) {
        no = *(int *)(w + 0x84);
        p = w + 0x460;
        fdsWork = w + 0xA0;
        fdsFlags = (FDSFlags *)(w + 0x730);
        fdsRecord = &motionKind[*(int *)(p + 0x30)];
        fdsGroup = *(int *)(w + (id << 2) + 0x60C);
        fdsLayout = (struct MotCtrl *)p;
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

static void executeSEPackageByGObj(GObj *gobj, int no, int grp)
{
    int id;
    int *p;
    int i;

    id = setSEEnvironment(gobj, grp);
    p = findSEPackage(no, id);
    for (i = 0; i < 2; i++) {
        execSE(p[i]);
    }
}

static void executeSEPackageWithNoGObj(int no)
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

void ExecuteSEPackageWithGroupVariation(GObj *gobj, int id, int grp)
{
    fdsVolume = 1.0f;
    if (gobj != 0) {
        executeSEPackageByGObj(gobj, id, grp);
    } else {
        executeSEPackageWithNoGObj(id);
    }
}

void ExecuteSEPackage(GObj *gobj, int id)
{
    ExecuteSEPackageWithGroupVariation(gobj, id, 0);
}

void ExecuteSEPackageWithVolumeRate(GObj *gobj, int id, float rate)
{
    fdsVolume = rate;
    executeSEPackageByGObj(gobj, id, 0);
}

/* as in s_init.h, which this file does not include */
extern void soundSeGroupStop(int arg);

void StopSEPackageWithGroupVariation(GObj *gobj, int grp)
{
    soundSeGroupStop(GOBJ_SUB(gobj)->ctrl.seGroup[grp]);
}

void StopSEPackage(GObj *gobj)
{
    StopSEPackageWithGroupVariation(gobj, 0);
}
