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

int RequestStageChange(int no, char *g, int flag, float speed, float wait);
void RequestStageChangeDirect(int *self);
int RequestStageChangeSimple(int a0, int a1, int a2, int a3);
int RequestStageChangeWithColor(int no, char *g, int flag, float speed, float wait, unsigned char r, unsigned char gr, unsigned char b);
void ScpCallCameraGetTarget(float *dst);
void ScpCallCameraOff(void);
void ScpCallCameraOn(void);
void ScpCallCameraSetTarget(float x, float y, float z);
void ScpCallCameraTargetOff(void);
int _SCPMoveByWay_ToChar(char *self, char *target, int deg, int a3, float scale, float speed);
int _SCPMoveCharactorByWay(char *self, int a1, int a2, float speed, int a3);
void _SCPMoveCharactorByWay_Cancel(char *a0);
void preload(int idx);
int scpActStatusDeathFall(char *self);
int scpAdpcmCloseChkFunc(char **h);
void scpAdpcmCloseFunc(char **h);
int scpAdpcmFadeCloseFunc(char **h, short fade);
void scpAdpcmPlayRequestFunc(int kind, char **id, int a2, int a3, int a4);
int scpAdpcmPlayRequestNum(void);
void scpBornSpider(int n, float a, float b, float c, float d);
void scpCheckDisconnectWallEnd(char *a0);
void scpCheckDisconnectWallStart(char *a0);
int scpCheckExistAliveEnemy(void);
void scpDisActivateAllWithKind(void);
void scpDispOffAllWithKind(void);
void scpDispOnAllWithKind(int x);
void scpDoorTypeUpDown(volatile int a0);
void scpDoorTypeUpMain(volatile int a0);
void scpDoorTypeUpUp(volatile int a0);
void scpEffectStart(int a0, int a1);
void scpExplodeSecretItem(void);
int scpFadeChk(void);
void scpFadeIn(float f);
void scpFadeOut(float a0, int a1, int a2, int a3);
int scpGameStat_BoyWeaponkind(void);
int scpGetRotObjectCurrentRot(int no);
float scpGetRotObjectRotCount(void);
void scpGetWallCollision(float a0, float a1, float a2, float a3, float a4, float a5);
void scpGirlHintVoiceCancel(void);
void scpGirlHintVoicePlay(void);
void scpGirlHintVoiceReady(int kind);
int *scpIsBombExplode(int x);
int scpIsHangChainOptional(int a0, int b);
int scpIsRotObjectZPlusDirInclude(int a0, int a1, int a2);
int scpIsTorchLightOn(int a0);
void scpKillEnemyAll(void);
void scpKillEnemyOne(void);
void scpKillSpiderGroup(void);
void scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(int a0, int a1, int a2, int a3);
void scpLinkBGAtoLayoutedTarget(int a0, int a1);
void scpLinkBGAtoLayoutedTargetSkeltonWithLocalRotationFlag(int a0, int a1, int a2, int a3);
void scpLockMaxRotate(char *a0, float f12);
void scpMaskGeneratorAll(void);
void scpPlayEnd(int a0);
void scpPlayMot(char *self, int mot);
void scpPlayMotDir(char *self, float *dir);
void scpPlayMotNode(void *a0, int a1, void *a2, int a3);
void scpPlayMotReq(char *a0, int a1);
void scpPlayPosSet(void *a0, float f12, float f13, float f14);
void scpPlayStart(int a0);
void scpPlayWaitMotEnd(char *a0);
int scpSearchGobj(int id);
void scpSekizou(char *self, int flag, int anim, int anim2, int kind, float bx, float by, float bz, float gx, float gy, float gz);
void scpSekizouCheckPoint(void);
void scpSetBoyWeaponGObj(int a0, int a1, int a2, int a3);
void scpSetCageVelocityFriction(float f12);
void scpSetStreamMotionRootOffset(int a0, float x, float y, float z);
void scpSleepEnemyAll(void);
void scpSleepEnemyOne(void);
void scpSleepSpiderGroupOne(void);
void scpSubAdpcmPlay(volatile int a0);
void scpTorchLightOff(void);
void scpTorchLightOn(void);
void scpTransGObj(void *a0, float f12, float f13, float f14);
int scpTriggerBall(char *obj, char *target, float r);
int scpTriggerFloorAttr(char *self, int attr);
int scpTriggerFloorAttrTargetMan(char *self, int attr);
int scpTriggerPosBall(float *pos, float *target, float r);
int scpTriggerPosBox(float *p, float *pos, float *size);
void scpUnLockMaxRotate(char *a0);
void scpWakeupEnemyAll(void);
void scpWakeupEnemyOne(void);
void scpWakeupItemWithBoundary(float x, float y, float z, float r);
void scpWakeupSpiderGroupOne(void);

#endif /* SCRIPT_H */
