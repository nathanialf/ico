#include "sugiCommon.h"
#include "backStage.h"
#include "debug.h"
#include "gamesys.h"
#include "layout_texture.h"
#include "obj_manager.h"
#include "act-way.h"
#include "enemy_act.h"
#include "way_llf.h"
#include "camera-root.h"
#include "fightSound.h"
#include "generator.h"
#include "gv.h"
#include "gflag.h"
#include "st25a.h"
#include "Primitive.h"
#include "StageAnimation.h"
#include "Texture.h"
#include "a_p_1.h"
#include "cage.h"
#include "particleEffect.h"
#include "spider.h"
#include <string.h>
#include <stdlib.h>
#include "StageManager.h"
#include "act.h"
#include "motionOrientManager.h"
#include "typedef.h"
#include "torch.h"
#include "matrixDrive.h"
#include "script.h"
#include "layout_action.h"
#include "Basic.h"
#include "GifPacket.h"

/* script.o's .sdata, in the ROM's order.  MAIN.MAP lists all but the three
   hint-voice words, which the retail build added after scpSeEnvMasterVolRate
   (the January map has sekizo_common at +8): the ADPCM handle of the girl's
   hint voice and the distance range its volume follows. */
int scpBoyControlReadDisable = 0;

float scpSeEnvMasterVolRate = 1.0f;

static char *girlHintVoice = 0; /* derived name */

static float girlHintRangeMin = 500.0f; /* derived name */

static float girlHintRangeMax = 4000.0f; /* derived name */

char *sekizo_common = 0;

char *scpDummyGObj = 0;

char *scpDummyGObj2 = 0;

int sekizo_yure = 0;

unsigned char sekizo_yure_vol = 0;

/* a 0x40-byte layout record as CreateLayoutedGObj takes it: position,
   rotation, the unit scale at 0x20 and the kind index at 0x30 */
struct DQW {
    float f0, f4, f8, fc, f10, f14;
    char _18[0x8];
    float scale[3];
    int _2C;
    int f30;
    int _34[3];
};

struct SPMD {
    int a;
    int b;
};

struct SVF {
    int a;
    int b;
};

/* the 16-byte work vector scpSekizou reuses for the motion direction and
   for the stone-statue SE position it copies out of .rodata */

/* MUST be above the TU's first call site: with the implicit `int` return the
   call SETs $2 and global-alloc picks different scratch registers. */

/* ACT+0x20 / ACT+0x18 are the 64-bit actor status words.  The dev header
   declares them as a UNION (cf. `union ActStatus` in src/st13c.c and
   src/st04a.c), not as a bare `unsigned long long`: a union-member access has
   alias set 0, so a store through it aliases every other load -- which is why
   ROM re-loads `gobj->0x164` after a status store. */

/* the wall-collision result scpWallCollision and its sibling hand back; the
   record leads script.o's .bss run, so it is defined ahead of the ADPCM table */
struct WallColPos {
    int f00, f04;
};

struct WallCol {
    struct WallColPos pos;
    int f08;
};

/* .bss, owned by script.o and reached only from this file (MAIN.MAP names no
   symbol in the run), in the ROM's run order: the wall-collision result, the
   two-slot ADPCM play-request table (2 x 0x18 bytes), and the camera target
   the script last asked for. */
static struct WallCol wallColResult;

/* the two-slot ADPCM play-request table */
typedef struct AdpcmReq {
    int kind;  /* 0x00, 0 == slot free */
    char **id; /* 0x04: the caller's handle variable */
    int unk08; /* 0x08 */
    int unk0C; /* 0x0C */
    int unk10; /* 0x10 */
    int unk14; /* 0x14 */
} AdpcmReq;

static AdpcmReq adpcmReq[2];

static float scriptCameraTarget[4];

struct S {
    int a;
    int b;
};

/* kept local: void (char *, float *) here, void (void *, float *) in motionManager2.h */
extern void SetMotionDirection(char *self, float *dir);
/* SCE VU0 library: sceVu0Normalize(dst, src) -- normalised in place here, so
   the second argument is already in $a1 and cse drops the redundant copy. */
/* kept local: agrees with libvu0.h, which this TU does not include (sceVu0AddVector, sceVu0InnerProduct differ) */
extern void sceVu0Normalize();
/* kept local: void (char *, float *, float) here, int (int, float *, float) in commonact.h */
extern void SetMotionDirectionSmooze(char *self, float *dir, float ang);

extern struct MotTblRec {
    char _000[0x186];
    short smzAngle;
    char _188[0xC];
} motionKind[];

/* kept local: char * here, GObj * in main.h */
extern char *boyGObj;
/* kept local: char * here, GObj * in main.h */
extern char *girlGObj;
/* kept local: agrees with gobj.h, which this TU does not include (isysGObjSearchFromObjKindID_begin, isysGObjSearchFromObjKindID_next differ) */
extern int isysGObjSearchFromObjLayoutID();
/* kept local: void (int) here, void (char *) in act-game.h */
extern void ACTItemForceDrop(int a0);
/* kept local: agrees with lodManager.h, which this TU does not include */
extern int SetLodLevel();
/* kept local: agrees with geometryManager.h, which this TU does not include (GetRootMatrixRotOffset, GetRootMatrixTransOffset differ) */
extern void SetRootMatrixWithTransOffset(void *a0, float x, float y, float z);
/* kept local: void (float *, float *, float *) here, void (void *, void *, void *) in libvu0.h */
extern void sceVu0SubVector(float *d, float *a, float *b);
/* kept local: float (float *, float *) here, float (void *, void *) in libvu0.h */
extern float sceVu0InnerProduct(float *a, float *b);
/* kept local: agrees with libvu0.h, which this TU does not include (sceVu0AddVector, sceVu0InnerProduct differ) */
extern void sceVu0UnitMatrix(void *m);
/* kept local: void (void *, void *) here, void (void *, char *) in geometryManager.h */
extern void GetRootPosition(void *dst, void *obj);
/* kept local: void (float *, void *) here, void (char *, char *) in geometryManager.h */
extern void GetRootMatrixTransOffset(float *dst, void *obj);
/* kept local: void (int, int) here, void (char *, int) in commonact.h */
extern void ACTSendMailCorrect(int a0, int mail);

/* .data, first in script.o's run: the colour packet prim_DispWireBox draws the
   debug trigger box with.  Declared as the whole 4-word record so gcc reaches
   it with a %hi/%lo pair rather than gp-relative (-G 8). */
static int wireBoxColor[4] = {0, 16, 32, 128};

/* .data.  MAIN.MAP line 5865/5866 names the two exported door tables at +0x10
   and +0x30 of script.o's run; the five below it are read only here.  Each is
   the usual actor mail pair: the mail the door thread answers, then the 429
   end marker act.c walks to. */
ActMail scpInterDoorUpLever1[2] = {{406, scpDoorTypeUpSwitch}, {429}};

ActMail scpInterDoorUpLever2[2] = {{407, scpDoorTypeUpSwitch}, {429}};

static ActMail doorTypeUp_mes[2] = {{430}, {429}};

static ActMail doorTypeUpSwitchDown_mes[2] = {{430}, {429}};

static ActMail doorTypeUpSwitchUp_mes[2] = {{430}, {429}};

static ActMail doorTypeUpDown_mes[2] = {{430}, {429}};

static ActMail doorTypeUpUp_mes[2] = {{430}, {429}};

struct ScpAct {
    char _000[0x18];
    ActStatus st18; /* 0x18 -- the 64-bit actor status word */
    char _020[0xB0];
    ActMail *mainMail; /* 0xD0 */
    ActMail *mail;     /* 0xD4 */
};

/* kept local: agrees with adpcm_init.h, which this TU does not include (AdpcmFadeCloseAll, AdpcmPlay differ) */
extern int AdpcmFreeAreaGet(void);
/* kept local: agrees with adpcm_init.h, which this TU does not include (AdpcmFadeCloseAll, AdpcmPlay differ) */
extern int AdpcmNotUseIopAreaFree(void);
/* kept local: void (int) here, void (short) in adpcm_init.h */
extern void AdpcmFadeCloseAll(int a0);
/* kept local: void (void *, int, int, int, int) here, void (int *, int, int, int, int) in s_init.h */
extern void soundDataOpen(void *work, int mode, int kind, int a3, int a4);
/* kept local: char * (void *) here, int * (int *) in s_init.h */
extern char *soundDataOpenSync(void *work);
/* kept local: void (int) here, void (void *) in adpcm_init.h */
extern void AdpcmPlay(int a0);
/* kept local: void (char *) here, void (int *) in s_init.h */
extern void soundDataClose(char *h);
/* kept local: void (float *, float *, float *) here, void (void *, void *, void *) in Matrix.h */
extern void _SubVector(float *dst, float *a, float *b);
/* kept local: float (float *, float *) here, float (void *, void *) in Matrix.h */
extern float _InnerProduct(float *a, float *b);
/* kept local: this TU's uses of AdpcmInterStereoVolumeSet do not fit the
   prototype in adpcm_init.h */
/* kept local: void (void *, int) here, void () in adpcm_init.h */
extern void AdpcmInterStereoVolumeSet(void *h, int a1);

/* the 0x30-byte wood-bridge table entry at woodBoxTbl: an object id, the
   trigger `kind` that selects which axis test runs, the bridge end offset the
   way group is built from, and the four axis bounds the tests read. */
struct WoodBoxEnt {
    short id;       /* 0x00 */
    char kind;      /* 0x02 */
    char _03[0x0D]; /* 0x03 */
    float ofs[4];   /* 0x10 */
    float b0;       /* 0x20 */
    float b1;       /* 0x24 */
    float b2;       /* 0x28 */
    float b3;       /* 0x2C */
};

