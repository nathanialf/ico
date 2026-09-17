/*
 * ico2/fumi/include/act.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what act.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ACT_H
#define ACT_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order act.c's inline tail has. */
void actInitialize_geo(void *self);
int ACTReserveTarget(char *self, void *a1, int a2);
void _ACTRun(int n);
void _ACTWait(int a0);
void actCreateSubThreadGOppArg(int a0, int a1);
void actSetInterrupt(char *self, int val);
void ConvertStickToAbsCoord(void *a0, float *a1);
void ActSetStartBrainStatus(char *self, int status);
void actWaitCondition(int a0, int a1);

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order act.c's inline tail has. */

void ACTDebugMove(int a0, int a1);
void actChangeActBrain(int a0, int a1, int *a2);
void actChangeActMain(void *a0, void *a1, void **a2);
void actCreateMotionThread(void *a0, void *a1, void **a2);
int actCreateSubThread(void *a0, void *a1);
char *actInitialize(char *self);
void actInitialize_ext_charcter(char *self);
void actInitialize_only_charcter(char *self);

#endif /* ACT_H */
