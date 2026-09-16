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

extern int RequestStageChange(int no, char *g, int flag, float speed, float wait);
extern void RequestStageChangeDirect(int *self);
extern int RequestStageChangeSimple(int a0, int a1, int a2, int a3);
extern int RequestStageChangeWithColor(int no, char *g, int flag, float speed, float wait, unsigned char r, unsigned char gr, unsigned char b);
extern void ScpCallCameraGetTarget(float *dst);
extern void ScpCallCameraOff(void);
extern void ScpCallCameraOn(void);
extern void ScpCallCameraSetTarget(float x, float y, float z);
extern void ScpCallCameraTargetOff(void);
extern int _SCPMoveByWay_ToChar(char *self, char *target, int deg, int a3, float scale, float speed);
extern int _SCPMoveCharactorByWay(char *self, int a1, int a2, float speed, int a3);
extern void _SCPMoveCharactorByWay_Cancel(char *a0);
extern void preload(int idx);
extern int scpActStatusDeathFall(char *self);
extern int scpAdpcmCloseChkFunc(char **h);
extern void scpAdpcmCloseFunc(char **h);
extern int scpAdpcmFadeCloseFunc(char **h, short fade);
extern void scpAdpcmPlayRequestFunc(int kind, char **id, int a2, int a3, int a4);
extern int scpAdpcmPlayRequestNum(void);
extern void scpBornSpider(int n, float a, float b, float c, float d);
extern void scpCheckDisconnectWallEnd(char *a0);
extern void scpCheckDisconnectWallStart(char *a0);
extern int scpCheckExistAliveEnemy(void);
extern void scpDisActivateAllWithKind(void);
extern void scpDispOffAllWithKind(void);
extern void scpDispOnAllWithKind(int x);
extern void scpDoorTypeUpDown(volatile int a0);
extern void scpDoorTypeUpMain(volatile int a0);
extern void scpDoorTypeUpUp(volatile int a0);
extern void scpEffectStart(int a0, int a1);
extern void scpExplodeSecretItem(void);
extern int scpFadeChk(void);
extern void scpFadeIn(float f);
extern void scpFadeOut(float a0, int a1, int a2, int a3);
extern int scpGameStat_BoyWeaponkind(void);
extern int scpGetRotObjectCurrentRot(int no);
extern float scpGetRotObjectRotCount(void);
extern void scpGetWallCollision(float a0, float a1, float a2, float a3, float a4, float a5);
extern void scpGirlHintVoiceCancel(void);
extern void scpGirlHintVoicePlay(void);
extern void scpGirlHintVoiceReady(int kind);
extern int *scpIsBombExplode(int x);
extern int scpIsHangChainOptional(int a0, int b);
extern int scpIsRotObjectZPlusDirInclude(int a0, int a1, int a2);
extern int scpIsTorchLightOn(int a0);
extern void scpKillEnemyAll(void);
extern void scpKillEnemyOne(void);
extern void scpKillSpiderGroup(void);
extern void scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(int a0, int a1, int a2, int a3);
extern void scpLinkBGAtoLayoutedTarget(int a0, int a1);
extern void scpLinkBGAtoLayoutedTargetSkeltonWithLocalRotationFlag(int a0, int a1, int a2, int a3);
extern void scpLockMaxRotate(char *a0, float f12);
extern void scpMaskGeneratorAll(void);
extern void scpPlayEnd(int a0);
extern void scpPlayMot(char *self, int mot);
extern void scpPlayMotDir(char *self, float *dir);
extern void scpPlayMotNode(void *a0, int a1, void *a2, int a3);
extern void scpPlayMotReq(char *a0, int a1);
extern void scpPlayPosSet(void *a0, float f12, float f13, float f14);
extern void scpPlayStart(int a0);
extern void scpPlayWaitMotEnd(char *a0);
extern int scpSearchGobj(int id);
extern void scpSekizou(char *self, int flag, int anim, int anim2, int kind, float bx, float by, float bz, float gx, float gy, float gz);
extern void scpSekizouCheckPoint(void);
extern void scpSetBoyWeaponGObj(int a0, int a1, int a2, int a3);
extern void scpSetCageVelocityFriction(float f12);
extern void scpSetStreamMotionRootOffset(int a0, float x, float y, float z);
extern void scpSleepEnemyAll(void);
extern void scpSleepEnemyOne(void);
extern void scpSleepSpiderGroupOne(void);
extern void scpSubAdpcmPlay(volatile int a0);
extern void scpTorchLightOff(void);
extern void scpTorchLightOn(void);
extern void scpTransGObj(void *a0, float f12, float f13, float f14);
extern int scpTriggerBall(char *obj, char *target, float r);
extern int scpTriggerFloorAttr(char *self, int attr);
extern int scpTriggerFloorAttrTargetMan(char *self, int attr);
extern int scpTriggerPosBall(float *pos, float *target, float r);
extern int scpTriggerPosBox(float *p, float *pos, float *size);
extern void scpUnLockMaxRotate(char *a0);
extern void scpWakeupEnemyAll(void);
extern void scpWakeupEnemyOne(void);
extern void scpWakeupItemWithBoundary(float x, float y, float z, float r);
extern void scpWakeupSpiderGroupOne(void);

#endif /* SCRIPT_H */
