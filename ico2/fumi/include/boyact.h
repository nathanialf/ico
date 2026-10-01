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
int CorrectStickInfo(void *dir, void *stick);
void *GetBoyWeaponGObj(void);
void actBoyStand(GObj *volatile a0);
void actBoyHang(GObj *volatile a0);
void actBoyBHang(GObj *volatile a0);
void actBoyFall(GObj *volatile a0);
void actBoyCall(GObj *volatile a0);
void actBoyHangBefore(GObj *volatile a0);
void actBoyBeslam(GObj *volatile a0);
void actBoyRescueSrc(GObj *volatile a0);
void actBoySupportGBBegin(GObj *volatile a0);
void actBoySupportGBLoop(GObj *volatile a0);
void actBoySupportGBEnd(GObj *volatile a0);
void actBoySupportBGBegin(GObj *volatile a0);
void actBoyDitch3mExec(GObj *volatile a0);
void actBoyHangG3M(GObj *volatile a0);
unsigned char IsAbleBoyControl(void);
void actBoyHand50(GObj *volatile a0);
void afterBoyHand50(GObj *volatile a0);
void actBoyHand100(GObj *volatile a0);
void afterBoyHand100(GObj *volatile a0);
void actBoyHand200(GObj *volatile a0);
void afterBoyHand200(GObj *volatile a0);
void ACTSearchEnemy(void *a0, int *out_id, float *out_vec);
void DeleteBoyWeapon(void);
int isLiftBoyEnable(void);
void SetKidnapInfo(int a0, int a1);
void GetKidnapInfo(int *a0, int *a1);

inline void PrivInsCamSet(float *pos, float *tgt, int a2, int a3, int a4, float f5, float f6,
                   unsigned char a7);

inline void BoyInfoUpdate_StageChange(void);
int IsBoyStatus_EnemyMustWait(void);
int IsGirlEscortedInNextStage(void);
unsigned char IsGirlEscortedInCurrentStage(void);
int GetSaveSofaLayoutID(void);
void OnGirlEscortFlag(void);
void SetBoyWeaponGObj(void *w);
int IsBoyStatus_NotDanger(void);
int RequestStageChangeKidnapEnd(void *a0, int a1);
int GetEfStageCameraTargetID(void);
int IsBackFromEfStage(void);
inline int PrivInsCamChk(void);
inline unsigned char PrivInsCamChk_Control(void);
int *GetbufpCharacterPacket(void);
int GetsizeCharacterPacket(void);
void MakeCharacterPacket(void);
void ReadCharacterPacket(void);
void ACTSearchGObj(void *a0, int a1, int a2, int *out_id, float *out_vec, float thresh);
void afterBoySwim(GObj *volatile a0);
void actBoyJump(GObj *volatile a0);
inline void afterBoyTakeWeapon(GObj *volatile a0);
inline void afterBoyHangG3M(int x);
inline void afterBoyRescueGirlBhang(GObj *volatile a0);
inline void subBoyBrainMain(int a0);
void SetBoyInfo(int *a0, int *a1);
void GetBoyRootPositionForCamera(float *out, struct GObj *gobj);
void Boy_Init(void);
void ACTDispLwsBoyStonize_InQueenStage(void *self);
void BoyBgaManager(void *self, int id, void *dst);
void PutWeapon(void);
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