/* kept local: void (float *, float *, float *) here, void (void *, void *, void *) in libvu0.h */
extern void sceVu0AddVector(float *dst, float *a, float *b);
/* kept local: void (int) here, int (int) in item.h */
extern void ReviveAllCarryableItemsWithNonSleepFrame(int frames);
/* kept local: int (char *, int) here, int (int, int) in pad.h */
extern int iosPadActRequest(char *g, int no);
/* kept local: void (int, int) here, int * (int, unsigned int) in pad.h */
extern void iosPadActVolumeSet(int h, int vol);
/* kept local: agrees with pad.h, which this TU does not include (iosPadActRequest, iosPadActVolumeSet differ) */
extern void iosPadActStop(int h);
/* kept local: int (int, int, void *, int) here, int (int, int, int, int) in s_init.h */
extern int soundSeDefPlay(int no, int a1, void *pos, int a3);
/* kept local: agrees with s_init.h, which this TU does not include (soundDataClose, soundDataOpen differ) */
extern void soundSeDefStop(int h);
/* kept local: char * here, int in main.h */
extern char *boyPad;
/* kept local: float * (char *) here, void * (void *) in commonact.h */
extern float *test_CURRENTROOT(char *target);
/* kept local: void (void *) here, void (int *) in motionManager2.h */
extern void ClearMotionGeometryInfo(void *a0);
/* kept local: agrees with geometryManager.h, which this TU does not include (GetRootMatrixRotOffset, GetRootMatrixTransOffset differ) */
extern void SetDirectRootPosition();
/* kept local: void (void *) here, int (void *) in fieldCollision.h */
extern void ClipWall(void *w);

/* the wall-collision result the ClipWall work area hands back at +0x80 */

typedef struct {
    float p0[4];        /* 0x00 */
    float p1[4];        /* 0x10 */
    char _020[0x50];    /* 0x20 */
    float f70;          /* 0x70 */
    char _074[0x0C];    /* 0x74 */
    struct WallCol res; /* 0x80 */
    char _08C[0x34];    /* 0x8C */
} ClipWorkScript;       /* 0xC0 */

/* kept local: void (float *, float *, float) here, void (void *, void *, float) in libvu0.h */
extern void sceVu0ScaleVector(float *dst, float *src, float scale);
/* kept local: agrees with main.h, which this TU does not include (boyGObj, boyPad differ) */
extern int stage_no;

/* the 0x28-byte stage table at exitData and the per-stage 0x194-byte link
   table at stageData: row [stage_no], entry .ent[no - 1] at +0xA0. */
struct StgEnt {
    char _00[0x24];
    int id;
}; /* 0x28 */

extern struct StgEnt exitData[];
extern StgPre stageData[];
/* kept local: agrees with boyact.h, which this TU does not include */
extern void SetBoyWeaponGObj();
/* kept local: agrees with gobj.h, which this TU does not include (isysGObjSearchFromObjKindID_next, isysGObjSearchFromObjLayoutID differ) */
extern int isysGObjSearchFromObjKindID_begin();
/* kept local: agrees with gobj.h, which this TU does not include (isysGObjSearchFromObjKindID_begin, isysGObjSearchFromObjLayoutID differ) */
extern int isysGObjSearchFromObjKindID_next();
/* kept local: int (int, int) here, int (char *, int) in motionManager2.h */
extern int GetSkeltonFocusNode(int a0, int a1);

/* .data, last in script.o's run: the wood-bridge trigger table, one row per
   bridge object, walked by object id. */
static struct WoodBoxEnt woodBoxTbl[11] = {
    {276, 6, {0}, {0.0f, -100.0f, 100.0f, 0.0f}, 1068.0f, -135.0f, 200.0f, 580.0f},
    {1710, 0, {0}, {-100.0f, -200.0f, 0.0f, 0.0f}, -1410.0f, 1000.0f, 0.0f, 0.0f},
    {1705, 6, {0}, {0.0f, -200.0f, 100.0f, 0.0f}, 807.0f, 2000.0f, 570.0f, 1027.0f},
    {1707, 6, {0}, {0.0f, -200.0f, 100.0f, 0.0f}, 807.0f, 2000.0f, 570.0f, 1027.0f},
    {363, 1, {0}, {0.0f, -200.0f, -100.0f, 0.0f}, 740.0f, -3600.0f, 0.0f, 0.0f},
    {988, 6, {0}, {0.0f, -200.0f, 100.0f, 0.0f}, -1431.0f, 105.0f, -470.0f, -259.0f},
    {865, 8, {0}, {-100.0f, -200.0f, 0.0f, 0.0f}, -350.0f, -285.0f, -450.0f, -280.0f},
    {866, 8, {0}, {-100.0f, -200.0f, 0.0f, 0.0f}, -350.0f, -285.0f, -450.0f, -280.0f},
    {1773, 7, {0}, {-100.0f, -200.0f, 0.0f, 0.0f}, 0.0f, 0.0f, 0.0f, 0.0f},
    {1626, 1, {0}, {100.0f, -200.0f, 0.0f, 0.0f}, 680.0f, 230.0f, 0.0f, 0.0f},
    {3294, 9, {0}, {-100.0f, -200.0f, 0.0f, 0.0f}, 0.0f, 0.0f, 0.0f, 0.0f},
};

/* kept local: agrees with item.h, which this TU does not include (BreakItemFromOutside, ReviveAllCarryableItemsWithNonSleepFrame differ) */
extern int IsBombExplode(char *self);
/* kept local: float (int) here, float (char *) in rotObject.h */
extern float GetRotObjectRotCount(int a0);
/* kept local: int (int) here, int (void *) in rotObject.h */
extern int GetRotObjectZPlusDirection(int a0);
/* kept local: void (float *, void *) here, void (void *, int) in geometryManager.h */
extern void GetRootMatrixRotOffset(float *q, void *obj);
/* kept local: void (void *, float *) here, void (int, void *) in geometryManager.h */
extern void SetRootMatrixRotOffset(void *obj, float *q);
/* kept local: void (float *, int) here, void (void *, int) in quaternion.h */
extern void RotQuaternionX(float *q, int step);
/* kept local: void (float *, int) here, void (void *, int) in quaternion.h */
extern void RotQuaternionY(float *q, int step);
/* kept local: void (float *, int) here, void (void *, int) in quaternion.h */
extern void RotQuaternionZ(float *q, int step);
/* kept local: agrees with act-game.h, which this TU does not include (ACTGame_StageChangeGObjDirect, ACTGame_isHangChain differ) */
extern float _ACTGame_GetParamF(int idx);
/* kept local: agrees with motionManager2.h, which this TU does not include (ClearMotionGeometryInfo, GetSkeltonFocusNode differ) */
extern int CheckFloorAttribute(char *self, int attr);
/* kept local: int (char *, int) here, int (char *) in motionManager2.h */
extern int CheckWallAttribute(char *self, int attr);
/* kept local: void (int) here, void (void *) in quaternion.h */
extern void SetIdentityQuaternion(int a0);
extern char objLayout[];

struct EnemyEnt {
    char _00[0x42];
    unsigned short f42;
}; /* 0x4C stride */

/* kept local: agrees with act-game.h, which this TU does not include (ACTGame_StageChangeGObjDirect, ACTGame_isHangChain differ) */
extern void ACTCharctrl_Lock(char *self);
/* kept local: float * (char *) here, void * (char *) in commonact.h */
extern float *test_CURRENTORIENT(char *target);
/* kept local: void (void *, void *, int, int, void *, float, float, float, float) here, void (char *, char *, float, float, float, int, int, float, void *) in motionManager2.h */
extern void SetMotionNodeFixModeParameter(void *a0, void *a1, int a2, int a3, void *a4, float f12,
                                          float f13, float f14, float f15);

/* .sbss, owned by script.o and reached only from this file: a stage change has
   been requested and no further one is accepted. */
static int stageChangeReq;

/* kept local: agrees with main.h, which this TU does not include (boyGObj, boyPad differ) */
extern int gameover_flag;
/* kept local: agrees with act-game.h, which this TU does not include (ACTGame_StageChangeGObjDirect, ACTGame_isHangChain differ) */
extern void ACTGame_StageChangeGObj(char *g, int no);
/* kept local: agrees with boyact.h, which this TU does not include (SetBoyWeaponGObj differ) */
extern void BoyInfoUpdate_StageChange(void);
/* kept local: agrees with act-game.h, which this TU does not include (ACTGame_StageChangeGObjDirect, ACTGame_isHangChain differ) */
extern void ACTCharctrl_Lock(char *a0);
/* kept local: agrees with act-game.h, which this TU does not include (ACTGame_isHangChain, ACTItemForceDrop differ) */
extern void ACTGame_StageChangeGObjDirect();
/* kept local: this TU's uses of IsWallLeverStatus do not fit the prototype in box.h */
extern int IsWallLeverStatus(void);
/* kept local: this TU's uses of ACTGame_isHangChain do not fit the prototype in act-game.h */
/* kept local: agrees with act-game.h, which this TU does not include (ACTGame_StageChangeGObjDirect, ACTItemForceDrop differ) */
extern int ACTGame_isHangChain();

/* the last object of script.o's .data (VMA 0x2A5400..0x2A5440): the layout
   record scpBornSpider fills and hands MakeAP1GObj for each spider */
static struct DQW spiderLayout = {0, 0, 0, 0, 0, 0, {0}, {1.0f, 1.0f, 1.0f}}; /* derived name */

