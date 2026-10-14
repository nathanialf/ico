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
#include "include_asm.h"

static int execSE(int no, void *entry);
static int checkWaterDepth(struct GObj *gobj, int depth);
static int checkModelDataID(struct GObj *gobj, int id);
static int checkWeaponType(struct GObj *gobj, int kind);
static int execVib(int no, void *entry);
static int execWeaponLightOff(int no, void *entry);
extern GsysObjInfo seDef[];
/* int (int, unsigned int, int, int) here, int (int, int, int, int) in s_init.h */
extern int soundSeDefPlay(int se, unsigned int owner, int pos, int playMode);

typedef struct FDSFlags { /* field names derived */
    int vibDone[2];       /* 0x00 */
    int effDone[12];      /* 0x08 */
    int seDone[12];       /* 0x38 */
    int weaponDone;       /* 0x68 */
    int vibEntry[2];      /* 0x6C */
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
static int playSE(int no);

INCLUDE_ASM(playSE);

static int playSERandomID(int no, void *entry);

INCLUDE_ASM(playSERandomID);

static int playSEConditionID(int no, void *entry);

INCLUDE_ASM(playSEConditionID);

INCLUDE_ASM(playEff);

INCLUDE_ASM(execEff);

static void execVibCondition(int no, int *entry);
/* declared here: motionOrientManager.h reaches ico2/fumi's files through
   typedef.h, and commonact.c declares the table char [] */
extern const MotionDef motionKind[];

static inline void fireFDSSlot(float t, int no, void *entry, int *done,
                               int (*fn)(int no, void *entry)) /* derived name */
{
    if (t < 0.0f) {
        return;
    }
    if (t < fdsLayout->animFrame) {
        fn(no, entry);
        *done = 1;
    }
}

INCLUDE_ASM(ExecFrameDependSequence);

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
        p = w + 0x470;
        fdsWork = w + 0xA0;
        fdsFlags = (FDSFlags *)(w + 0x740);
        fdsRecord = &motionKind[*(int *)(p + 0x30)];
        fdsGroup = *(int *)(w + (id << 2) + 0x61C);
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

static void executeSEPackageByGObj(GObj *gobj, int no, int grp);

INCLUDE_ASM(executeSEPackageByGObj);

static void executeSEPackageWithNoGObj(int no);

INCLUDE_ASM(executeSEPackageWithNoGObj);

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
void StopSEPackageWithGroupVariation(GObj *gobj, int grp);

INCLUDE_ASM(StopSEPackageWithGroupVariation);

void StopSEPackage(GObj *gobj)
{
    StopSEPackageWithGroupVariation(gobj, 0);
}

INCLUDE_ASM(InitFrameDependSequence);

/* a frame slot's handler: it is passed the slot's number and entry, which it does not read */

INCLUDE_ASM(execSE);

INCLUDE_ASM(checkWaterDepth);

INCLUDE_ASM(checkModelDataID);

INCLUDE_ASM(execVib);

INCLUDE_ASM(execWeaponLightOff);
