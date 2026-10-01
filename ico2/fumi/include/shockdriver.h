/*
 * ico2/fumi/include/shockdriver.h
 *
 * The declarations of what shockdriver.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef SHOCKDRIVER_H
#define SHOCKDRIVER_H

struct SHOCKREQUEST;

/* The voice set manager: its slot count, the slot table and the hook the
   decoders call on a 0x3F command (Init_ShockDriver clears it). */
typedef struct { /* field names derived */
    int count;
    int *arr;
    void (*callback)(struct SHOCKREQUEST *req, unsigned char *cmd);
} ShockMgr; /* derived name */

/* shockdriver.c's globals (ShockRequest is left out: pad.c has a type of that
   name). */
extern int ShockDriver[4];
extern ShockMgr *System_shock_driver;
extern char *ShockVoiceSetCommon;
extern char *ShockVoiceSetStage;
extern int ShockVoiceSetBuf[2];
extern int ShockRequestMemory[2];

void Init_Controler(short *motor);
void Init_Player(int *box);
void Init_Shock(void);
typedef struct ShockVoiceSet ShockVoiceSet; /* derived name */

void Init_ShockVoiceSet(ShockVoiceSet *set, int *data);
int *ShockRequestBox_EndRequestFree(int **box);
int *ShockRequestBox_GetRequest(int **head_ptr, int key);
int ShockRequestBox_RequestCancel(int boxp, int key);
int Shock_SetShockVoiceSet(int idx, int val);
int dumyAllocFunc(void);

void Vibration_SetDecodeData(void *req, int shot, int wave, unsigned char b2, unsigned char b3);

#endif /* SHOCKDRIVER_H */