/* kept local: void (int) here, void (int *) in act_a_p_1.h */
extern void WakeUpAP1(int a0);
/* kept local: int (float *, float) here, int (void *, float) in item.h */
extern int ReviveCarryableItemsWithBoundary(float *pos, float r);
/* kept local: agrees with box.h, which this TU does not include (IsWallLeverStatus differ) */
extern int CheckReadyAllSwitches();
/* kept local: void (void *, void *) here, void (void *, char *) in geometryManager.h */
extern void GetRootPosition(void *a0, void *a1);
/* kept local: void (void *, void *) here, void (char *, void *) in geometryManager.h */
extern void SetDirectRootPosition(void *a0, void *a1);
/* kept local: void (void *) here, int (char *) in item.h */
extern void BreakItemFromOutside(void *o);
/* kept local: int (void *) here, int (char *) in item.h */
extern int CheckItemDead(void *o);
/* kept local: int (void *) here, int (char *) in item.h */
extern int GetItemKind(void *o);
/* kept local: int (char *) here, int (int *) in act_a_p_1.h */
extern int IsActCharDead(char *g);
/* kept local: agrees with rotObject.h, which this TU does not include (GetRotObjectRotCount, GetRotObjectZPlusDirection differ) */
extern void GetRotObjectGameSysObjInfoExtData(short *a0, int *a1, char *a2);
extern ActMail queen_appear_mes[];

/* The January listing has no row for this function (its body is st25a.c's
 * actSt25aQueenAppear there); the retail object emits it last in the inline
 * block.  WHAT THE BYTES PIN: its first declaration follows
 * scpDoorTypeUpMain's (script.h), and its definition precedes every inline it
 * calls (ScpCallCameraSetTarget, scpSearchGobj and
 * scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag stay calls).  WHAT THEY
 * CANNOT PIN: its source line, so it opens the function list here. */
inline void actSubSekizoSe(volatile int a0)
{
    int x = a0;
    struct ScpAct *act = (struct ScpAct *)actInitialize(a0);

    _ACTWait(1);
    if (gflagChk(332) == 0) {
        ScpCallCameraSetTarget(3834.0f, -888.0f, 0.0f);
        *(int *)(scpSearchGobj(2149) + 0x16C) = 0;
        stage_SetLoopFlag(555, 0);
        queen_appear_mes[0].func = actSt25aQueenAppearChk;
        act->mail = queen_appear_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
        return;
    }
    scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(0x2F, 0, 0x22B, 0);
    *(int *)(scpSearchGobj(2149) + 0x16C) = 1;
    scpPlayMot((char *)scpSearchGobj(2149), 1104);
    tex_SetUVScroll(faceShadowTex, 0.0f, 0.0f, 0.25f, 0.0625f, 0.8f, 0.8f, 1);
    tex_SetUVScroll(faceShadowTex00, 0.0f, 0.0f, 0.25f, 0.0625f, 0.45f, 0.45f, 1);
    ScpCallCameraSetTarget(3834.0f, -888.0f, 0.0f);
    stage_SetAnimation(156, 0, -1);
    stage_SetAnimation(159, 1, 0);
}

inline void scpDispOffAllWithKind(void)
{
    int v0 = isysGObjSearchFromObjKindID_begin();
    while (v0 != 0) {
        *(int *)(v0 + 0x50) = 0;
        v0 = isysGObjSearchFromObjKindID_next(v0);
    }
}

inline void scpDispOnAllWithKind(int x)
{
    int *p = isysGObjSearchFromObjKindID_begin(x);
    while (p != 0) {
        ((unsigned int *)p)[0x50 / 4] = 0xFFFFFFFF;
        p = isysGObjSearchFromObjKindID_next(p);
    }
}

inline void scpActivateAllWithKind(void)
{
    int *p = isysGObjSearchFromObjKindID_begin();
    while (p != 0) {
        p[0x16C / 4] = 1;
        p = isysGObjSearchFromObjKindID_next(p);
    }
}

inline void scpDisActivateAllWithKind(void)
{
    int v0 = isysGObjSearchFromObjKindID_begin();
    while (v0 != 0) {
        *(int *)(v0 + 0x16C) = 0;
        v0 = isysGObjSearchFromObjKindID_next(v0);
    }
}

inline int scpIsTorchLightOn(int a0)
{
    int ret1 = scpSearchGobj(a0);
    int *ret2 = (int *)scpSearchGobj(0);
    ret2[0x16C / 4] = 1;
    return IsTorchLightOn(ret1);
}

void scpTorchLightOn(int id)
{
    void *r = scpSearchGobj(id);
    if (r) {
        LightTorchOn(r);
    }
}

void scpTorchLightOff(int id)
{
    int v = scpSearchGobj(id);
    if (v) {
        LightTorchOff(v);
    }
}

inline int *scpIsBombExplode(int x)
{
    int *p = isysGObjSearchFromObjKindID_begin(x);
    if (p != 0) {
        do {
            if (IsBombExplode(p) != 0) {
                return p;
            }
            p = isysGObjSearchFromObjKindID_next(p);
        } while (p != 0);
    }
    return 0;
}

void scpSetCageVelocityFriction(int id, float f12)
{
    int *v = scpSearchGobj(id);
    if (v) {
        SetCageVelocityFriction(v, f12);
    }
    /* no hanging object found */
    debug_StdPrintfDummy("ぶら下がりオブジェクトが見つかりません。(scpSetCageVelocityFriction)\n");
}

inline float scpGetRotObjectRotCount(int id)
{
    int v = scpSearchGobj(id);
    if (v != 0) {
        return GetRotObjectRotCount(v);
    }
    /* no push-turn object found */
    debug_StdPrintfDummy("押し回しオブジェクトが見つかりません。(scpGetRotObjectRotCount)\n");
    return 0.0f;
}

inline short scpGetRotObjectCurrentRot(int no)
{
    short rot;
    int ext;
    char *info = gamesysObjInfoGet(0x12, no);
    if (info != 0) {
        GetRotObjectGameSysObjInfoExtData(&rot, &ext, info);
        return rot;
    }
    return 0;
}

inline int scpIsRotObjectZPlusDirInclude(int a0, int a1, int a2)
{
    int q = scpSearchGobj(a0);
    if (q != 0) {
        int e = GetRotObjectZPlusDirection(q);
        short A1 = (a1 << 15) / 0xB4;
        short A2 = (a2 << 15) / 0xB4;
        if (A2 < A1) {
            if (A1 < e || e < A2)
                return 1;
            return 0;
        }
        if (A1 < e && e < A2)
            return 1;
        return 0;
    }
    /* no push-turn object found */
    debug_StdPrintfDummy("押し回しオブジェクトが見つかりません。(scpGetRotObjectZDirInclude)\n");
    return 0;
}

inline void scpLinkBGAtoLayoutedTarget(int a0, int a1)
{
    int ret = scpSearchGobj(a0);
    if (ret != 0) {
        int msg[2] = {ret, 0};
        stage_SetParentOfGObj(a1, msg);
    }
}

inline void scpLinkBGAtoLayoutedTargetSkeltonWithLocalRotationFlag(int a0, int a1, int a2, int a3)
{
    int ret = scpSearchGobj(a0);
    if (ret != 0) {
        struct SVF copy;
        struct SVF pair;
        pair.a = ret;
        pair.b = GetSkeltonFocusNode(ret, a1);
        copy = pair;
        if (copy.b == -1)
            /* LWS skeleton parenting: the node was not found */
            debug_StdPrintfDummy(
                "LWSのスケルトンペアレント処理において,ノードが見つかりませんでした\n");
        else
            stage_SetParentOfGObjWithLocalRotationFlag(a2, &copy, a3);
    }
}

inline void scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(int a0, int a1, int a2, int a3)
{
    int *ret = isysGObjSearchFromObjKindID_begin(a0);
    if (ret != 0) {
        struct SPMD copy;
        struct SPMD pair;
        pair.a = (int)ret;
        pair.b = GetSkeltonFocusNode((int)ret, a1);
        copy = pair;
        if (copy.b == -1)
            /* LWS skeleton parenting: the node was not found */
            debug_StdPrintfDummy(
                "LWSのスケルトンペアレント処理において,ノードが見つかりませんでした\n");
        else
            stage_SetParentOfGObjWithLocalRotationFlag(a2, &copy, a3);
    }
}

inline void scpLinkBGAtoLayoutedTargetSkelton(int a0, int a1, int a2)
{
    int ret = scpSearchGobj(a0);
    if (ret != 0) {
        struct S copy;
        struct S pair;
        pair.a = ret;
        pair.b = GetSkeltonFocusNode(ret, a1);
        copy = pair;
        if (copy.b == -1)
            /* LWS skeleton parenting: the node was not found */
            debug_StdPrintfDummy(
                "LWSのスケルトンペアレント処理において,ノードが見つかりませんでした\n");
        else
            stage_SetParentOfGObjWithLocalRotationFlag(a2, &copy, 1);
    }
}

inline struct WallCol *scpGetWallCollision(float x0, float y0, float z0, float x1, float y1,
                                           float z1)
{
    ClipWorkScript work;

    work.p0[0] = x0;
    work.p0[1] = y0;
    work.p0[2] = z0;
    work.p0[3] = 1.0f;
    work.p1[0] = x1;
    work.p1[1] = y1;
    work.p1[2] = z1;
    work.p1[3] = 1.0f;
    work.f70 = 0.0f;
    ClipWall(&work);
    wallColResult.f08 = work.res.f08;
    wallColResult.pos = work.res.pos;
    if (work.res.f08 == 0) {
        /* no wall collision found */
        debug_StdPrintfDummy(
            "scpGetWallCollision: (%4.3f, %4.3f, %4.3f) => (%4.3f, %4.3f, %4.3f)\n\t壁コリジョンが見つかりません。\n",
            x0, y0, z0, x1, y1, z1);
    }
    return &wallColResult;
}

