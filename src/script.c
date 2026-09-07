#include "common.h"
#include "sugiCommon.h"

struct DQW { float f0, f4, f8, fc, f10, f14; char _18[0x18]; int f30; };

struct SPMD { int a; int b; };

struct SVF { int a; int b; };

typedef union { float f[4]; int i[4]; } Vec4u;

/* the 16-byte primitive colour record the debug wire-draws copy out of
   .rodata before overriding the first word */
typedef struct Blob16 { long long a, b; } Blob16;

/* MUST be above the TU's first call site: with the implicit `int` return the
   call SETs $2 and global-alloc picks different scratch registers. */
extern void _ACTWait(int a0);

/* ACT+0x20 / ACT+0x18 are the 64-bit actor status words.  The dev header
   declares them as a UNION (cf. `union ActStatus` in src/st13c.c and
   src/st04a.c), not as a bare `unsigned long long`: a union-member access has
   alias set 0, so a store through it aliases every other load -- which is why
   ROM re-loads `gobj->0x164` after a status store. */
typedef union ActStatus { unsigned long long ll; int i[2]; } ActStatus;

/* the two-slot ADPCM play-request table at D_006E5950 (2 x 0x18 bytes) */
typedef struct AdpcmReq {
    int  kind;   /* 0x00, 0 == slot free */
    int  id;     /* 0x04 */
    int  unk08;  /* 0x08 */
    int  unk0C;  /* 0x0C */
    int  unk10;  /* 0x10 */
    int  unk14;  /* 0x14 */
} AdpcmReq;
extern AdpcmReq D_006E5950[2];

/* the PAL listing's static helper at script.c:1636-1644 (inlined into
   scpAdpcmCloseChkFunc, scpGirlHintVoiceCancel, ... -- it has no MAIN.MAP
   symbol, so its rows show up outside every caller's own line span) */
static inline int scpAdpcmRequestSlot(int id)
{
    int i;
    for (i = 0; i < 2; i++) {
        if (D_006E5950[i].kind != 0 && D_006E5950[i].id == id) goto found;
    }
    i = -1;
found:
    return i;
}

struct S { int a; int b; };

extern void LightTorchOn(void *a0);
extern int scpSearchGobj();

void scpTorchLightOn(void) {
    void *r = scpSearchGobj();
    if (r) {
        LightTorchOn(r);
    }
}
extern void LightTorchOff();
extern int scpSearchGobj();

void scpTorchLightOff(void)
{
    int v = scpSearchGobj();
    if (v) {
        LightTorchOff(v);
    }
}
extern const char D_005543C0[];
extern void SetCageVelocityFriction(char *self, float val);
extern void debug_StdPrintfDummy();
extern int scpSearchGobj();

void scpSetCageVelocityFriction(float f12) {
    int *v = scpSearchGobj();
    if (v) {
        SetCageVelocityFriction(v, f12);
    }
    debug_StdPrintfDummy(D_005543C0);
}
extern void SetMotionDirection(char *self, float *dir);
/* SCE VU0 library: sceVu0Normalize(dst, src) -- normalised in place here, so
   the second argument is already in $a1 and cse drops the redundant copy. */
extern void sceVu0Normalize();

void scpPlayMotDir(char *self, float *dir)
{
    sceVu0Normalize(dir, dir);
    SetMotionDirection(self, dir);
}
extern void SetMotionDirectionSmooze(char *self, float *dir, float ang);
extern struct MotTblRec { char _000[0x186]; short smzAngle; char _188[0xC]; } D_0055FE58[];

void scpPlayMotDirSmz(char *self, float *dir)
{
    sceVu0Normalize(dir, dir);
    SetMotionDirectionSmooze(self, dir,
        (float)((struct MotTblRec *)(*(int *)(*(char **)(self + 0x15C) + 0x4A0) * 0x194
                                     + (char *)D_0055FE58))->smzAngle);
}
extern char *D_00639EA4;
extern char *D_00639EA8;
extern int isysGObjSearchFromObjLayoutID();
extern void InitMotionOrient(char *self, int a1, int a2, int a3, int a4, int mot);
extern void ControlMotionOrient(int id, int mot);
extern int SetMotionRequest(char *self, int a1, char *a2);

void scpPlayMot(char *self, int mot)
{
    char *act = *(char **)(self + 0x164);
    int id = -1;

    if (self == D_00639EA4) {
        id = 0x501;
    } else if (self == D_00639EA8) {
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
    *(int *)(act + 0x130) = SetMotionRequest(self, 0x10C, act + 0x620);
}
void scpPlayJump(char *a0, int a1) {
    ACTItemForceDrop(a0);
    *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0xC0) = a1;
    iosOmSendMail(a0, 0x2D, a0);
}
extern void ACTItemForceDrop(int a0);
extern int SetLodLevel();
extern int iosOmSendMail(char *self_arg, int val5, int val6);

void scpPlayStart(int a0)
{
    int new_var;
    ACTItemForceDrop(a0);
    iosOmSendMail(a0, 0x2E, a0);
    new_var = SetLodLevel(a0, 0);
    return new_var;
}
void scpPlayEnd(int a0)
{
    iosOmSendMail(a0, 0x2F, a0);
    SetLodLevel(a0, 2);
}
extern void SetRootMatrixWithTransOffset(void *a0, float x, float y, float z);

void scpTrans(void *a0, float *rot)
{
    SetRootMatrixWithTransOffset(a0, rot[0], rot[1], rot[2]);
}
extern int D_00554560[];
extern int D_0063B150;
extern char D_00554550[];
extern void sceVu0SubVector(float *d, float *a, float *b);
extern float sceVu0InnerProduct(float *a, float *b);
extern void MatrixDrive_PushMatrix(void);
extern void MatrixDrive_PopMatrix(void);
extern void *MatrixDrive_GetMatrix(void);
extern void sceVu0UnitMatrix(void *m);
extern void MatrixDrive_TransMatrixV(float *v);
extern void gif_StartPacketPri(int pri);
extern void gif_EndPacket(void);
extern void prim_DispWireSphere(void *col, int a1, int a2, float r);
extern void GetRootPosition(void *dst, void *obj);
/* INTERIM stand-in: scpTriggerPosBall is a real TU function with its own ROM
   slot (matched above), but the compiler inlines it into scpTriggerBall and
   scpTriggerBallTargetMan.  Delete it and mark the real definition `inline`
   once this TU is C-complete. */
static inline int scpTriggerPosBallInline(float *pos, float *target, float r)
{
    float d[4];
    Blob16 col;
    float rr;
    int hit;

    sceVu0SubVector(d, target, pos);
    rr = r * r;
    if (sceVu0InnerProduct(d, d) < rr) {
        hit = 1;
    } else {
        hit = 0;
    }
    if (D_0063B150 != 0) {
        MatrixDrive_PushMatrix();
        col = *(Blob16 *)D_00554550;
        if (hit != 0) {
            *(int *)&col = 0xFF;
        }
        gif_StartPacketPri(0xB);
        sceVu0UnitMatrix(MatrixDrive_GetMatrix());
        MatrixDrive_TransMatrixV(pos);
        prim_DispWireSphere(&col, 0x10, 8, r);
        gif_EndPacket();
        MatrixDrive_PopMatrix();
    }
    return hit;
}

