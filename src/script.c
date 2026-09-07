#include "common.h"
#include "sugiCommon.h"

struct DQW { float f0, f4, f8, fc, f10, f14; char _18[0x18]; int f30; };

struct SPMD { int a; int b; };

struct SVF { int a; int b; };

typedef union { float f[4]; int i[4]; } Vec4u;

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
INCLUDE_ASM("asm/nonmatchings/src/script", scpPlayMot);
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
INCLUDE_ASM("asm/nonmatchings/src/script", scpTriggerBallTargetMan);
INCLUDE_ASM("asm/nonmatchings/src/script", scpDoorTypeUpDown);
INCLUDE_ASM("asm/nonmatchings/src/script", scpDoorTypeUpUp);
INCLUDE_ASM("asm/nonmatchings/src/script", scpSubAdpcmPlay);
INCLUDE_ASM("asm/nonmatchings/src/script", scpAdpcmCloseFunc);
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
INCLUDE_ASM("asm/nonmatchings/src/script", scpGirlHintVoiceTickProc);
INCLUDE_ASM("asm/nonmatchings/src/script", scpWoodSrh);
INCLUDE_ASM("asm/nonmatchings/src/script", scpSekizou);
INCLUDE_ASM("asm/nonmatchings/src/script", _SCPBoySupportGirl);
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
extern char D_0055C518[];
extern unsigned char D_005F5D50[];
extern int stage_no;
extern void stgmgrNextStagePreLoadForceNoCancel(int val);
extern void stgmgrNextStagePreLoadForceStageSet(int val);

void preload(int idx)
{
  int new_var;
  char *p;
  char *q;
  int new_var2;
  short s;
  new_var = 0xA0;
  p = &D_005F5D50[new_var];
  new_var = ((idx - 1) * 2) + (stage_no * 0x194);
  s = *((short *) (p + new_var));
  new_var2 = 0x28;
  ;
  q = &D_0055C518[new_var];
  stgmgrNextStagePreLoadForceStageSet(*((int *) ((&D_0055C518[s * new_var2]) + 0x24)));
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
INCLUDE_ASM("asm/nonmatchings/src/script", scpGetWallCollision);
INCLUDE_ASM("asm/nonmatchings/src/script", scpDoorTypeUp);
INCLUDE_ASM("asm/nonmatchings/src/script", scpDoorTypeUpSwitch);
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
INCLUDE_ASM("asm/nonmatchings/src/script", scpGirlHintVoiceCancel);
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
INCLUDE_ASM("asm/nonmatchings/src/script", scpTransLinear);
INCLUDE_ASM("asm/nonmatchings/src/script", scpRotateLinear);
INCLUDE_ASM("asm/nonmatchings/src/script", scpTriggerPosBall);
INCLUDE_ASM("asm/nonmatchings/src/script", scpTriggerBall);
INCLUDE_ASM("asm/nonmatchings/src/script", scpTriggerFloorAttr);
INCLUDE_ASM("asm/nonmatchings/src/script", scpTriggerWallAttr);
INCLUDE_ASM("asm/nonmatchings/src/script", scpTriggerFloorAttrTargetMan);
INCLUDE_ASM("asm/nonmatchings/src/script", scpTriggerPosBox);
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
INCLUDE_ASM("asm/nonmatchings/src/script", _SCPMoveCharactorByWay);
INCLUDE_ASM("asm/nonmatchings/src/script", _SCPMoveByWay_ToChar);
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
extern void scpPlayMot(void *a0, int a1);

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
   and by RequestStageChange, which forwards $f12/$f13 untouched). */
extern int RequestStageChangeWithColor(int no, char *g, int flag, float speed,
                                       float wait, int r, int gr, int b);

int RequestStageChange(int no, char *g, int flag, float speed, float wait) {
    return RequestStageChangeWithColor(no, g, flag, speed, wait, 0, 0, 0);
}
INCLUDE_ASM("asm/nonmatchings/src/script", RequestStageChangeWithColor);
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
extern float D_006390C0;
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
        D_002A5400.f14 = (float)((r >> 4) & 0xFFFF) * D_006390C0 * 3.0517578125e-05f;
        dead = MakeAP1GObj(&D_002A5400);
        _ACTWait(1);
        WakeUpAP1(dead);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/script", scpActStatusDeathFall);
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
typedef struct Blob16 { long long a, b; } Blob16;
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
INCLUDE_ASM("asm/nonmatchings/src/script", ScpCallCameraSetTarget);
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
INCLUDE_ASM("asm/nonmatchings/src/script", scpTriggerIgnore);
INCLUDE_ASM("asm/nonmatchings/src/script", scpDoorTypeUpMain);
INCLUDE_ASM("asm/nonmatchings/src/script", actSubSekizoSe);