inline int scpSearchGobj(int id)
{
    return isysGObjSearchFromObjLayoutID(id);
}

void scpPlayMotDir(char *self, float *dir)
{
    sceVu0Normalize(dir, dir);
    SetMotionDirection(self, dir);
}

void scpPlayMotDirSmz(char *self, float *dir)
{
    sceVu0Normalize(dir, dir);
    SetMotionDirectionSmooze(
        self, dir,
        (float)((struct MotTblRec *)(GOBJ_SUB(self)->f_4A0 * 0x194 + (char *)motionKind))
            ->smzAngle);
}

inline void scpPlayMotNode(void *a0, int a1, void *a2, int a3)
{
    float buf[4];
    memset(buf, 0, 0x10);
    buf[3] = 1.0f;
    SetMotionNodeFixModeParameter(a0, a2, 0, a3, buf, 0.0f, 0.0f, 0.0f, 1.0f);
    scpPlayMot(a0, a1);
}

void scpPlayMot(char *self, int mot)
{
    Act *act = GOBJ_ACT(self);
    int id = -1;

    if (self == boyGObj) {
        id = 0x501;
    } else if (self == girlGObj) {
        id = 0x846;
    } else if (self == (char *)isysGObjSearchFromObjLayoutID(0x865)) {
        id = 0x96D;
    } else if (*(int *)(self + 0xC) == 4) {
        id = 0x965;
    }

    if (id < 0) {
        InitMotionOrient(self, 0x84A, 0x967, -1, -1, mot);
        return;
    }
    ControlMotionOrient(id, mot);
    *(int *)((char *)act + 0x130) =
        SetMotionRequest(self, 0x10C, *(MotOriReq *)((char *)act + 0x620));
}

inline void scpPlayMotReq(char *a0, int a1)
{
    Act *p = GOBJ_ACT(a0);
    *(int *)((char *)p + 0x130) = SetMotionRequest(a0, a1, *(MotOriReq *)((char *)p + 0x620));
}

inline void scpPlayPosSet(void *a0, float f12, float f13, float f14)
{
    float buf[4];
    memset(buf, 0, 0x10);
    buf[0] = f12;
    buf[1] = f13;
    buf[2] = f14;
    SetDirectRootPosition(a0, buf);
    ClearMotionGeometryInfo(a0);
}

void scpPlayJump(char *a0, int a1)
{
    ACTItemForceDrop(a0);
    *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0xC0) = a1;
    iosOmSendMail(a0, 0x2D, a0);
}

void scpPlayStart(int a0)
{
    ACTItemForceDrop(a0);
    iosOmSendMail(a0, 0x2E, a0);
    SetLodLevel(a0, 0);
}

void scpPlayEnd(int a0)
{
    iosOmSendMail(a0, 0x2F, a0);
    SetLodLevel(a0, 2);
}

inline void scpPlayWaitMotEnd(char *a0)
{
    Act *p = GOBJ_ACT(a0);
    while ((*(int *)(*(char **)((char *)p + 0x130) + 0x5C) & 1) == 0) {
        _ACTWait(1);
    }
}

void scpTrans(void *a0, float *rot)
{
    SetRootMatrixWithTransOffset(a0, rot[0], rot[1], rot[2]);
}

/* one linear step of *p toward TARGET; returns non-zero once it arrives */
static inline int scpTransStep(float *p, float target, float step)
{
    int done = 0;

    if (0.0f < target) {
        *p += step;
        if (target < *p) {
            *p = target;
            done = 1;
        }
    } else {
        *p -= step;
        if (*p < target) {
            *p = target;
            done = 1;
        }
    }
    return done;
}

inline void scpTransLinear(void *obj, int axis, float target, float step)
{
    int done = 0;
    float pos[4];

    GetRootMatrixTransOffset(pos, obj);
    while (done == 0) {
        done = scpTransStep(&pos[axis], target, step);
        scpTrans(obj, pos);
        _ACTWait(1);
    }
}

inline void scpRotateLinear(void *obj, int deg, short step, int axis)
{
    float q[4];
    int t;
    int n;
    short rem;

    t = (deg << 15) / 180;
    rem = (short)(t % step);
    n = t / step < 0 ? -(t / step) : t / step;
    if (deg < 0) {
        step = -step;
    }
    while (n-- > 0 || rem != 0) {
        if (n < 0) {
            step = rem;
            rem = 0;
        }
        GetRootMatrixRotOffset(q, obj);
        step = -step;
        switch (axis) {
        case 0:
            RotQuaternionX(q, step);
            break;
        case 1:
            RotQuaternionY(q, step);
            break;
        case 2:
            RotQuaternionZ(q, step);
            break;
        }
        SetRootMatrixRotOffset(obj, q);
        _ACTWait(1);
    }
}

/* the colour a trigger ball's wire sphere is drawn in; red while it hits */
static const Col4 triggerBallColor = {{0, 16, 32, 128}}; /* derived name */

inline int scpTriggerPosBall(float *pos, float *target, float r)
{
    float d[4];
    Col4 col;
    float rr;
    int hit;

    sceVu0SubVector(d, target, pos);
    rr = r * r;
    if (sceVu0InnerProduct(d, d) < rr) {
        hit = 1;
    } else {
        hit = 0;
    }
    if (debug_wallcheck_flag != 0) {
        MatrixDrive_PushMatrix();
        col = triggerBallColor;
        if (hit != 0) {
            col.c[0] = 0xFF;
        }
        gif_StartPacketPri(0xB);
        sceVu0UnitMatrix(MatrixDrive_GetMatrix());
        MatrixDrive_TransMatrixV(pos);
        prim_DispWireSphere(r, &col, 16, 8);
        gif_EndPacket();
        MatrixDrive_PopMatrix();
    }
    return hit;
}

inline int scpTriggerBall(char *obj, char *target, float r)
{
    float tpos[4];
    float pos[4];

    GetRootPosition(tpos, target);
    GetRootPosition(pos, obj);
    return scpTriggerPosBall(pos, tpos, r);
}

/* the object kinds a trigger ball tests */
static const int targetManKind[] = {1, 2, 4}; /* derived name */

int scpTriggerBallTargetMan(char *obj, float r)
{
    char *g;
    unsigned int i;
    int hit = 0;

    for (i = 0; i < 3 && hit == 0; i++) {
        for (g = isysGObjSearchFromObjKindID_begin(targetManKind[i]); g != 0;
             g = isysGObjSearchFromObjKindID_next(g)) {
            if (scpTriggerBall(obj, g, r) != 0) {
                hit = 1;
                break;
            }
        }
    }
    return hit;
}

/* the object kinds a trigger may ignore, up to the -1 end marker */
static const int ignoreKind[] = {1, 2, 4, -1}; /* derived name */

inline int scpTriggerIgnore(char *self)
{
    int i = 0;

    while (ignoreKind[i] != -1) {
        if (*(int *)(self + 0xC) == ignoreKind[i]) {
            Sub15C *sub = GOBJ_SUB(self);
            if (_ACTGame_GetParamF(2) < *(float *)((char *)sub + 0x560) ||
                GOBJ_ACT(self)->unk34 == 0x16) {
                return 1;
            }
        }
        i++;
    }
    return 0;
}

inline int scpTriggerFloorAttr(char *self, int attr)
{
    if (scpTriggerIgnore(self) != 0) {
        return 0;
    }
    return CheckFloorAttribute(self, attr);
}

inline int scpTriggerWallAttr(char *self, int attr)
{
    if (scpTriggerIgnore(self) != 0) {
        return 0;
    }
    return CheckWallAttribute(self, attr);
}

/* the object kinds a floor-attribute trigger tests */
static const int floorTargetManKind[] = {1, 2, 4, 17}; /* derived name */

inline int scpTriggerFloorAttrTargetMan(char *self, int attr)
{
    char *g;
    unsigned int i;
    int hit = 0;

    for (i = 0; i < 4 && hit == 0; i++) {
        for (g = isysGObjSearchFromObjKindID_begin(floorTargetManKind[i]); g != 0;
             g = isysGObjSearchFromObjKindID_next(g)) {
            if (scpTriggerFloorAttr(g, attr) != 0) {
                hit = 1;
                break;
            }
        }
    }
    return hit;
}

inline int scpTriggerPosBox(float *p, float *pos, float *size)
{
    int hit = 0;

    if (pos[0] - size[0] < p[0] && p[0] < pos[0] + size[0] && pos[1] - size[1] < p[1] &&
        p[1] < pos[1] + size[1] && pos[2] - size[2] < p[2] && p[2] < pos[2] + size[2]) {
        hit = 1;
    }
    if (debug_wallcheck_flag != 0) {
        MatrixDrive_PushMatrix();
        if (hit != 0) {
            wireBoxColor[0] = 0xFF;
        } else {
            wireBoxColor[0] = 0;
        }
        gif_StartPacketPri(0xB);
        sceVu0UnitMatrix(MatrixDrive_GetMatrix());
        MatrixDrive_TransMatrixV(pos);
        prim_DispWireBox(size, wireBoxColor);
        gif_EndPacket();
        MatrixDrive_PopMatrix();
    }
    return hit;
}

