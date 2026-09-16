/*
 * ico2/fumi/include/shockdriver.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what shockdriver.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef SHOCKDRIVER_H
#define SHOCKDRIVER_H

extern void Init_Controler(short *a0);
extern void Init_Player(int *box);
extern void Init_Shock();
extern void Init_ShockVoiceSet(int **a0, int *a1);
extern int *ShockRequestBox_EndRequestFree(int **a0);
extern int *ShockRequestBox_GetRequest(int **head_ptr, int key);
extern int ShockRequestBox_RequestCancel(int a0_, int a1);
extern int Shock_SetShockVoiceSet(int idx, int val);
extern int dumyAllocFunc(void);

#endif /* SHOCKDRIVER_H */
