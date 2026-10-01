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

/* The voice set manager: its slot count, the slot table and the level the
   decoders read (Init_ShockDriver clears it). */
typedef struct {
    int count;
    int *arr;
    int level;
} ShockMgr;

/* shockdriver.c's globals (MAIN.MAP's shockdriver.o names; ShockRequest is
   left out, pad.c has a type of that name). */
extern int ShockDriver[4];
extern ShockMgr *System_shock_driver;
extern char *ShockVoiceSetCommon;
extern char *ShockVoiceSetStage;
extern int ShockVoiceSetBuf[2];
extern int ShockRequestMemory[2];

void Init_Controler(short *a0);
void Init_Player(int *box);
void Init_Shock();
typedef struct ShockVoiceSet ShockVoiceSet;

void Init_ShockVoiceSet(ShockVoiceSet *set, int *data);
int *ShockRequestBox_EndRequestFree(int **a0);
int *ShockRequestBox_GetRequest(int **head_ptr, int key);
int ShockRequestBox_RequestCancel(int a0_, int a1);
int Shock_SetShockVoiceSet(int idx, int val);
int dumyAllocFunc(void);

void Vibration_SetDecodeData(void *a0, int a1, int a2, unsigned char a3, unsigned char a4);

#endif /* SHOCKDRIVER_H */