inline int scpEffectStart(void *pos, int kind)
{
    int buf[4];
    SetIdentityQuaternion(buf);
    return SetParticleEffect(kind, pos, buf);
}

inline void scpDoorTypeUp(volatile int a0)
{
    Act *act = GOBJ_ACT(a0);

    if (gflagChk(*(int *)((char *)act + 0x454)) != 0) {
        int self = a0;
        scpTransLinear((void *)self, 1, -*(float *)((char *)act + 0x458),
                       *(float *)((char *)act + 0x458));
    }
    doorTypeUp_mes[0].func = scpDoorTypeUpMain;
    ((struct ScpAct *)act)->mail = doorTypeUp_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

inline void scpDoorTypeUpMain(volatile int a0)
{
    Act *p = GOBJ_ACT(a0);
    *(int *)((char *)p + 0xD0) = *(int *)((char *)p + 0x460);
    for (;;) {
        _ACTWait(1);
    }
}

inline void scpDoorTypeUpSwitch(volatile int a0)
{
    struct ScpAct *act = (struct ScpAct *)*(char **)(a0 + 0x164);

    act->mainMail = 0;
    if (gflagChk(*(int *)((char *)act + 0x454)) != 0) {
        doorTypeUpSwitchDown_mes[0].func = scpDoorTypeUpDown;
        act->mail = doorTypeUpSwitchDown_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
    doorTypeUpSwitchUp_mes[0].func = scpDoorTypeUpUp;
    act->mail = doorTypeUpSwitchUp_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void scpDoorTypeUpDown(volatile int a0)
{
    Act *act = GOBJ_ACT(a0);

    if (*(int *)((char *)act + 0x46C) != 0) {
        Camctrl_SetTarget(*(int *)((char *)act + 0x46C), 0, 3);
        if (*(int *)((char *)act + 0x464) != 0) {
            _ACTWait(*(int *)((char *)act + 0x464));
        }
    }
    debug_StdPrintfDummy("start animation down\n");
    gflagOff(*(int *)((char *)act + 0x454));
    scpTransLinear((void *)a0, 1, *(float *)((char *)act + 0x458), *(float *)((char *)act + 0x45C));
    if (*(int *)((char *)act + 0x468) != 0) {
        _ACTWait(*(int *)((char *)act + 0x468));
    }
    Camctrl_ExitEveRock();
    doorTypeUpDown_mes[0].func = scpDoorTypeUpMain;
    ((struct ScpAct *)act)->mail = doorTypeUpDown_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void scpDoorTypeUpUp(volatile int a0)
{
    Act *act = GOBJ_ACT(a0);

    if (*(int *)((char *)act + 0x46C) != 0) {
        Camctrl_SetTarget(*(int *)((char *)act + 0x46C), 0, 3);
        if (*(int *)((char *)act + 0x464) != 0) {
            _ACTWait(*(int *)((char *)act + 0x464));
        }
    }
    debug_StdPrintfDummy("start animation up\n");
    gflagOn(*(int *)((char *)act + 0x454));
    scpTransLinear((void *)a0, 1, -*(float *)((char *)act + 0x458),
                   *(float *)((char *)act + 0x45C));
    if (*(int *)((char *)act + 0x468) != 0) {
        _ACTWait(*(int *)((char *)act + 0x468));
    }
    Camctrl_ExitEveRock();
    doorTypeUpUp_mes[0].func = scpDoorTypeUpMain;
    ((struct ScpAct *)act)->mail = doorTypeUpUp_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

inline void scpAdpcmPlayRequestFunc(int kind, char **id, int a2, int a3, int a4)
{
    int i;

    if (id != 0) {
        *id = 0;
    }
    for (i = 0; i < 2; i++) {
        if (adpcmReq[i].kind == 0) {
            goto found;
        }
    }
    return;

found:
    adpcmReq[i].kind = kind;
    adpcmReq[i].id = id;
    adpcmReq[i].unk08 = a3;
    adpcmReq[i].unk0C = a2;
    adpcmReq[i].unk10 = a4;
    adpcmReq[i].unk14 = 0;
}

inline int scpAdpcmPlayRequestNum(void)
{
    int i;
    int n = 0;
    for (i = 0; i < 2; i++) {
        if (adpcmReq[i].kind != 0) {
            n++;
        }
    }
    return n;
}

/* the PAL listing's static helper at script.c:1636-1644 (inlined into
   scpAdpcmCloseChkFunc, scpGirlHintVoiceCancel, ... -- it has no MAIN.MAP
   symbol, so its rows show up outside every caller's own line span) */
static inline int scpAdpcmRequestSlot(char **id)
{
    int i;
    for (i = 0; i < 2; i++) {
        if (adpcmReq[i].kind != 0 && adpcmReq[i].id == id)
            goto found;
    }
    i = -1;
found:
    return i;
}

/* the PAL listing's second static helper at script.c:1651-1653 (inlined into
   scpAdpcmCloseFunc and scpAdpcmFadeCloseFunc): flag the pending play request
   whose id is ID so the ADPCM daemon closes it. */
static inline void scpAdpcmRequestClose(char **id)
{
    int i;
    for (i = 0; i < 2; i++)
        if (adpcmReq[i].kind != 0 && adpcmReq[i].id == id) {
            adpcmReq[i].unk14 = 1;
            break;
        }
}

void scpSubAdpcmPlay(volatile int a0)
{
    int work[8];
    int i;
    char *h;

    memset(adpcmReq, 0, sizeof(adpcmReq));
    for (;;) {
        AdpcmReq *tbl = adpcmReq;
        for (i = 0; i < 2; i++) {
            if (tbl[i].kind != 0) {
                AdpcmReq *p = &tbl[i];

                while (AdpcmFreeAreaGet() == 0) {
                    /* could not open: ADPCM is full */
                    debug_StdPrintfDummy("ADPCM一杯で開けませんでした。\n");
                    if (AdpcmNotUseIopAreaFree() != 0) {
                        /* an IOP area in use although nothing is open: found and forced free */
                        debug_StdPrintfDummy(
                            "オープンされていないのにも関わらず使われていないIOP領域発見&強制解放\n");
                    } else if (fightSoundPlayChk() != 0) {
                        /* stop the battle music and request instead; no battle music until the stage changes */
                        debug_StdPrintfDummy(
                            "戦闘曲を止めて,変わりにリクエストします。以降ステージ切り換えまで戦闘曲なりません。\n");
                        fightSoundProcessRequestPause();
                        while (fightSoundPlayChk() != 0) {
                            _ACTWait(1);
                        }
                    } else {
                        /* the battle music is not playing, so to keep the program running stop every tune and request instead */
                        debug_StdPrintfDummy(
                            "戦闘曲なっていないので,プログラムを止めないために\n全部曲を止めて,変わりにリクエストします。\n");
                        AdpcmFadeCloseAll(0x3FFF);
                        _ACTWait(1);
                    }
                }
                soundDataOpen(work, 2, p->kind, p->unk0C, p->unk08);
                while ((h = soundDataOpenSync(work)) == (char *)-1) {
                    _ACTWait(1);
                }
                if (h != 0) {
                    if (p->unk10 != 0) {
                        AdpcmPlay(*(int *)(h + 0x2C));
                    }
                    if (p->unk14 == 0) {
                        if (p->id != 0) {
                            *p->id = h;
                        }
                    } else {
                        soundDataClose(h);
                    }
                }
                p->kind = 0;
            }
        }
        _ACTWait(1);
    }
}

void scpAdpcmCloseFunc(char **h)
{
    char *handle = *h;
    if (handle != 0) {
        soundDataClose(handle);
        return;
    }
    scpAdpcmRequestClose(h);
}

inline int scpAdpcmFadeCloseFunc(char **h, short fade)
{
    char *p = *h;

    if (p != 0) {
        char *s = *(char **)(p + 0x2C);
        if (s == 0) {
            return 0;
        }
        *(short *)(s + 0x44) = fade;
        return 1;
    }
    scpAdpcmRequestClose(h);
    return 0;
}

inline int scpAdpcmCloseChkFunc(char **h)
{
    int no;
    char *p = *h;
    if (p != 0) {
        if (*(char **)(p + 0x2C) == 0 || *(int *)(*(char **)(p + 0x2C) + 0x28) == 0) {
            return 0;
        }
        return 1;
    }
    no = -1;
    return no < scpAdpcmRequestSlot(h);
}

/* the listing's rows put a label of TickProc's own at script.c:1773 after
   the inlined scpAdpcmCloseChkFunc (1760-1767): a static inline of its own
   that returns that check for the hint voice's slot, used only here (the name
   is ours; it has no out-of-line copy and no MAIN.MAP symbol) */
static inline int scpGirlHintVoiceChk(void)
{
    return scpAdpcmCloseChkFunc(&girlHintVoice);
}

inline void scpDeamon(volatile int a0)
{
    debug_StdPrintfDummy("deamon start");
    girlHintVoice = 0;
    startStagePauseDisableTimer = 0;
    if (stage_no == 0xB && gflagChk(137) == 0) {
        scpSeEnvMasterVolRate = 0.0f;
    } else {
        scpSeEnvMasterVolRate = 1.0f;
    }
    gflagOff(389);
    _ACTWait(1);
    actCreateSubThread(scpSubAdpcmPlay, 21);
    _ACTWait(3);
    StabilizeAllLayoutedCage();
    _ACTWait(1);
    backStageProcessInStage(0.0f);
    gflagOff(394);
}

void scpGirlHintVoiceReady(int kind)
{
    float p0[4];
    float p1[4];
    float d[4];
    float dist;

    if (girlHintVoice != 0) {
        /* a hint voice is playing, so a new one cannot be READY */
        debug_StdPrintfDummy("ヒントポイス再生中なので新にREADYできません\n");
    }
    if (AdpcmFreeAreaGet() == 0) {
        /* hint voice: could not open, ADPCM is full */
        debug_StdPrintfDummy("ヒントポイスADPCM一杯で開けませんでした。\n");
        return;
    }
    if (boyGObj == 0) {
        return;
    }
    GetRootPosition(p0, boyGObj);
    GetRootPosition(p1, girlGObj);
    _SubVector(d, p0, p1);
    dist = _InnerProduct(d, d);
    girlHintRangeMin = 500.0f;
    girlHintRangeMax = 4000.0f;
    switch (kind) {
    case 0x65:
        if (500000.0f < dist) {
            kind = 0x66;
        }
        break;
    case 0x67:
        if (500000.0f < dist) {
            kind = 0x68;
        }
        break;
    }
    scpAdpcmPlayRequestFunc(kind, &girlHintVoice, 1, 1, 0);
}

void scpGirlHintVoicePlay(void)
{
    char *p = girlHintVoice;
    if (p != 0) {
        AdpcmPlay(*(int *)(p + 0x2C));
    } else {
        /* the hint voice is not prepared yet, so it could not play */
        debug_StdPrintfDummy("ヒントポイスの準備未終了の状態なのでならせませんでした。\n");
    }
}

inline void scpGirlHintVoiceCancel(void)
{
    if (scpAdpcmCloseChkFunc(&girlHintVoice) != 0) {
        scpAdpcmCloseFunc(&girlHintVoice);
        girlHintVoice = 0;
    }
}

void scpGirlHintVoiceTickProc(void)
{
    float rmin = girlHintRangeMin; /* the listing's line 1892: both range globals are
                                read into locals before the early returns */
    float rmax = girlHintRangeMax;
    float pos[4];
    float dist;
    int deg;
    char *snd;
    float vol;
    float lr;
    float l;
    float r;
    int adeg;

    if (girlHintVoice == 0 || girlGObj == 0)
        return;
    if (scpGirlHintVoiceChk() == 0) {
        girlHintVoice = 0;
        return;
    }
    snd = *(char **)(girlHintVoice + 0x2C);
    GetRootPosition(pos, girlGObj);
    CameraGetOtherObjOffset(pos, &dist, &deg);
    if (rmax <= dist) {
        vol = 0.0f;
    } else if (dist < rmin) {
        vol = 1.0f / (dist / rmin + 1.0f);
    } else {
        dist = dist - rmin;
        vol = 1.0f / (dist / (rmax - rmin) + 1.0f) - 0.5f;
    }
    /* What the bytes pin (listing lines 1923 and 1925): the angle is read into
       adeg on a line of its own and the negation reads the angle again, so the
       conditional move keeps adeg in the load's register and jump's copy of
       the compared value carries the angle into the sign test below. What they
       cannot pin: whether the test was spelled `<= -1` or `< 0` (the same
       code). */
    adeg = deg;
    if (adeg <= -1)
        adeg = -deg;
    lr = (float)adeg * -0.0027777778f + 1.0f;
    /* each arm sets its fixed side first: the ROM keeps r in the register of
       the 1.0f the lr line loaded (no copy in this arm) and builds r from l
       in the other */
    if (deg >= 0) {
        r = 1.0f;
        adeg = deg;
        if (adeg >= 91)
            adeg = 180 - adeg;
        l = (float)adeg * -0.01f + 1.0f;
    } else {
        l = 1.0f;
        adeg = -deg;
        if (adeg >= 91)
            adeg = 180 - adeg;
        r = (float)adeg * -0.01f + 1.0f;
    }
    *(short *)(snd + 0x3C) = vol * 16383.0f * lr * l;
    *(short *)(snd + 0x42) = vol * 16383.0f * lr * r;
    AdpcmInterStereoVolumeSet(snd, 0);
}

void scpWoodSrh(char *self, struct WoodBoxEnt *w)
{
    float pos[4];
    float dst[4];
    float gpos[4];
    char *g;
    int st;
    void *way = 0;

    for (;;) {
        st = 0;
        GetRootPosition(pos, self);
        pos[1] -= 50.0f;
        switch (w->kind) {
        case 0:
            if (pos[0] < w->b0 && pos[1] > w->b1) {
                st = 1;
            } else {
                st = 2;
            }
            break;
        case 1:
            if (pos[0] > w->b0 && pos[1] > w->b1) {
                st = 1;
            } else {
                st = 2;
            }
            break;
        case 2:
            if (pos[2] > w->b0 && pos[1] > w->b1) {
                st = 1;
            } else {
                st = 2;
            }
            break;
        case 4:
        case 8:
            if (pos[0] < w->b0 && pos[1] > w->b1 && pos[2] > w->b2 && pos[2] < w->b3) {
                st = 1;
            } else {
                st = 2;
            }
            if (st == 1 && w->kind == 8) {
                for (g = isysGObjSearchFromObjKindID_begin(17); g != 0;
                     g = isysGObjSearchFromObjKindID_next(g)) {
                    if (g != self) {
                        if (*(int *)(g + 8) == 865 || *(int *)(g + 8) == 866) {
                            GetRootPosition(gpos, g);
                            gpos[1] -= 50.0f;
                            if (gpos[1] < -182.0f && gpos[1] > -280.0f) {
                                st = 2;
                            }
                        }
                    }
                }
            }
            break;
        case 5:
            if (pos[2] < w->b0 && pos[1] > w->b1 && pos[0] > w->b2 && pos[0] < w->b3) {
                st = 1;
            } else {
                st = 2;
            }
            break;
        case 6:
            if (pos[2] > w->b0 && pos[1] > w->b1 && pos[0] > w->b2 && pos[0] < w->b3) {
                st = 1;
            } else {
                st = 2;
            }
            break;
        case 7:
            if (pos[1] > -190.0f && (pos[0] < 660.0f || pos[0] > 916.0f) && pos[2] > -1600.0f) {
                st = 1;
                if (pos[0] > 916.0) {
                    w->ofs[0] = 100.0f;
                } else {
                    w->ofs[0] = -100.0f;
                }
            } else {
                st = 2;
            }
            break;
        case 9:
            if (pos[1] > 750.0f && (pos[0] < -515.0f || pos[0] > 325.0f)) {
                st = 1;
                if (pos[0] > 325.0) {
                    w->ofs[0] = 100.0f;
                } else {
                    w->ofs[0] = -100.0f;
                }
            } else {
                st = 2;
            }
            break;
        }
        switch (st) {
        case 1:
            if (way != 0) {
                DeleteWayGroup(way);
            } else {
                debug_StdPrintfDummy("bridge create");
            }
            sceVu0AddVector(dst, pos, w->ofs);
            way = CreateBridge(pos, dst);
            break;
        case 2:
            if (way != 0) {
                debug_StdPrintfDummy("bridge delete");
                DeleteWayGroup(way);
                way = 0;
            }
            break;
        }
        _ACTWait(1);
    }
}

inline void scpWoodBox(volatile int a0)
{
    struct WoodBoxEnt *p;
    unsigned int i;

    _ACTWait(10);

    for (i = 0, p = woodBoxTbl; i < 11; i++, p++) {
        if (p->id == *(int *)(a0 + 8)) {
            goto found;
        }
    }
    return;

found:
    scpWoodSrh(a0, p);
}

/* where the stone statue's sound effects play */
static const Vec16 sekizouSePos = {{6646.0f, -2157.0f, 1102.0f, 0.0f}}; /* derived name */

void scpSekizou(char *self, int flag, int anim, int anim2, int kind, float bx, float by, float bz,
                float gx, float gy, float gz)
{
    int fade = 0;

    if (gflagChk(flag) != 0) {
        stage_SetAnimation(anim, 0, -1);
        return;
    }
    stage_SetAnimation(anim, 0, 0);
    if (girlGObj == 0) {
        return;
    }
    for (;;) {
        if (scpTriggerBall(self, girlGObj, 200.0f) == 0 ||
            scpTriggerBall(self, boyGObj, 200.0f) == 0 || scpActStatusDeathFall(boyGObj) != 0) {
            _ACTWait(1);
        } else {
            break;
        }
    }
    if (gflagChk(394) != 0) {
        fade = 1;
        scpFadeOut(255.0f, 0, 0, 0);
    }
    stgmgrNextStagePreLoadForceStageSet(0);
    lt_switch_layout(55);
    scpBoyControlReadDisable = 1;
    scpAdpcmPlayRequestFunc(kind, &sekizo_common, 1, 1, 0);
    while (sekizo_common == 0) {
        _ACTWait(1);
    }
    AdpcmPlay(*(int *)(sekizo_common + 0x2C));
    if (fade != 0) {
        scpFadeIn(8.0f);
    }
    stgmgrNextStagePreLoadDistBoyMode();
    scpKillEnemyAll();
    scpMaskGeneratorAll();
    stage_SetAnimation(anim, 1, 0);
    ReviveAllCarryableItemsWithNonSleepFrame(250);
    sekizo_yure = iosPadActRequest(boyPad, 9);
    sekizo_yure_vol = 128;
    iosPadActVolumeSet(sekizo_yure, 128);
    scpPlayStart(girlGObj);
    scpPlayMot(girlGObj, 532);
    scpPlayPosSet(girlGObj, gx, gy, gz);
    scpPlayPosSet(boyGObj, bx, by, bz);
    _ACTWait(1);
    {
        Vec16 v;

        sceVu0SubVector(v.f, test_CURRENTROOT(self), test_CURRENTROOT(girlGObj));
        scpPlayMotDir(girlGObj, v.f);
        scpBoyControlReadDisable = 1;
        sceVu0SubVector(v.f, test_CURRENTROOT(girlGObj), test_CURRENTROOT(boyGObj));
        scpPlayMotDir(boyGObj, v.f);
        scpSekizouCheckPoint();
        scpPlayMot(girlGObj, 645);
        scpPlayWaitMotEnd(girlGObj);
        gflagOn(flag);
        if (anim2 != 0) {
            int h;

            stage_SetAnimation(anim2, 1, 0);
            v = sekizouSePos;
            soundSeDefPlay(1220, 0, v.f, 1);
            _ACTWait(30);
            h = soundSeDefPlay(1221, 0, v.f, 1);
            _ACTWait(38);
            soundSeDefStop(h);
            soundSeDefPlay(1222, 0, v.f, 1);
        }
    }
    while (stage_CheckAnimationFrame(anim, 180, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActStop(sekizo_yure);
    while (stage_CheckAnimationFinish(anim) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    scpPlayMot(girlGObj, 532);
    scpPlayEnd(girlGObj);
    lt_switch_layout(54);
    scpBoyControlReadDisable = 0;
}

inline void InitStageChange(void)
{
    stageChangeReq = 0;
}

inline int RequestStageChange(int no, char *g, int flag, float speed, float wait)
{
    return RequestStageChangeWithColor(no, g, flag, speed, wait, 0, 0, 0);
}

inline int RequestStageChangeWithColor(int no, char *g, int flag, float speed, float wait,
                                       unsigned char r, unsigned char gr, unsigned char b)
{
    int ret;
    short next;
    char *act;

    next = stageData[stage_no].ent[no - 1];
    ret = 0;
    if (gameover_flag == 0 && stageChangeReq == 0 && next != 0) {
        if (g != 0) {
            act = *(char **)(g + 0x164);
            ACTGame_StageChangeGObj(g, next);
            if (*(char **)(act + 0x150) != 0) {
                ACTGame_StageChangeGObj(*(char **)(act + 0x150), next);
            }
            if (*(char **)(act + 0x154) != 0) {
                ACTGame_StageChangeGObj(*(char **)(act + 0x154), next);
            }
            BoyInfoUpdate_StageChange();
        }
        if (flag != 0) {
            ACTGame_StageChangeGObj(girlGObj, next);
        }
        stgmgrForceSwitchWithFadeColor(exitData[next].id, speed, wait, r, gr, b);
        ret = 1;
        stageChangeReq = 1;
    }
    return ret;
}

inline int RequestStageChangeSimple(int no, float speed, float wait, unsigned char r,
                                    unsigned char gr, unsigned char b)
{
    int ret = 0;

    if (gameover_flag == 0) {
        if (stageChangeReq == 0) {
            stgmgrForceSwitchWithFadeColor(no, speed, wait, r, gr, b);
            stageChangeReq = 1;
            ret = 1;
        }
    }
    return ret;
}

/* the root position a direct stage change parks the actor at, far out of the map */
static const Vec16 farRootPos = {{-1000000.0f, 0.0f, 0.0f, 0.0f}}; /* derived name */

inline void RequestStageChangeDirect(int *self)
{
    Vec16 pos;
    ACTGame_StageChangeGObjDirect((int)self);
    ACTCharctrl_Lock((int)self);
    pos = farRootPos;
    SetDirectRootPosition(self, &pos);
    iosOmSendMail((int)self, 0x27, (int)self);
}

inline void scpFadeOut(float a0, int a1, int a2, int a3)
{
    fadeStatus = 1;
    fadeSpeed = a0;
    fadeContinue = 1;
    fadeColor[0] = a1;
    fadeColor[1] = a2;
    fadeColor[2] = a3;
}

inline void scpFadeIn(float f)
{
    fadeStatus = 1;
    fadeContinue = 0;
    fadeSpeed = -f;
}

inline int scpFadeChk(void)
{
    int v = fadeStatus;
    if (v == 0) {
        return 0;
    }
    if (v == 3) {
        v = 0;
        return v;
    }
    return 1;
}

void _SCPBoySupportGirl(float x0, float y0, float z0, float x1, float y1, float z1)
{
    float v0[4] = {x0, y0, z0};
    float v1[4] = {x1, y1, z1};
    struct WallCol *wc;

    if (boyGObj == 0 || girlGObj == 0) {
        return;
    }
    sceVu0ScaleVector(v0, v0, -1.0f);
    sceVu0ScaleVector(v1, v1, -1.0f);
    wc = scpGetWallCollision(v0[0], v0[1], v0[2], v1[0], v1[1], v1[2]);
    if (wc != 0) {
        *(struct WallCol *)(*(char **)(boyGObj + 0x164) + 0x670) = *wc;
        *(struct WallCol *)(*(char **)(girlGObj + 0x164) + 0x660) = *wc;
        iosOmSendMail(boyGObj, 385, boyGObj);
        iosOmSendMail(girlGObj, 386, boyGObj);
    }
}

/* declared int: the call's result register is live-out of the call in ROM's
   allocation (the same C89 default-int prototype the TU's other way/thread
   callees carry) */

inline int _SCPMoveCharactorByWay(char *self, int a1, int a2, float speed, int a3)
{
    struct ScpAct *act = (struct ScpAct *)*(char **)(self + 0x164);

    act->st18.ll |= 1ULL << 47;
    ACTCharctrl_Lock(self);
    ACTSendMailCorrect(self, 0x106);
    ACTWayExec_Position(self, a1, a2, speed, a3);
    act->st18.ll &= ~(1ULL << 47);
    ACTCharctrl_Unlock(self);
    return 0;
}

void _SCPMoveCharactorByWay_Cancel(char *a0)
{
    *(unsigned long long *)(*(char **)(a0 + 0x164) + 0x18) &= ~(1ULL << 47);
    ACTCharctrl_Unlock(a0);
}

inline void _SCPCharacterStop(char *self)
{
    Act *p = GOBJ_ACT(self);
    *(int *)((char *)p + 0x120) = 0;
    *(int *)((char *)p + 0x124) = 0;
    *(int *)((char *)p + 0x128) = 0;
    *(int *)((char *)p + 0x338) = *(int *)((char *)p + 0x33C) = 0x7F;
    p->f_34C = 0;
}

inline int _SCPMoveByWay_ToChar(char *self, char *target, int deg, int a3, float scale, float speed)
{
    float v[4];
    float w[4];

    v[0] = test_CURRENTORIENT(target)[0];
    v[1] = test_CURRENTORIENT(target)[1];
    v[2] = test_CURRENTORIENT(target)[2];
    _ApplyRyGV(v, (float)deg * 3.1415927f / 180.0f);
    sceVu0ScaleVector(v, v, scale);
    sceVu0AddVector(w, test_CURRENTROOT(target), v);
    return _SCPMoveCharactorByWay(self, (int)target, (int)w, speed, a3);
}

inline int scpGameStat_BoyWeaponkind(void)
{
    char *w = *(char **)(*(char **)(boyGObj + 0x164) + 0x150);
    if (w == 0)
        return 0;
    return CheckWeaponKind(w);
}

void scpSekizouCheckPoint(void)
{
    int was;

    if (girlGObj != 0) {
        gamesysObjInfoPosSetStage((int *)girlGObj, GOBJ_ACT(girlGObj)->f_444, 0, stage_no);
    }
    gamesysObjInfoPosSetStage((int *)boyGObj, GOBJ_ACT(boyGObj)->f_444, 0, stage_no);
    was = gflagChk(381);
    gflagOn(381);
    CheckPoint();
    if (was == 0) {
        gflagOff(381);
    }
}

inline int scpIsWallLever2On(void)
{
    return IsWallLeverStatus();
}

inline int scpIsHangChain(void)
{
    return ACTGame_isHangChain() != 0;
}

inline int scpIsHangChainOptional(int a0, int b)
{
    register int *p;         /* v1 */
    register int b_save;     /* s0 */
    register unsigned int v; /* v0 */
    b_save = b;
    p = ACTGame_isHangChain(a0);
    v = 0;
    if (p == 0)
        goto out;
    v = (unsigned int)(p[0x8 / 4] ^ b_save) < 1;
out:
    return (int)v;
}

void scpWakeupEnemyOne(int id)
{
    int rc = isysGObjSearchFromObjLayoutID(id);
    if (rc) {
        iosOmSendMail(rc, 0x1F, rc);
    }
}

inline void scpWakeupEnemyAll(void)
{
    char *g;
    for (g = isysGObjSearchFromObjKindID_begin(4); g != 0;
         g = isysGObjSearchFromObjKindID_next(g)) {
        iosOmSendMail(g, 0x1F, g);
    }
    for (g = isysGObjSearchFromObjKindID_begin(62); g != 0;
         g = isysGObjSearchFromObjKindID_next(g)) {
        iosOmSendMail(g, 0x1F, g);
    }
}

void scpSleepEnemyOne(int id)
{
    int rc = isysGObjSearchFromObjLayoutID(id);
    if (rc) {
        iosOmSendMail(rc, 0x20, rc);
    }
}

void scpSleepSpiderGroupOne(int id)
{
    int v = isysGObjSearchFromObjLayoutID(id);
    if (v) {
        SleepSpiderGroup(v);
    }
}

void scpWakeupSpiderGroupOne(int id)
{
    int v = isysGObjSearchFromObjLayoutID(id);
    if (v) {
        WakeupSpiderGroup(v);
    }
}

inline void scpSleepEnemyAll(void)
{
    char *g;
    for (g = isysGObjSearchFromObjKindID_begin(4); g != 0;
         g = isysGObjSearchFromObjKindID_next(g)) {
        iosOmSendMail(g, 0x20, g);
    }
    for (g = isysGObjSearchFromObjKindID_begin(62); g != 0;
         g = isysGObjSearchFromObjKindID_next(g)) {
        iosOmSendMail(g, 0x20, g);
    }
}

inline void scpKillEnemyOne(int id)
{
    int *p = isysGObjSearchFromObjLayoutID(id);
    if (p != 0) {
        iosOmSendMail((int)p, 0x26, (int)p);
        ((struct EnemyEnt *)(p[0x8 / 4] * 0x4C + (char *)objLayout))->f42 = 0;
    }
}

inline void scpKillEnemyAll(void)
{
    char *g;

    for (g = (char *)isysGObjSearchFromObjKindID_begin(4); g != 0;
         g = (char *)isysGObjSearchFromObjKindID_next(g)) {
        iosOmSendMail(g, 0x26, g);
        ((struct EnemyEnt *)(*(int *)(g + 8) * 0x4C + (char *)objLayout))->f42 = 0;
    }
    for (g = (char *)isysGObjSearchFromObjKindID_begin(62); g != 0;
         g = (char *)isysGObjSearchFromObjKindID_next(g)) {
        iosOmSendMail(g, 0x26, g);
    }
}

inline void scpMaskGeneratorAll(void)
{
    int *p = isysGObjSearchFromObjKindID_begin(33);
    while (p != 0) {
        Generator_Mask(p);
        p = isysGObjSearchFromObjKindID_next(p);
    }
}

void scpKillSpiderGroup(int id)
{
    DeleteAllSpidersOfLayoutGroup(isysGObjSearchFromObjLayoutID(id));
}

inline void scpBornSpider(int n, float a, float b, float c, float d)
{
    int i;
    float t1, t2;
    int r, dead;
    for (i = 0; i < n; i++) {
        t1 = random_unit();
        spiderLayout.f4 = b;
        spiderLayout.f0 = a + d * (t1 + t1 - 1.0f);
        t2 = random_unit();
        spiderLayout.f8 = c + d * (t2 + t2 - 1.0f);
        r = rand();
        spiderLayout.f30 = 1;
        spiderLayout.f14 = (float)((r >> 4) & 0xFFFF) * 3.1415927f * 3.0517578125e-05f;
        dead = MakeAP1GObj(&spiderLayout);
        _ACTWait(1);
        WakeUpAP1(dead);
    }
}

inline void scpSetStreamMotionRootOffset(int a0, float x, float y, float z)
{
    Vec4u v;
    v.f[0] = x;
    v.f[1] = y;
    v.f[2] = z;
    v.i[3] = 0;
    CopyVector((int)GOBJ_SUB(a0) + 0x670, &v);
}

/* the colour the item-revival boundary's wire sphere is drawn in */
static const Col4 itemBoundaryColor = {{0, 32, 16, 128}}; /* derived name */

inline void scpWakeupItemWithBoundary(float x, float y, float z, float r)
{
    float pos[4];
    Col4 col;

    pos[0] = x;
    pos[1] = y;
    pos[2] = z;
    ((int *)pos)[3] = 0;
    ReviveCarryableItemsWithBoundary(pos, r);
    if (debug_wallcheck_flag != 0) {
        MatrixDrive_PushMatrix();
        col = itemBoundaryColor;
        gif_StartPacketPri(0xB);
        sceVu0UnitMatrix(MatrixDrive_GetMatrix());
        MatrixDrive_TransMatrixV(pos);
        prim_DispWireSphere(r, &col, 16, 8);
        gif_EndPacket();
        MatrixDrive_PopMatrix();
    }
}

inline int scpCheckReadyAllObjects(void)
{
    return CheckReadyAllSwitches() != 0;
}

inline void ScpCallCameraOff(void)
{
    char *g = boyGObj;
    if (g != 0) {
        *(unsigned long long *)(*(char **)(g + 0x164) + 0x20) &= ~(1ULL << 23);
    }
}

inline void ScpCallCameraOn(void)
{
    char *g = boyGObj;
    if (g != 0) {
        *(long long *)(*(char **)(g + 0x164) + 0x20) |= 0x800000;
    }
}

inline void ScpCallCameraSetTarget(float x, float y, float z)
{
    /* the camera target is the NEGATED point, as a homogeneous vector; the
       block initializer is what keeps ROM's 0/4/8/C store order (a separate
       `pos[3] = 1.0f` statement lets sched hoist the constant store first) */
    float pos[4] = {-x, -y, -z, 1.0f};
    char *g = boyGObj;

    if (g != 0) {
        ActStatus *st = (ActStatus *)(*(char **)(g + 0x164) + 0x20);
        st->ll = (st->ll & ~(3ULL << 24)) | (1ULL << 24);
        scriptCameraTarget[0] = pos[0];
        scriptCameraTarget[1] = pos[1];
        scriptCameraTarget[2] = pos[2];
    }
}

inline void ScpCallCameraTargetOff(void)
{
    char *g = boyGObj;
    if (g != 0) {
        *(unsigned long long *)(*(char **)(g + 0x164) + 0x20) &= ~(3ULL << 24);
    }
}

inline void ScpCallCameraGetTarget(float *dst)
{
    dst[0] = scriptCameraTarget[0];
    dst[1] = scriptCameraTarget[1];
    dst[2] = scriptCameraTarget[2];
}

inline void scpTransGObj(void *a0, float f12, float f13, float f14)
{
    float buf[4];
    GetRootPosition(buf, a0);
    buf[0] = buf[0] + f12;
    buf[1] = buf[1] + f13;
    buf[2] = buf[2] + f14;
    SetDirectRootPosition(a0, buf);
}

inline void scpExplodeSecretItem(void)
{
    void *o = (void *)isysGObjSearchFromObjKindID_begin(19);
    while (o) {
        if (GetItemKind(o) == 6 && CheckItemDead(o) == 0) {
            BreakItemFromOutside(o);
            return;
        }
        o = (void *)isysGObjSearchFromObjKindID_next(o);
    }
}

void preload(int idx)
{
    short s;

    s = stageData[stage_no].ent[idx - 1];
    stgmgrNextStagePreLoadForceStageSet(exitData[s].id);
    stgmgrNextStagePreLoadForceNoCancel(1);
}

inline int scpActStatusDeathFall(char *self)
{
    char *sub;

    switch (*(unsigned int *)(*(char **)(self + 0x164) + 0x34)) {
    case 4:
    case 5:
    case 0x3E:
        break;
    case 0x16:
    case 0x18:
        return 1;
    default:
        return 0;
    }

    sub = (char *)GOBJ_SUB(self);
    if (stage_no == 0x22) {
        if (_ACTGame_GetParamF(2) - 200.0f < *(float *)(sub + 0x560)) {
            return 1;
        }
        sub = (char *)GOBJ_SUB(self);
    }
    if (_ACTGame_GetParamF(2) < *(float *)(sub + 0x560)) {
        return 1;
    }
    sub = (char *)GOBJ_SUB(self);
    if (!(_ACTGame_GetParamF(2) < *(float *)(sub + 0x55C))) {
        return 0;
    }
    return 1;
}

void scpSetBoyWeaponGObj(int a0, int a1, int a2, int a3)
{
    SetBoyWeaponGObj(a0, a1, a2, a3);
}

inline int scpCheckExistAliveEnemy(void)
{
    char *g;
    for (g = (char *)isysGObjSearchFromObjKindID_begin(4); g != 0;
         g = (char *)isysGObjSearchFromObjKindID_next(g)) {
        if (actEnemyFlagCheckDead(g) == 0) {
            /* found a living enemy */
            debug_StdPrintfDummy("scpCheckExistAliveEnemy: 生きている敵を発見\n");
            return 1;
        }
    }
    /* no living enemy */
    debug_StdPrintfDummy("scpCheckExistAliveEnemy: 生きている敵はいません\n");
    return 0;
}

inline int scpCheckExistAliveSpider(void)
{
    char *g;
    for (g = (char *)isysGObjSearchFromObjKindID_begin(62); g != 0;
         g = (char *)isysGObjSearchFromObjKindID_next(g)) {
        if (IsActCharDead(g) == 0) {
            /* found a living spider */
            debug_StdPrintfDummy("scpCheckExistAliveSpider: 生きている蜘蛛を発見\n");
            return 1;
        }
    }
    /* no living spider */
    debug_StdPrintfDummy("scpCheckExistAliveSpider: 生きている蜘蛛はいません\n");
    return 0;
}

inline void scpLockMaxRotate(char *a0, float f12)
{
    ((ActStatus *)(*(char **)(a0 + 0x164) + 0x20))->ll |= (1ULL << 33);
    *(float *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x344) = f12;
}

inline void scpUnLockMaxRotate(char *a0)
{
    *(unsigned long long *)(*(char **)(a0 + 0x164) + 0x20) &= ~(1ULL << 33);
}

inline void scpCheckDisconnectWallStart(char *a0)
{
    *(unsigned long long *)(*(char **)(a0 + 0x164) + 0x18) |= (1ULL << 58);
}

inline void scpCheckDisconnectWallEnd(char *a0)
{
    *(unsigned long long *)(*(char **)(a0 + 0x164) + 0x18) &= ~(1ULL << 58);
}
