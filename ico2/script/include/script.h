/*
 * ico2/script/include/script.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what script.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef SCRIPT_H
#define SCRIPT_H

/* The entry points script.o defines inline, in the order its end-of-file
 * block emits them: ee-gcc 2.9 defers every inline definition to the end of
 * the object and writes it out in first-declaration order, so this block is
 * read from the ROM (script.o's .text from scpDispOffAllWithKind on). */
void scpDispOffAllWithKind(void);
void scpDispOnAllWithKind(int x);
void scpActivateAllWithKind(void);
void scpDisActivateAllWithKind(void);
void scpLinkBGAtoLayoutedTarget(int a0, int a1);
void scpLinkBGAtoLayoutedTargetSkelton(int a0, int a1, int a2);
void scpLinkBGAtoLayoutedTargetSkeltonWithLocalRotationFlag(int a0, int a1, int a2, int a3);
void scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(int a0, int a1, int a2, int a3);
struct WallCol *scpGetWallCollision(float x0, float y0, float z0, float x1, float y1, float z1);
void scpDoorTypeUp(volatile int a0);
void scpDoorTypeUpSwitch(volatile int a0);
void scpAdpcmPlayRequestFunc(int kind, char **id, int a2, int a3, int a4);
int scpAdpcmPlayRequestNum(void);
int scpAdpcmFadeCloseFunc(char **h, short fade);
int scpAdpcmCloseChkFunc(char **h);
void scpDeamon(volatile int a0);
void scpGirlHintVoiceCancel(void);
void scpWoodBox(volatile int a0);
int scpIsTorchLightOn(int a0);
int *scpIsBombExplode(int x);
float scpGetRotObjectRotCount(int id);
int scpIsRotObjectZPlusDirInclude(int a0, int a1, int a2);
void scpTransLinear(void *obj, int axis, float target, float step);
void scpRotateLinear(void *obj, int deg, short step, int axis);
int scpTriggerPosBall(float *pos, float *target, float r);
int scpTriggerBall(char *obj, char *target, float r);
int scpTriggerFloorAttr(char *self, int attr);
int scpTriggerWallAttr(char *self, int attr);
int scpTriggerFloorAttrTargetMan(char *self, int attr);
int scpTriggerPosBox(float *p, float *pos, float *size);
void scpEffectStart(int a0, int a1);
void scpSleepEnemyAll(void);
void scpWakeupEnemyAll(void);
void scpKillEnemyAll(void);
void scpMaskGeneratorAll(void);
void scpKillEnemyOne(void);
int _SCPMoveCharactorByWay(char *self, int a1, int a2, float speed, int a3);
int _SCPMoveByWay_ToChar(char *self, char *target, int deg, int a3, float scale, float speed);
void _SCPCharacterStop(char *self);
int scpSearchGobj(int id);
void scpPlayMotNode(void *a0, int a1, void *a2, int a3);
void scpPlayMotReq(char *a0, int a1);
void scpPlayPosSet(void *a0, float f12, float f13, float f14);
void scpPlayWaitMotEnd(char *a0);
void InitStageChange(void);
int RequestStageChange(int no, char *g, int flag, float speed, float wait);

int RequestStageChangeWithColor(int no, char *g, int flag, float speed, float wait, unsigned char r,
                                unsigned char gr, unsigned char b);

int RequestStageChangeSimple(int no, float speed, float wait, unsigned char r, unsigned char gr,
                             unsigned char b);

void RequestStageChangeDirect(int *self);
void scpFadeOut(float a0, int a1, int a2, int a3);
void scpFadeIn(float f);
int scpFadeChk(void);
int scpGameStat_BoyWeaponkind(void);
int scpIsWallLever2On(void);
int scpIsHangChain(void);
int scpIsHangChainOptional(int a0, int b);
void scpBornSpider(int n, float a, float b, float c, float d);
int scpActStatusDeathFall(char *self);
void scpSetStreamMotionRootOffset(int a0, float x, float y, float z);
void scpWakeupItemWithBoundary(float x, float y, float z, float r);
int scpCheckReadyAllObjects(void);
void ScpCallCameraSetTarget(float x, float y, float z);
void ScpCallCameraGetTarget(float *dst);
void ScpCallCameraOff(void);
void ScpCallCameraOn(void);
void ScpCallCameraTargetOff(void);
void scpTransGObj(void *a0, float f12, float f13, float f14);
void scpExplodeSecretItem(void);
int scpCheckExistAliveEnemy(void);
int scpCheckExistAliveSpider(void);
void scpLockMaxRotate(char *a0, float f12);
void scpUnLockMaxRotate(char *a0);
int scpGetRotObjectCurrentRot(int no);
void scpCheckDisconnectWallStart(char *a0);
void scpCheckDisconnectWallEnd(char *a0);
int scpTriggerIgnore(char *self);
void scpDoorTypeUpMain(volatile int a0);
void actSubSekizoSe(volatile int a0);
/* The entry points script.o compiles in place, in its own parse order. */
void scpTorchLightOn(int id);
void scpTorchLightOff(int id);
void scpSetCageVelocityFriction(int id, float f12);
void scpPlayMotDir(char *self, float *dir);
void scpPlayMot(char *self, int mot);
void scpPlayStart(int a0);
void scpPlayEnd(int a0);
void scpDoorTypeUpDown(volatile int a0);
void scpDoorTypeUpUp(volatile int a0);
void scpSubAdpcmPlay(volatile int a0);
void scpAdpcmCloseFunc(char **h);
void scpGirlHintVoiceReady(int kind);
void scpGirlHintVoicePlay(void);

void scpSekizou(char *self, int flag, int anim, int anim2, int kind, float bx, float by, float bz,
                float gx, float gy, float gz);

void _SCPMoveCharactorByWay_Cancel(char *a0);
void scpSekizouCheckPoint(void);
void scpWakeupEnemyOne(void);
void scpSleepEnemyOne(void);
void scpSleepSpiderGroupOne(void);
void scpWakeupSpiderGroupOne(void);
void scpKillSpiderGroup(void);
void preload(int idx);
void scpSetBoyWeaponGObj(int a0, int a1, int a2, int a3);

#endif /* SCRIPT_H */
