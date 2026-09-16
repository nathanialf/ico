/*
 * ico2/omori/include/brain.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what brain.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef BRAIN_H
#define BRAIN_H

extern void OverrideBrainStatusByGObj(int *b, void *gobj, float f8, float f10, float fC);
extern void brainAddLevelGirl(float lv);
extern int brainCheckView(int *a0, int *a1);
extern void brainClsTargetLevel();
extern void brainInit(void);
extern void brainInitGirlSet(void *a0, int a1);
extern void brainLockGirl(void);
extern void brainSetLevelGop(int gobj, int a1, int a2, float lv);
extern void brainSetSpMode(void);
extern void brainStatusDefaultSet(void *b, int gobj, int idx);
extern void brainSubLevelGop(void *gobj, float lv);
extern void brainUnlockGirl(void);

#endif /* BRAIN_H */
