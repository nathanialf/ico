/*
 * ico2/omori/include/generator.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what generator.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef GENERATOR_H
#define GENERATOR_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order generator.c's inline tail has. */
char *InitGeneratorGeo(char *gobj, char *src);
void Generator_Call(char *a0);
void Generator_ResetCount(char *a0);
void Generator_Mask(char *a0);
void Generator_MaskOff(char *a0);
void SetMotherGenerator(int no, int label);
void Generator_Init(void);
int *GetbufpGeneratorPacket(void);
int GetsizeGeneratorPacket(void);
int RestoreGeneratorGeo(float *dst, float *src);
int RestoreGeneratorExtGeo(char *a0, short *a1);
int MemoryGenerator(short *a0, char *a1);
void *IsEnableCallEnemy(char *self);
char *DirectCallEnemy(char *gobj, char *mother, float *pos, float *dir, int a4);
void LockEnemyGenerate(int *self);
void UnlockEnemyGenerate(void *a0);
void RestoreReviveCount(char *gobj);
void ReturnEnemyToGenerator(int a0);
int GeneratorWorkEnd(char *a0);
int SearchActiveGenerator(void);
void ResetReviveCountEnemy(int a0);
void SetInfoSpKidnapGenerator(short *a0);
void SetInfoSpKidnapEnemy(void);
int IsOpenGenerator(char *gobj);
int IsEnableCallEnemyByTargetGObj(void *a0);

int CheckGeneratorCollision(char *gobj, float *dir);
void Generator_Delete(void *a0);
void Generator_QuickCall(char *gobj);
void GetGeneratorSafePosition(float *dst, char *gobj);
int GetMotherGenerator(int label);
/* K&R, unprototyped on purpose: generator.c defines it with one parameter and
   calls it with none at its own line 196, so only this form serves both. */
char *IsNeedGeneratorHard();
void MakeGeneratorPacket(void);
void ReadGeneratorPacket(void);
void endfunc_BGA(char *gobj);

#endif /* GENERATOR_H */