/* INTERIM stand-in: scpTriggerBall is a real TU function with its own ROM slot
   (matched below), but the compiler inlines it here.  Delete it and mark the
   real definition `inline` once this TU is C-complete. */
static inline int scpTriggerBallInline(char *obj, char *target, float r)
{
    float tpos[4];
    float pos[4];

    GetRootPosition(tpos, target);
    GetRootPosition(pos, obj);
    return scpTriggerPosBallInline(pos, tpos, r);
}

int scpTriggerBallTargetMan(char *obj, float r)
{
    char *g;
    unsigned int i;
    int hit = 0;

    for (i = 0; i < 3 && hit == 0; i++) {
        for (g = isysGObjSearchFromObjKindID_begin(D_00554560[i]); g != 0;
             g = isysGObjSearchFromObjKindID_next(g)) {
            if (scpTriggerBallInline(obj, g, r) != 0) {
                hit = 1;
                break;
            }
        }
    }
    return hit;
}
extern const char D_00554590[];
extern void Camctrl_SetTarget(int target, int a1, int a2);
extern void Camctrl_ExitEveRock(void);
extern void gflagOff(int no);
extern void GetRootMatrixTransOffset(float *dst, void *obj);
extern void scpDoorTypeUpMain(volatile int a0);
extern void ACTSendMailCorrect(int a0, int mail);
/* the 0x20-byte door "mail" records in .data; the slot at +4 is the actor
   thread the mail starts. */
struct ScpMail { int mail; void (*func)(volatile int); char _08[0x18]; };
extern struct ScpMail D_002A51B0[];
struct ScpAct {
    char _000[0x18];
    ActStatus st18;             /* 0x18 -- the 64-bit actor status word */
    char _020[0xB0];
    struct ScpMail *mainMail;   /* 0xD0 */
    struct ScpMail *mail;       /* 0xD4 */
};

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

/* INTERIM stand-in: scpTransLinear is a real TU function with its own ROM slot
   (below), but the compiler inlines it into the door threads.  Delete it and
   mark the real definition `inline` once this TU is C-complete. */
