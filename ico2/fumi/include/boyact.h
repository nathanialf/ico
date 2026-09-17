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

void ACTDispLwsBoyStonize_InQueenStage(void *self);
void ACTSearchEnemy(void *a0, int *out_id, float *out_vec);
void ACTSearchGObj(void *a0, int a1, int a2, int *out_id, float *out_vec, float thresh);
void BoyBgaManager(void *self, int id, void *dst);
void BoyInfoUpdate_StageChange(void);
void Boy_Init(void);
int CorrectStickInfo(void *dir, void *stick);
void DeleteBoyWeapon(void);
void GetBoyRootPositionForCamera(float *out);
void *GetBoyWeaponGObj(void);
int GetEfStageCameraTargetID(void);
void GetKidnapInfo(int *a0, int *a1);
int *GetbufpCharacterPacket(void);
int GetsizeCharacterPacket(void);
unsigned char IsAbleBoyControl(void);
int IsBoyStatus_EnemyMustWait(void);
int IsBoyStatus_NotDanger(void);
unsigned char IsGirlEscortedInCurrentStage(void);
int IsGirlEscortedInNextStage(void);
void MakeCharacterPacket(void);
void OnGirlEscortFlag(void);
void PrivInsCamSet(float *pos, float *tgt, int a2, int a3, int a4, float f5, float f6, unsigned char a7);
void PutWeapon(void);
void ReadCharacterPacket(void);
int RequestStageChangeKidnapEnd(void *a0, int a1);
void SetBoyInfo(int *a0, int *a1);
void SetBoyWeaponGObj(void *w);
void SetKidnapInfo(int a0, int a1);
void SetStatusBoy_OtherStageGirlPinch(void);
void afterBoyHand100(volatile int a0);
void afterBoyHand200(volatile int a0);
void afterBoyHand50(volatile int a0);
void afterBoyHangG3M(int x);
void afterBoyRescueGirlBhang(volatile int a0);
void afterBoyTakeWeapon(volatile int a0);
void handoff_heroin(void);

#endif /* BOYACT_H */
