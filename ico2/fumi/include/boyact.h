/*
 * ico2/fumi/include/boyact.h
 *
 * The declarations of what boyact.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef BOYACT_H
#define BOYACT_H

#include "typedef.h"

/* boyact.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order). */
int CorrectStickInfo(void *dir, IosPadStick *stick);
void *GetBoyWeaponGObj(void);
void actBoyStand(GObj *volatile self);
void actBoyHang(GObj *volatile self);
void actBoyBHang(GObj *volatile self);
void actBoyFall(GObj *volatile self);
void actBoyCall(GObj *volatile self);
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
void actBoyItem(GObj *volatile self);
void actBoyItemAfter(GObj *volatile self);
void actBoyCliffHesitate(GObj *volatile self);
void actBoyHangBefore(GObj *volatile self);
void actBoyReadyMove(GObj *volatile self);
#else
void actBoyHangBefore(GObj *volatile self);
#endif
void actBoyBeslam(GObj *volatile self);
void actBoyRescueSrc(GObj *volatile self);
void actBoySupportGBBegin(GObj *volatile self);
void actBoySupportGBLoop(GObj *volatile self);
void actBoySupportGBEnd(GObj *volatile self);
void actBoySupportBGBegin(GObj *volatile self);
void actBoyDitch3mExec(GObj *volatile self);
void actBoyHangG3M(GObj *volatile self);
unsigned char IsAbleBoyControl(void);
void actBoyHand50(GObj *volatile self);
void afterBoyHand50(GObj *volatile self);
void actBoyHand100(GObj *volatile self);
void afterBoyHand100(GObj *volatile self);
void actBoyHand200(GObj *volatile self);
void afterBoyHand200(GObj *volatile self);
void ACTSearchEnemy(void *self, int *out_id, float *out_vec);
void DeleteBoyWeapon(void);
int isLiftBoyEnable(void);
#ifdef VERSION_AUG6

inline void BoyInfoUpdate_StageChange(void);
/* emitted here, after BoyInfoUpdate_StageChange (0x152A38; MAIN.MAP puts it in boyact.o) */
int ACTChkAttackIgnore_BOY(GObj *self);
#else
#ifndef VERSION_NTSC
void SetKidnapInfo(int enemyLabel, int targetLabel);
void GetKidnapInfo(int *enemyLabel, int *targetLabel);

inline void PrivInsCamSet(float *pos, float *tgt, struct GObj *track, int inFrames, int outFrames,
                          float inRate, float blend, unsigned char control);
#endif

inline void BoyInfoUpdate_StageChange(void);
#endif
int IsBoyStatus_EnemyMustWait(void);
int IsGirlEscortedInNextStage(void);
unsigned char IsGirlEscortedInCurrentStage(void);
int GetSaveSofaLayoutID(void);
void OnGirlEscortFlag(void);
#ifndef VERSION_AUG6
void SetBoyWeaponGObj(void *w);
#ifndef VERSION_NTSC
int IsBoyStatus_NotDanger(void);
#endif
#endif
int RequestStageChangeKidnapEnd(int stage, int targetId);
int GetEfStageCameraTargetID(void);
int IsBackFromEfStage(void);
#ifndef VERSION_NTSC
#ifndef VERSION_AUG6
inline int PrivInsCamChk(void);
#endif
inline unsigned char PrivInsCamChk_Control(void);
#endif
int *GetbufpCharacterPacket(void);
int GetsizeCharacterPacket(void);
void MakeCharacterPacket(void);
void ReadCharacterPacket(void);
void ACTSearchGObj(void *self, int kind, int maxDeg, int *out_id, float *out_vec, float thresh);
void afterBoySwim(GObj *volatile self);
void actBoyJump(GObj *volatile self);
inline void afterBoyTakeWeapon(GObj *volatile self);
#ifdef VERSION_AUG6
inline void afterCommonItem(GObj *volatile self);
inline void subBoyBrainMain(GObj *volatile self);
#else
#ifdef VERSION_NTSC
inline void afterCommonItem(GObj *volatile self);
#else
inline void afterBoyHangG3M(int x);
inline void afterBoyRescueGirlBhang(GObj *volatile self);
#endif
inline void subBoyBrainMain(int arg);
#endif
void SetBoyInfo(GObj *weapon, GObj *item);
void GetBoyRootPositionForCamera(float *out, struct GObj *gobj);
void Boy_Init(void);
#ifndef VERSION_AUG6
void ACTDispLwsBoyStonize_InQueenStage(void *self);
#endif
void SetStatusBoy_OtherStageGirlPinch(void);
void handoff_heroin(void);
/* boyact.o's .sdata globals: the two rope values and, last,
 * gopp_subBoyControl, the boy control thread. */
extern int test_rope_slope;
extern float add_rope_val;
extern void *gopp_subBoyControl;
/* boyact.o's last two .data globals, two quadwords. */
extern float test_rope_velo[4];
extern float add_rope_vec[4];

#endif /* BOYACT_H */
