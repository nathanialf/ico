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

extern void ACTDispLwsBoyStonize_InQueenStage(void *self);
extern void ACTSearchEnemy(void *a0, int *out_id, float *out_vec);
extern void ACTSearchGObj(void *a0, int a1, int a2, int *out_id, float *out_vec, float thresh);
extern void BoyBgaManager(void *self, int id, void *dst);
extern void BoyInfoUpdate_StageChange(void);
extern void Boy_Init(void);
extern void CorrectStickInfo(int a0);
extern void DeleteBoyWeapon(void);
extern void GetBoyRootPositionForCamera(float *out);
extern void *GetBoyWeaponGObj(void);
extern int GetEfStageCameraTargetID(void);
extern void GetKidnapInfo(int *a0, int *a1);
extern int *GetbufpCharacterPacket(void);
extern int GetsizeCharacterPacket(void);
extern unsigned char IsAbleBoyControl(void);
extern int IsBoyStatus_EnemyMustWait(void);
extern int IsBoyStatus_NotDanger(void);
extern unsigned char IsGirlEscortedInCurrentStage(void);
extern int IsGirlEscortedInNextStage(void);
extern void MakeCharacterPacket(void);
extern void OnGirlEscortFlag(void);
extern void PrivInsCamSet(float *pos, float *tgt, int a2, int a3, int a4, float f5, float f6, unsigned char a7);
extern void PutWeapon(void);
extern void ReadCharacterPacket(void);
extern int RequestStageChangeKidnapEnd(void *a0, int a1);
extern void SetBoyInfo(int *a0, int *a1);
extern void SetBoyWeaponGObj(void *w);
extern void SetKidnapInfo(int a0, int a1);
extern void SetStatusBoy_OtherStageGirlPinch(void);
extern void afterBoyHand100(volatile int a0);
extern void afterBoyHand200(volatile int a0);
extern void afterBoyHand50(volatile int a0);
extern void afterBoyHangG3M(int x);
extern void afterBoyRescueGirlBhang(volatile int a0);
extern void afterBoyTakeWeapon(volatile int a0);
extern void handoff_heroin(void);

#endif /* BOYACT_H */
