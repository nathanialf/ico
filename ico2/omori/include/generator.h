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

int CheckGeneratorCollision(char *gobj, float *dir);
char *DirectCallEnemy(char *gobj, char *mother, float *pos, float *dir, int a4);
void Generator_Call(char *a0);
void Generator_Delete(void *a0);
void Generator_Init(void);
void Generator_Mask(char *a0);
void Generator_MaskOff(char *a0);
void Generator_QuickCall(char *gobj);
void Generator_ResetCount(char *a0);
void GetGeneratorSafePosition(float *dst, char *gobj);
int GetMotherGenerator(int label);
int *GetbufpGeneratorPacket(void);
int GetsizeGeneratorPacket(void);
char *IsNeedGeneratorHard(char *mother);
int IsOpenGenerator(char *gobj);
void LockEnemyGenerate(int *self);
void MakeGeneratorPacket(void);
void ReadGeneratorPacket(void);
void RestoreReviveCount(char *gobj);
void SetInfoSpKidnapEnemy(void);
void SetInfoSpKidnapGenerator(short *a0);
void UnlockEnemyGenerate(void *a0);
void endfunc_BGA(char *gobj);

#endif /* GENERATOR_H */
