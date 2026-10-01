/*
 * ico2/fumi/include/boyact.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what boyact.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef BOYACT_H
#define BOYACT_H

/* boyact.c defines these `inline`, so the compiler emits them after the
 * rest of the file in the order they are first declared: this list is the
 * ROM's order of the TU's closing run, from CorrectStickInfo to Boy_Init. */
int CorrectStickInfo(void *dir, void *stick);
void *GetBoyWeaponGObj(void);
void actBoyStand(volatile int a0);
void actBoyHang(volatile int a0);
void actBoyBHang(volatile int a0);
void actBoyFall(volatile int a0);
void actBoyCall(volatile int a0);
void actBoyHangBefore(volatile int a0);
void actBoyBeslam(volatile int a0);
void actBoyRescueSrc(volatile int a0);
void actBoySupportGBBegin(volatile int a0);
void actBoySupportGBLoop(volatile int a0);
void actBoySupportGBEnd(volatile int a0);
void actBoySupportBGBegin(volatile int a0);
void actBoyDitch3mExec(volatile int a0);
void actBoyHangG3M(volatile int a0);
unsigned char IsAbleBoyControl(void);
void actBoyHand50(volatile int a0);
void afterBoyHand50(volatile int a0);
void actBoyHand100(volatile int a0);
void afterBoyHand100(volatile int a0);
void actBoyHand200(volatile int a0);
void afterBoyHand200(volatile int a0);
void ACTSearchEnemy(void *a0, int *out_id, float *out_vec);
void DeleteBoyWeapon(void);
int isLiftBoyEnable(void);
void SetKidnapInfo(int a0, int a1);
void GetKidnapInfo(int *a0, int *a1);
void PrivInsCamSet(float *pos, float *tgt, int a2, int a3, int a4, float f5, float f6, unsigned char a7);
void BoyInfoUpdate_StageChange(void);
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
int PrivInsCamChk(void);
unsigned char PrivInsCamChk_Control(void);
int *GetbufpCharacterPacket(void);
int GetsizeCharacterPacket(void);
void MakeCharacterPacket(void);
void ReadCharacterPacket(void);
void ACTSearchGObj(void *a0, int a1, int a2, int *out_id, float *out_vec, float thresh);
void afterBoySwim(volatile int a0);
void actBoyJump(volatile int a0);
void afterBoyTakeWeapon(volatile int a0);
void afterBoyHangG3M(int x);
void afterBoyRescueGirlBhang(volatile int a0);
void subBoyBrainMain(int a0);
void SetBoyInfo(int *a0, int *a1);
void GetBoyRootPositionForCamera(float *out);
void Boy_Init(void);

void ACTDispLwsBoyStonize_InQueenStage(void *self);
void BoyBgaManager(void *self, int id, void *dst);
void PutWeapon(void);
void SetStatusBoy_OtherStageGirlPinch(void);
void handoff_heroin(void);

/* MAIN.MAP globals of boyact.o's .sdata: the two rope values in place and
 * gopp_subBoyControl, the boy control thread, the run's last word. */
extern int test_rope_slope;
extern float add_rope_val;
extern void *gopp_subBoyControl;

/* MAIN.MAP globals of boyact.o's .data, the run's last two quadwords. */
extern float test_rope_velo[4];
extern float add_rope_vec[4];

#endif /* BOYACT_H */