static inline void scpTransLinearInline(void *obj, int axis, float target, float step)
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
void scpDoorTypeUpDown(volatile int a0)
{
    char *act = *(char **)(a0 + 0x164);

    if (*(int *)(act + 0x46C) != 0) {
        Camctrl_SetTarget(*(int *)(act + 0x46C), 0, 3);
        if (*(int *)(act + 0x464) != 0) {
            _ACTWait(*(int *)(act + 0x464));
        }
    }
    debug_StdPrintfDummy(D_00554590);
    gflagOff(*(int *)(act + 0x454));
    scpTransLinearInline((void *)a0, 1, *(float *)(act + 0x458), *(float *)(act + 0x45C));
    if (*(int *)(act + 0x468) != 0) {
        _ACTWait(*(int *)(act + 0x468));
    }
    Camctrl_ExitEveRock();
    D_002A51B0[0].func = scpDoorTypeUpMain;
    ((struct ScpAct *)act)->mail = D_002A51B0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
extern const char D_005545A8[];
extern void gflagOn(int no);
extern struct ScpMail D_002A51D0[];

void scpDoorTypeUpUp(volatile int a0)
{
    char *act = *(char **)(a0 + 0x164);

    if (*(int *)(act + 0x46C) != 0) {
        Camctrl_SetTarget(*(int *)(act + 0x46C), 0, 3);
        if (*(int *)(act + 0x464) != 0) {
            _ACTWait(*(int *)(act + 0x464));
        }
    }
    debug_StdPrintfDummy(D_005545A8);
    gflagOn(*(int *)(act + 0x454));
    scpTransLinearInline((void *)a0, 1, -*(float *)(act + 0x458), *(float *)(act + 0x45C));
    if (*(int *)(act + 0x468) != 0) {
        _ACTWait(*(int *)(act + 0x468));
    }
    Camctrl_ExitEveRock();
    D_002A51D0[0].func = scpDoorTypeUpMain;
    ((struct ScpAct *)act)->mail = D_002A51D0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
INCLUDE_ASM("asm/nonmatchings/src/script", scpSubAdpcmPlay);
INCLUDE_ASM("asm/nonmatchings/src/script", scpAdpcmCloseFunc);
ASM_LIT4_SLOT(D_00639090, 5e+05f);
ASM_LIT4_SLOT(D_00639094, 5e+05f);
INCLUDE_ASM("asm/nonmatchings/src/script", scpGirlHintVoiceReady);
extern char *D_0063AA10;
extern char D_00554750[];
void scpGirlHintVoicePlay(void) {
    char *p = D_0063AA10;
    if (p != 0) {
        AdpcmPlay(*(int *)(p + 0x2C));
    } else {
        debug_StdPrintfDummy(D_00554750);
    }
}
ASM_LIT4_SLOT(D_00639098, -0.0027777778f);
ASM_LIT4_SLOT(D_0063909C, -0.01f);
ASM_LIT4_SLOT(D_006390A0, -0.01f);
ASM_LIT4_SLOT(D_006390A4, 16383.0f);
INCLUDE_ASM("asm/nonmatchings/src/script", scpGirlHintVoiceTickProc);
ASM_LIT4_SLOT(D_006390A8, 7.5e+02f);
ASM_LIT4_SLOT(D_006390AC, -515.0f);
ASM_LIT4_SLOT(D_006390B0, 325.0f);
INCLUDE_ASM("asm/nonmatchings/src/script", scpWoodSrh);
ASM_LIT4_SLOT(D_006390B4, 4e+04f);
ASM_LIT4_SLOT(D_006390B8, 4e+04f);
INCLUDE_ASM("asm/nonmatchings/src/script", scpSekizou);
extern const char D_005544E0[];
extern void ClipWall(void *w);

/* the wall-collision result the ClipWall work area hands back at +0x80 */
struct WallColPos { int f00, f04; };
struct WallCol { struct WallColPos pos; int f08; };
extern struct WallCol D_006E5940;

typedef struct {
    float p0[4];            /* 0x00 */
    float p1[4];            /* 0x10 */
    char _020[0x50];        /* 0x20 */
    float f70;              /* 0x70 */
    char _074[0x0C];        /* 0x74 */
    struct WallCol res;     /* 0x80 */
    char _08C[0x34];        /* 0x8C */
} ClipWork;                 /* 0xC0 */

/* INTERIM stand-in.  scpGetWallCollision is a real TU function with its own
   ROM slot (below); the compiler inlines it here. */
static inline struct WallCol *scpGetWallCollisionInline(float x0, float y0, float z0,
                                                        float x1, float y1, float z1)
{
    ClipWork work;

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
    D_006E5940.f08 = work.res.f08;
    D_006E5940.pos = work.res.pos;
    if (work.res.f08 == 0) {
        debug_StdPrintfDummy(D_005544E0, x0, y0, z0, x1, y1, z1);
    }
    return &D_006E5940;
}
extern void sceVu0ScaleVector(float *dst, float *src, float scale);

void _SCPBoySupportGirl(float x0, float y0, float z0, float x1, float y1, float z1)
{
    float v0[4] = { x0, y0, z0 };
    float v1[4] = { x1, y1, z1 };
    struct WallCol *wc;

    if (D_00639EA4 == 0 || D_00639EA8 == 0) {
        return;
    }
    sceVu0ScaleVector(v0, v0, -1.0f);
    sceVu0ScaleVector(v1, v1, -1.0f);
    wc = scpGetWallCollisionInline(v0[0], v0[1], v0[2], v1[0], v1[1], v1[2]);
    if (wc != 0) {
        *(struct WallCol *)(*(char **)(D_00639EA4 + 0x164) + 0x670) = *wc;
        *(struct WallCol *)(*(char **)(D_00639EA8 + 0x164) + 0x660) = *wc;
        iosOmSendMail(D_00639EA4, 385, D_00639EA4);
        iosOmSendMail(D_00639EA8, 386, D_00639EA4);
    }
}
void _SCPMoveCharactorByWay_Cancel(char *a0) {
    *(unsigned long long *)(*(char **)(a0 + 0x164) + 0x18) &= ~(1ULL << 47);
    ACTCharctrl_Unlock(a0);
}
extern char *D_00639EA8;
extern char *D_00639EA4;
extern int stage_no;
extern void gamesysObjInfoPosSetStage(char *g, int no, int a2, int stage);
extern void CheckPoint(void);
extern int gflagChk(int no);
extern void gflagOn(int no);
extern void gflagOff(int no);

void scpSekizouCheckPoint(void)
{
    int was;

    if (D_00639EA8 != 0) {
        gamesysObjInfoPosSetStage(D_00639EA8,
            *(int *)(*(char **)(D_00639EA8 + 0x164) + 0x444), 0, stage_no);
    }
    gamesysObjInfoPosSetStage(D_00639EA4,
        *(int *)(*(char **)(D_00639EA4 + 0x164) + 0x444), 0, stage_no);
    was = gflagChk(0x17D);
    gflagOn(0x17D);
    CheckPoint();
    if (was == 0) {
        gflagOff(0x17D);
    }
}
extern int isysGObjSearchFromObjLayoutID();

void scpWakeupEnemyOne(void)
{
    int rc = isysGObjSearchFromObjLayoutID();
    if (rc) {
        iosOmSendMail(rc, 0x1F, rc);
    }
}
void scpSleepEnemyOne(void)
{
    int rc = isysGObjSearchFromObjLayoutID();
    if (rc) {
        iosOmSendMail(rc, 0x20, rc);
    }
}
extern void SleepSpiderGroup();

void scpSleepSpiderGroupOne(void)
{
    int v = isysGObjSearchFromObjLayoutID();
    if (v) {
        SleepSpiderGroup(v);
    }
}
extern void WakeupSpiderGroup();

void scpWakeupSpiderGroupOne(void)
{
    int v = isysGObjSearchFromObjLayoutID();
    if (v) {
        WakeupSpiderGroup(v);
    }
}
extern void DeleteAllSpidersOfLayoutGroup();

void scpKillSpiderGroup(void)
{
    DeleteAllSpidersOfLayoutGroup(isysGObjSearchFromObjLayoutID());
}
/* the 0x28-byte stage table at D_0055C518 and the per-stage 0x194-byte link
   table at D_005F5D50: row [stage_no], entry .next[no - 1] at +0xA0. */
struct StgEnt { char _00[0x24]; int id; };            /* 0x28 */
struct StgRow { char _000[0xA0]; short next[122]; };  /* 0x194 */
extern struct StgEnt D_0055C518[];
extern struct StgRow D_005F5D50[];
extern int stage_no;
extern void stgmgrNextStagePreLoadForceNoCancel(int val);
extern void stgmgrNextStagePreLoadForceStageSet(int val);

void preload(int idx)
{
    short s;

    s = D_005F5D50[stage_no].next[idx - 1];
    stgmgrNextStagePreLoadForceStageSet(D_0055C518[s].id);
    stgmgrNextStagePreLoadForceNoCancel(1);
}
extern void SetBoyWeaponGObj();

void scpSetBoyWeaponGObj(int a0, int a1, int a2, int a3)
{
    SetBoyWeaponGObj(a0, a1, a2, a3);
}
extern int isysGObjSearchFromObjKindID_begin();
extern int isysGObjSearchFromObjKindID_next();

void scpDispOffAllWithKind(void)
{
    int v0 = isysGObjSearchFromObjKindID_begin();
    while (v0 != 0) {
        *(int *)(v0 + 0x50) = 0;
        v0 = isysGObjSearchFromObjKindID_next(v0);
    }
}
void scpDispOnAllWithKind(int x)
{
  unsigned int new_var;
  int *p = isysGObjSearchFromObjKindID_begin(x);
  while (p != 0)
  {
    new_var = (int) 0xFFFFFFFFU;
    p[0x50 / 4] = new_var;
    p = isysGObjSearchFromObjKindID_next(p);
  }

}
void scpActivateAllWithKind(void)
{
    int *p = isysGObjSearchFromObjKindID_begin();
    while (p != 0) {
        p[0x16C / 4] = 1;
        p = isysGObjSearchFromObjKindID_next(p);
    }
}
void scpDisActivateAllWithKind(void)
{
    int v0 = isysGObjSearchFromObjKindID_begin();
    while (v0 != 0) {
        *(int *)(v0 + 0x16C) = 0;
        v0 = isysGObjSearchFromObjKindID_next(v0);
    }
}
extern int scpSearchGobj__pn(int a0) __asm__("scpSearchGobj");
extern void stage_SetParentOfGObj(int a0, int *a1);

void scpLinkBGAtoLayoutedTarget(int a0, int a1) {
    int ret = scpSearchGobj__pn(a0);
    if (ret != 0) {
        int msg[2] = { ret, 0 };
        stage_SetParentOfGObj(a1, msg);
    }
}
extern char D_00554498[];
extern int GetSkeltonFocusNode(int a0, int a1);
extern void stage_SetParentOfGObjWithLocalRotationFlag(int a0, void *a1, int a2);

void scpLinkBGAtoLayoutedTargetSkelton(int a0, int a1, int a2){
 int ret = scpSearchGobj(a0);
 if(ret != 0){ struct S copy; struct S pair;
  pair.a=ret; pair.b=GetSkeltonFocusNode(ret,a1);
  copy=pair;
  if(copy.b==-1) debug_StdPrintfDummy(D_00554498);
  else stage_SetParentOfGObjWithLocalRotationFlag(a2,&copy,1);
 } }
void scpLinkBGAtoLayoutedTargetSkeltonWithLocalRotationFlag(int a0, int a1, int a2, int a3){
  int ret = scpSearchGobj(a0);
  if(ret != 0){ struct SVF copy; struct SVF pair;
   pair.a=ret; pair.b=GetSkeltonFocusNode(ret,a1);
   copy=pair;
   if(copy.b==-1) debug_StdPrintfDummy(D_00554498);
   else stage_SetParentOfGObjWithLocalRotationFlag(a2,&copy,a3);
  } }
void scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(int a0, int a1, int a2, int a3){
  int *ret = isysGObjSearchFromObjKindID_begin(a0);
  if(ret != 0){ struct SPMD copy; struct SPMD pair;
   pair.a=(int)ret; pair.b=GetSkeltonFocusNode((int)ret,a1);
   copy=pair;
   if(copy.b==-1) debug_StdPrintfDummy(D_00554498);
   else stage_SetParentOfGObjWithLocalRotationFlag(a2,&copy,a3);
  } }
struct WallCol *scpGetWallCollision(float x0, float y0, float z0,
                                    float x1, float y1, float z1)
{
    ClipWork work;

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
    D_006E5940.f08 = work.res.f08;
    D_006E5940.pos = work.res.pos;
    if (work.res.f08 == 0) {
        debug_StdPrintfDummy(D_005544E0, x0, y0, z0, x1, y1, z1);
    }
    return &D_006E5940;
}
extern struct ScpMail D_002A5150[];

void scpDoorTypeUp(volatile int a0)
{
    char *act = *(char **)(a0 + 0x164);

    if (gflagChk(*(int *)(act + 0x454)) != 0) {
        int self = a0;
        scpTransLinearInline((void *)self, 1, -*(float *)(act + 0x458),
                             *(float *)(act + 0x458));
    }
    D_002A5150[0].func = scpDoorTypeUpMain;
    ((struct ScpAct *)act)->mail = D_002A5150;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
extern struct ScpMail D_002A5170[];
extern struct ScpMail D_002A5190[];
extern void scpDoorTypeUpDown(volatile int a0);
extern void scpDoorTypeUpUp(volatile int a0);

void scpDoorTypeUpSwitch(volatile int a0)
{
    struct ScpAct *act = (struct ScpAct *)*(char **)(a0 + 0x164);

    act->mainMail = 0;
    if (gflagChk(*(int *)((char *)act + 0x454)) != 0) {
        D_002A5170[0].func = scpDoorTypeUpDown;
        act->mail = D_002A5170;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
    D_002A5190[0].func = scpDoorTypeUpUp;
    act->mail = D_002A5190;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
void scpAdpcmPlayRequestFunc(int kind, int *id, int a2, int a3, int a4)
{
    int i;

    if (id != 0) {
        *id = 0;
    }
    for (i = 0; i < 2; i++) {
        if (D_006E5950[i].kind == 0) {
            goto found;
        }
    }
    return;

found:
    D_006E5950[i].kind = kind;
    D_006E5950[i].unk08 = a3;
    D_006E5950[i].unk0C = a2;
    D_006E5950[i].unk10 = a4;
    D_006E5950[i].unk14 = 0;
    D_006E5950[i].id = (int)id;
}
int scpAdpcmPlayRequestNum(void)
{
    int i;
    int n = 0;
    for (i = 0; i < 2; i++) {
        if (D_006E5950[i].kind != 0) {
            n++;
        }
    }
    return n;
}
INCLUDE_ASM("asm/nonmatchings/src/script", scpAdpcmFadeCloseFunc);
int scpAdpcmCloseChkFunc(int *h)
{
    int no;
    char *p = *(char **)h;
    if (p != 0) {
        if (*(char **)(p + 0x2C) == 0 || *(int *)(*(char **)(p + 0x2C) + 0x28) == 0) {
            return 0;
        }
        return 1;
    }
    no = -1;
    return no < scpAdpcmRequestSlot((int)h);
}
extern char D_005546E0[];
extern char *D_0063AA10;
extern float D_0063AA0C;
extern int startStagePauseDisableTimer;
extern void actCreateSubThread(void (*func)(volatile int), int a1);
extern void scpSubAdpcmPlay(volatile int a0);
extern void StabilizeAllLayoutedCage(void);
extern void backStageProcessInStage(float f);

void scpDeamon(volatile int a0)
{
    debug_StdPrintfDummy(D_005546E0);
    D_0063AA10 = 0;
    startStagePauseDisableTimer = 0;
    if (stage_no == 0xB && gflagChk(0x89) == 0) {
        D_0063AA0C = 0.0f;
    } else {
        D_0063AA0C = 1.0f;
    }
    gflagOff(0x185);
    _ACTWait(1);
    actCreateSubThread(scpSubAdpcmPlay, 0x15);
    _ACTWait(3);
    StabilizeAllLayoutedCage();
    _ACTWait(1);
    backStageProcessInStage(0.0f);
    gflagOff(0x18A);
}
/* INTERIM stand-in.  scpAdpcmCloseChkFunc above is a real TU function with its
   own ROM slot, but the compiler INLINES it here.  While the tail of this TU
   still holds INCLUDE_ASM members its definition cannot be turned into a
   single `inline` one ahead of its callers without moving its ROM slot, so
   this caller uses a byte-identical static copy.  Delete it once the TU is
   C-complete. */
static inline int scpAdpcmCloseChkFuncInline(int *h)
{
    int no;
    char *p = *(char **)h;
    if (p != 0) {
        if (*(char **)(p + 0x2C) == 0 || *(int *)(*(char **)(p + 0x2C) + 0x28) == 0) {
            return 0;
        }
        return 1;
    }
    no = -1;
    return no < scpAdpcmRequestSlot((int)h);
}
extern void scpAdpcmCloseFunc(int *h);

void scpGirlHintVoiceCancel(void)
{
    if (scpAdpcmCloseChkFuncInline((int *)&D_0063AA10) != 0) {
        scpAdpcmCloseFunc((int *)&D_0063AA10);
        D_0063AA10 = 0;
    }
}
extern void _ACTWait(int a0);
extern void scpWoodSrh(int self);
extern struct WoodBoxEnt { short id; char _02[0x2E]; } D_002A51F0[11];

void scpWoodBox(volatile int a0)
{
    struct WoodBoxEnt *p;
    unsigned int i;

    _ACTWait(0xA);

    for (i = 0, p = D_002A51F0; i < 11; i++, p++) {
        if (p->id == *(int *)(a0 + 8)) {
            goto found;
        }
    }
    return;

found:
    scpWoodSrh(a0);
}
extern int IsTorchLightOn(int a0);

int scpIsTorchLightOn(int a0) {
    int ret1 = scpSearchGobj(a0);
    int *ret2 = (int *)scpSearchGobj(0);
    ret2[0x16C / 4] = 1;
    return IsTorchLightOn(ret1);
}
extern int IsBombExplode(char *self);

int *scpIsBombExplode(int x)
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
extern int D_00554408[];
extern float GetRotObjectRotCount(int a0);

float scpGetRotObjectRotCount(void)
{
    int v = scpSearchGobj();
    if (v != 0) {
        return GetRotObjectRotCount(v);
    }
    debug_StdPrintfDummy(D_00554408);
    return 0.0f;
}
extern char D_00554450[];
extern int GetRotObjectZPlusDirection(int a0);

int scpIsRotObjectZPlusDirInclude(int a0, int a1, int a2){
 int q = scpSearchGobj(a0);
 if(q != 0){
  int e = GetRotObjectZPlusDirection(q);
  short A1 = (a1 << 15) / 0xB4;
  short A2 = (a2 << 15) / 0xB4;
  if(A2 < A1){ if(A1 < e || e < A2) return 1; return 0; }
  if(A1 < e && e < A2) return 1;
  return 0;
 }
 debug_StdPrintfDummy(D_00554450);
 return 0;
}
void scpTransLinear(void *obj, int axis, float target, float step)
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
extern void GetRootMatrixRotOffset(float *q, void *obj);
extern void SetRootMatrixRotOffset(void *obj, float *q);
extern void RotQuaternionX(float *q, int step);
extern void RotQuaternionY(float *q, int step);
extern void RotQuaternionZ(float *q, int step);

void scpRotateLinear(void *obj, int deg, short step, int axis)
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
extern int D_0063B150;
extern char D_00554550[];
extern void sceVu0SubVector(float *d, float *a, float *b);
extern float sceVu0InnerProduct(float *a, float *b);
extern void MatrixDrive_PushMatrix(void);
extern void MatrixDrive_PopMatrix(void);
extern void *MatrixDrive_GetMatrix(void);
extern void sceVu0UnitMatrix(void *m);
extern void MatrixDrive_TransMatrixV(float *v);
extern void gif_StartPacketPri(int pri);
extern void gif_EndPacket(void);
extern void prim_DispWireSphere(void *col, int a1, int a2, float r);

int scpTriggerPosBall(float *pos, float *target, float r)
{
    float d[4];
    Blob16 col;
    float rr;
    int hit;

    sceVu0SubVector(d, target, pos);
    rr = r * r;
    if (sceVu0InnerProduct(d, d) < rr) {
        hit = 1;
    } else {
        hit = 0;
    }
    if (D_0063B150 != 0) {
        MatrixDrive_PushMatrix();
        col = *(Blob16 *)D_00554550;
        if (hit != 0) {
            *(int *)&col = 0xFF;
        }
        gif_StartPacketPri(0xB);
        sceVu0UnitMatrix(MatrixDrive_GetMatrix());
        MatrixDrive_TransMatrixV(pos);
        prim_DispWireSphere(&col, 0x10, 8, r);
        gif_EndPacket();
        MatrixDrive_PopMatrix();
    }
    return hit;
}
int scpTriggerBall(char *obj, char *target, float r)
{
    float tpos[4];
    float pos[4];

    GetRootPosition(tpos, target);
    GetRootPosition(pos, obj);
    return scpTriggerPosBallInline(pos, tpos, r);
}
extern int D_00554570[];
extern float _ACTGame_GetParamF(int idx);
/* INTERIM stand-in for scpTriggerIgnore (matched at its own ROM slot below);
   the compiler inlines it into every scpTrigger* entry point and a deferred
   `inline` definition would have to sit at the object's end. */
static inline int scpTriggerIgnoreInline(char *self)
{
    int i = 0;

    while (D_00554570[i] != -1) {
        if (*(int *)(self + 0xC) == D_00554570[i]) {
            char *sub = *(char **)(self + 0x15C);
            if (_ACTGame_GetParamF(2) < *(float *)(sub + 0x560)
                || *(int *)(*(char **)(self + 0x164) + 0x34) == 0x16) {
                return 1;
            }
        }
        i++;
    }
    return 0;
}
extern int CheckFloorAttribute(char *self, int attr);

int scpTriggerFloorAttr(char *self, int attr)
{
    if (scpTriggerIgnoreInline(self) != 0) {
        return 0;
    }
    return CheckFloorAttribute(self, attr);
}
extern int CheckWallAttribute(char *self, int attr);

int scpTriggerWallAttr(char *self, int attr)
{
    if (scpTriggerIgnoreInline(self) != 0) {
        return 0;
    }
    return CheckWallAttribute(self, attr);
}
extern int D_00554580[];
/* INTERIM stand-in: scpTriggerFloorAttr is a real TU function with its own ROM
   slot (matched above), but the compiler inlines it here.  Delete it and mark
   the real definition `inline` once this TU is C-complete. */
static inline int scpTriggerFloorAttrInline(char *self, int attr)
{
    if (scpTriggerIgnoreInline(self) != 0) {
        return 0;
    }
    return CheckFloorAttribute(self, attr);
}

int scpTriggerFloorAttrTargetMan(char *self, int attr)
{
    char *g;
    unsigned int i;
    int hit = 0;

    for (i = 0; i < 4 && hit == 0; i++) {
        for (g = isysGObjSearchFromObjKindID_begin(D_00554580[i]); g != 0;
             g = isysGObjSearchFromObjKindID_next(g)) {
            if (scpTriggerFloorAttrInline(g, attr) != 0) {
                hit = 1;
                break;
            }
        }
    }
    return hit;
}
/* the 16-byte wire-box colour packet; declared as the full 4-word record so
   gcc addresses it with a %hi/%lo pair rather than gp-relative (-G 8). */
extern int D_002A5100[4];
extern void prim_DispWireBox(float *size, int *col);

int scpTriggerPosBox(float *p, float *pos, float *size)
{
    int hit = 0;

    if (pos[0] - size[0] < p[0] && p[0] < pos[0] + size[0]
        && pos[1] - size[1] < p[1] && p[1] < pos[1] + size[1]
        && pos[2] - size[2] < p[2] && p[2] < pos[2] + size[2]) {
        hit = 1;
    }
    if (D_0063B150 != 0) {
        MatrixDrive_PushMatrix();
        if (hit != 0) {
            D_002A5100[0] = 0xFF;
        } else {
            D_002A5100[0] = 0;
        }
        gif_StartPacketPri(0xB);
        sceVu0UnitMatrix(MatrixDrive_GetMatrix());
        MatrixDrive_TransMatrixV(pos);
        prim_DispWireBox(size, D_002A5100);
        gif_EndPacket();
        MatrixDrive_PopMatrix();
    }
    return hit;
}
extern void SetIdentityQuaternion(int a0);
extern int SetParticleEffect(int a0, int a1, int a2);

void scpEffectStart(int a0, int a1)
{
    int buf[4];
    SetIdentityQuaternion(buf);
    SetParticleEffect(a1, a0, buf);
}
void scpSleepEnemyAll(void) {
    char *g;
    for (g = isysGObjSearchFromObjKindID_begin(4); g != 0; g = isysGObjSearchFromObjKindID_next(g)) {
        iosOmSendMail(g, 0x20, g);
    }
    for (g = isysGObjSearchFromObjKindID_begin(0x3E); g != 0; g = isysGObjSearchFromObjKindID_next(g)) {
        iosOmSendMail(g, 0x20, g);
    }
}
void scpWakeupEnemyAll(void) {
    char *g;
    for (g = isysGObjSearchFromObjKindID_begin(4); g != 0; g = isysGObjSearchFromObjKindID_next(g)) {
        iosOmSendMail(g, 0x1F, g);
    }
    for (g = isysGObjSearchFromObjKindID_begin(0x3E); g != 0; g = isysGObjSearchFromObjKindID_next(g)) {
        iosOmSendMail(g, 0x1F, g);
    }
}
extern char D_002C2DC8[];
struct EnemyEnt { char _00[0x42]; unsigned short f42; };   /* 0x4C stride */

void scpKillEnemyAll(void)
{
    char *g;

    for (g = (char *)isysGObjSearchFromObjKindID_begin(4); g != 0;
         g = (char *)isysGObjSearchFromObjKindID_next(g)) {
        iosOmSendMail(g, 0x26, g);
        ((struct EnemyEnt *)(*(int *)(g + 8) * 0x4C + (char *)D_002C2DC8))->f42 = 0;
    }
    for (g = (char *)isysGObjSearchFromObjKindID_begin(0x3E); g != 0;
         g = (char *)isysGObjSearchFromObjKindID_next(g)) {
        iosOmSendMail(g, 0x26, g);
    }
}
extern void Generator_Mask(char *self);

void scpMaskGeneratorAll(void)
{
    int *p = isysGObjSearchFromObjKindID_begin(0x21);
    while (p != 0) {
        Generator_Mask(p);
        p = isysGObjSearchFromObjKindID_next(p);
    }
}
extern char D_002C2DC8[];

void scpKillEnemyOne(void)
{
  char *new_var;
  int *p = isysGObjSearchFromObjLayoutID();
  if (p != 0)
  {
    iosOmSendMail((int) p, 0x26, (int) p);
    new_var = (char *) D_002C2DC8;
    *((unsigned short *) ((new_var + (p[0x8 / 4] * 0x4C)) + 0x42)) = 0;
  }
}
extern void ACTCharctrl_Lock(char *self);
/* declared int: the call's result register is live-out of the call in ROM's
   allocation (the same C89 default-int prototype the TU's other way/thread
   callees carry) */
extern int ACTWayExec_Position(char *self, int a1, int a2, float speed, int a3);

int _SCPMoveCharactorByWay(char *self, int a1, int a2, float speed, int a3)
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
extern float *test_CURRENTORIENT(char *target);
extern float *test_CURRENTROOT(char *target);
extern void _ApplyRyGV(float *v, float ang);
extern void sceVu0ScaleVector(float *dst, float *src, float scale);
extern void sceVu0AddVector(float *dst, float *a, float *b);

/* INTERIM stand-in.  _SCPMoveCharactorByWay is a real TU function with its own
   ROM slot (just above); the compiler inlines it here.  Delete once the TU is
   C-complete and the real definition can carry `inline`. */
static inline int _SCPMoveCharactorByWayInline(char *self, int a1, int a2, float speed, int a3)
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

int _SCPMoveByWay_ToChar(char *self, char *target, int deg, int a3, float scale, float speed)
{
    float v[4];
    float w[4];

    v[0] = test_CURRENTORIENT(target)[0];
    v[1] = test_CURRENTORIENT(target)[1];
    v[2] = test_CURRENTORIENT(target)[2];
    _ApplyRyGV(v, (float)deg * 3.1415927f / 180.0f);
    sceVu0ScaleVector(v, v, scale);
    sceVu0AddVector(w, test_CURRENTROOT(target), v);
    return _SCPMoveCharactorByWayInline(self, (int)target, (int)w, speed, a3);
}
void _SCPCharacterStop(char *self)
{
    char *p = *(char **)(self + 0x164);
    *(int *)(p + 0x120) = 0; *(int *)(p + 0x124) = 0; *(int *)(p + 0x128) = 0; *(int *)(p + 0x338) = *(int *)(p + 0x33C) = 0x7F; *(int *)(p + 0x34C) = 0;
}
int scpSearchGobj(void) {
    return isysGObjSearchFromObjLayoutID();
}
extern void SetMotionNodeFixModeParameter(void *a0, void *a1, int a2, int a3, void *a4, float f12, float f13, float f14, float f15);
extern void memset(void *a0, int a1, int a2);
extern void scpPlayMot(char *a0, int a1);

void scpPlayMotNode(void *a0, int a1, void *a2, int a3) {
    float buf[4];
    memset(buf, 0, 0x10);
    buf[3] = 1.0f;
    SetMotionNodeFixModeParameter(a0, a2, 0, a3, buf, 0.0f, 0.0f, 0.0f, 1.0f);
    scpPlayMot(a0, a1);
}
void scpPlayMotReq(char *a0, int a1) {
    char *p = *(char **)(a0 + 0x164);
    *(int *)(p + 0x130) = SetMotionRequest(a0, a1, p + 0x620);
}
extern void ClearMotionGeometryInfo(void *a0);
extern void SetDirectRootPosition();

void scpPlayPosSet(void *a0, float f12, float f13, float f14) {
    float buf[4];
    memset(buf, 0, 0x10);
    buf[0] = f12;
    buf[1] = f13;
    buf[2] = f14;
    SetDirectRootPosition(a0, buf);
    ClearMotionGeometryInfo(a0);
}
void scpPlayWaitMotEnd(char *a0) {
    char *p = *(char **)(a0 + 0x164);
    while ((*(int *)(*(char **)(p + 0x130) + 0x5C) & 1) == 0) {
        _ACTWait(1);
    }
}
extern int D_0063C24C;

void InitStageChange(void) {
    D_0063C24C = 0;
}
/* EABI: the six int parameters land in $a0..$t1 and the two floats in
   $f12/$f13, so the floats are parameters 4 and 5 (proved by the ROM body of
   RequestStageChangeWithColor, which reads $a0,$a1,$a2,$a3,$t0,$t1,$f12,$f13,
   and by RequestStageChange, which forwards $f12/$f13 untouched).  The three
   colour components are `unsigned char`: the disc listing attributes their
   three `andi 0xff` masks to the function's declarator line, so they are
   parameter promotions and not statements in the body. */
extern int RequestStageChangeWithColor(int no, char *g, int flag, float speed,
                                       float wait, unsigned char r,
                                       unsigned char gr, unsigned char b);

int RequestStageChange(int no, char *g, int flag, float speed, float wait) {
    return RequestStageChangeWithColor(no, g, flag, speed, wait, 0, 0, 0);
}
extern int D_00639EB4;
extern char *D_00639EA8;
extern void ACTGame_StageChangeGObj(char *g, int no);
extern void BoyInfoUpdate_StageChange(void);
extern void stgmgrForceSwitchWithFadeColor(int id, float speed, float wait, int r, int gr, int b);

int RequestStageChangeWithColor(int no, char *g, int flag, float speed, float wait,
                                unsigned char r, unsigned char gr, unsigned char b)
{
    int ret;
    short next;
    char *act;

    next = D_005F5D50[stage_no].next[no - 1];
    ret = 0;
    if (D_00639EB4 == 0 && D_0063C24C == 0 && next != 0) {
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
            ACTGame_StageChangeGObj(D_00639EA8, next);
        }
        stgmgrForceSwitchWithFadeColor(D_0055C518[next].id, speed, wait, r, gr, b);
        ret = 1;
        D_0063C24C = 1;
    }
    return ret;
}
extern int D_00639EB4;
extern int D_0063C24C;
extern void stgmgrForceSwitchWithFadeColor();

int RequestStageChangeSimple(int a0, int a1, int a2, int a3)
{
    int ret = 0;
    a1 = a1 & 0xFF;
    a2 = a2 & 0xFF;
    a3 = a3 & 0xFF;
    if (D_00639EB4 == 0) {
        if (D_0063C24C == 0) {
            stgmgrForceSwitchWithFadeColor(a0, a1, a2, a3);
            D_0063C24C = 1;
            ret = 1;
        }
    }
    return ret;
}
extern void ACTCharctrl_Lock(char *a0);
extern void ACTGame_StageChangeGObjDirect();
extern long long D_00554800[];

void RequestStageChangeDirect(int *self)
{
    long long buf[2];
    ACTGame_StageChangeGObjDirect((int)self);
    ACTCharctrl_Lock((int)self);
    buf[0] = D_00554800[0];
    buf[1] = D_00554800[1];
    SetDirectRootPosition(self, (int *)buf);
    iosOmSendMail((int)self, 0x27, (int)self);
}
extern int fadeStatus;
extern float fadeSpeed;
extern int fadeContinue;
extern unsigned char fadeColor;
extern unsigned char D_0063BCB1;
extern unsigned char D_0063BCB2;

void scpFadeOut(float a0, int a1, int a2, int a3) {
    fadeStatus = 1;
    fadeSpeed = a0;
    fadeContinue = 1;
    fadeColor = a1;
    D_0063BCB1 = a2;
    D_0063BCB2 = a3;
}
void scpFadeIn(float f) {
    fadeStatus = 1;
    fadeContinue = 0;
    fadeSpeed = -f;
}
int scpFadeChk(void)
{
  int v = fadeStatus;
  if (v == 0)
  {
    return 0;
  }
  if (v == 3)
  {
    v = 0;
    return v;
  }
  return 1;
}
extern char *D_00639EA4;
int scpGameStat_BoyWeaponkind(void) {
    char *w = *(char **)(*(char **)(D_00639EA4 + 0x164) + 0x150);
    if (w == 0) return 0;
    return CheckWeaponKind(w);
}
extern int IsWallLeverStatus(void);

int scpIsWallLever2On(void)
{
    return IsWallLeverStatus();
}
extern int ACTGame_isHangChain();

int scpIsHangChain(void) {
    return ACTGame_isHangChain() != 0;
}
extern int ACTGame_isHangChain();

int scpIsHangChainOptional(int a0, int b)
{
    register int *p;  /* v1 */
    register int b_save;  /* s0 */
    register unsigned int v;  /* v0 */
    b_save = b;
    p = ACTGame_isHangChain(a0);
    v = 0;
    if (p == 0) goto out;
    v = (unsigned int)(p[0x8/4] ^ b_save) < 1;
out:
    return (int)v;
}
extern struct DQW D_002A5400;
extern int MakeAP1GObj(void *p);
extern void WakeUpAP1(int a0);
extern void _ACTWait(int a0);
extern int rand(void);

void scpBornSpider(int n, float a, float b, float c, float d) {
    int i;
    float t1, t2;
    int r, dead;
    for (i = 0; i < n; i++) {
        t1 = random_unit();
        D_002A5400.f4 = b;
        D_002A5400.f0 = a + d * (t1 + t1 - 1.0f);
        t2 = random_unit();
        D_002A5400.f8 = c + d * (t2 + t2 - 1.0f);
        r = rand();
        D_002A5400.f30 = 1;
        D_002A5400.f14 = (float)((r >> 4) & 0xFFFF) * 3.1415927f * 3.0517578125e-05f;
        dead = MakeAP1GObj(&D_002A5400);
        _ACTWait(1);
        WakeUpAP1(dead);
    }
}
extern float _ACTGame_GetParamF(int idx);

int scpActStatusDeathFall(char *self)
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

    sub = *(char **)(self + 0x15C);
    if (stage_no == 0x22) {
        if (_ACTGame_GetParamF(2) - 200.0f < *(float *)(sub + 0x560)) {
            return 1;
        }
        sub = *(char **)(self + 0x15C);
    }
    if (_ACTGame_GetParamF(2) < *(float *)(sub + 0x560)) {
        return 1;
    }
    sub = *(char **)(self + 0x15C);
    if (!(_ACTGame_GetParamF(2) < *(float *)(sub + 0x55C))) {
        return 0;
    }
    return 1;
}
extern void CopyVector(int a0, void *a1);

void scpSetStreamMotionRootOffset(int a0, float x, float y, float z)
{
    Vec4u v;
    v.f[0] = x;
    v.f[1] = y;
    v.f[2] = z;
    v.i[3] = 0;
    CopyVector(*(int *)(a0 + 0x15C) + 0x670, &v);
}
extern char D_00554810[];
extern int D_0063B150;
extern int ReviveCarryableItemsWithBoundary(float *pos, float r);
extern void MatrixDrive_PushMatrix(void);
extern void MatrixDrive_PopMatrix(void);
extern void *MatrixDrive_GetMatrix(void);
extern void sceVu0UnitMatrix(void *m);
extern void MatrixDrive_TransMatrixV(float *v);
extern void gif_StartPacketPri(int pri);
extern void gif_EndPacket(void);
extern void prim_DispWireSphere(void *col, int a1, int a2, float r);

void scpWakeupItemWithBoundary(float x, float y, float z, float r)
{
    float pos[4];
    Blob16 col;

    pos[0] = x;
    pos[1] = y;
    pos[2] = z;
    ((int *)pos)[3] = 0;
    ReviveCarryableItemsWithBoundary(pos, r);
    if (D_0063B150 != 0) {
        MatrixDrive_PushMatrix();
        col = *(Blob16 *)D_00554810;
        gif_StartPacketPri(0xB);
        sceVu0UnitMatrix(MatrixDrive_GetMatrix());
        MatrixDrive_TransMatrixV(pos);
        prim_DispWireSphere(&col, 0x10, 8, r);
        gif_EndPacket();
        MatrixDrive_PopMatrix();
    }
}
extern int CheckReadyAllSwitches();

int scpCheckReadyAllObjects(void) {
    return CheckReadyAllSwitches() != 0;
}
extern float D_006E5980[];

void ScpCallCameraSetTarget(float x, float y, float z)
{
    /* the camera target is the NEGATED point, as a homogeneous vector; the
       block initializer is what keeps ROM's 0/4/8/C store order (a separate
       `pos[3] = 1.0f` statement lets sched hoist the constant store first) */
    float pos[4] = { -x, -y, -z, 1.0f };
    char *g = D_00639EA4;

    if (g != 0) {
        ActStatus *st = (ActStatus *)(*(char **)(g + 0x164) + 0x20);
        st->ll = (st->ll & ~(3ULL << 24)) | (1ULL << 24);
        D_006E5980[0] = pos[0];
        D_006E5980[1] = pos[1];
        D_006E5980[2] = pos[2];
    }
}
extern float D_006E5980[];

void ScpCallCameraGetTarget(float *dst)
{
    dst[0] = D_006E5980[0];
    dst[1] = D_006E5980[1];
    dst[2] = D_006E5980[2];
}
void ScpCallCameraOff(void) {
    char *g = D_00639EA4;
    if (g != 0) {
        *(unsigned long long *)(*(char **)(g + 0x164) + 0x20) &= ~(1ULL << 23);
    }
}
extern char *D_00639EA4;
void ScpCallCameraOn(void) {
    char *g = D_00639EA4;
    if (g != 0) {
        *(long long *)(*(char **)(g + 0x164) + 0x20) |= 0x800000;
    }
}
void ScpCallCameraTargetOff(void) {
    char *g = D_00639EA4;
    if (g != 0) {
        *(unsigned long long *)(*(char **)(g + 0x164) + 0x20) &= ~(3ULL << 24);
    }
}
extern void GetRootPosition(void *a0, void *a1);
extern void SetDirectRootPosition__pn(void *a0, void *a1) __asm__("SetDirectRootPosition");

void scpTransGObj(void *a0, float f12, float f13, float f14) {
    float buf[4];
    GetRootPosition(buf, a0);
    buf[0] = buf[0] + f12;
    buf[1] = buf[1] + f13;
    buf[2] = buf[2] + f14;
    SetDirectRootPosition__pn(a0, buf);
}
extern void BreakItemFromOutside(void *o);
extern int CheckItemDead(void *o);
extern int GetItemKind(void *o);
extern void *isysGObjSearchFromObjKindID_begin__pn(int id) __asm__("isysGObjSearchFromObjKindID_begin");
extern void *isysGObjSearchFromObjKindID_next__pn(void *o) __asm__("isysGObjSearchFromObjKindID_next");

void scpExplodeSecretItem(void) {
    void *o = isysGObjSearchFromObjKindID_begin__pn(0x13);
    while (o) {
        if (GetItemKind(o) == 6 && CheckItemDead(o) == 0) {
            BreakItemFromOutside(o);
            return;
        }
        o = isysGObjSearchFromObjKindID_next__pn(o);
    }
}
extern char D_00554820[];
extern char D_00554850[];
extern int actEnemyFlagCheckDead(char *g);

int scpCheckExistAliveEnemy(void)
{
    char *g;
    for (g = (char *)isysGObjSearchFromObjKindID_begin(4); g != 0;
         g = (char *)isysGObjSearchFromObjKindID_next(g)) {
        if (actEnemyFlagCheckDead(g) == 0) {
            debug_StdPrintfDummy(D_00554820);
            return 1;
        }
    }
    debug_StdPrintfDummy(D_00554850);
    return 0;
}
extern char D_00554888[];
extern char D_005548B8[];
extern int IsActCharDead(char *g);

int scpCheckExistAliveSpider(void)
{
    char *g;
    for (g = (char *)isysGObjSearchFromObjKindID_begin(0x3E); g != 0;
         g = (char *)isysGObjSearchFromObjKindID_next(g)) {
        if (IsActCharDead(g) == 0) {
            debug_StdPrintfDummy(D_00554888);
            return 1;
        }
    }
    debug_StdPrintfDummy(D_005548B8);
    return 0;
}
void scpLockMaxRotate(char *a0, float f12) {
    ((ActStatus *)(*(char **)(a0 + 0x164) + 0x20))->ll |= (1ULL << 33);
    *(float *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x344) = f12;
}
void scpUnLockMaxRotate(char *a0) {
    *(unsigned long long *)(*(char **)(a0 + 0x164) + 0x20) &= ~(1ULL << 33);
}
extern char *gamesysObjInfoGet(int kind, int no);
extern void GetRotObjectGameSysObjInfoExtData(short *a0, int *a1, char *a2);

int scpGetRotObjectCurrentRot(int no)
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
void scpCheckDisconnectWallStart(char *a0) {
    *(unsigned long long *)(*(char **)(a0 + 0x164) + 0x18) |= (1ULL << 58);
}
void scpCheckDisconnectWallEnd(char *a0) {
    *(unsigned long long *)(*(char **)(a0 + 0x164) + 0x18) &= ~(1ULL << 58);
}
extern int D_00554570[];
extern float _ACTGame_GetParamF(int idx);

int scpTriggerIgnore(char *self)
{
    int i = 0;

    while (D_00554570[i] != -1) {
        if (*(int *)(self + 0xC) == D_00554570[i]) {
            char *sub = *(char **)(self + 0x15C);
            if (_ACTGame_GetParamF(2) < *(float *)(sub + 0x560)) {
                return 1;
            }
            if (*(int *)(*(char **)(self + 0x164) + 0x34) == 0x16) {
                return 1;
            }
        }
        i++;
    }
    return 0;
}
void scpDoorTypeUpMain(volatile int a0)
{
    char *p = *(char **)(a0 + 0x164);
    *(int *)(p + 0xD0) = *(int *)(p + 0x460);
    for (;;) {
        _ACTWait(1);
    }
}
ASM_LIT4_SLOT(D_006390C4, 3834.0f);
ASM_LIT4_SLOT(D_006390C8, 0.8f);
ASM_LIT4_SLOT(D_006390CC, 0.45f);
ASM_LIT4_SLOT(D_006390D0, 3834.0f);
INCLUDE_ASM("asm/nonmatchings/src/script", actSubSekizoSe);
