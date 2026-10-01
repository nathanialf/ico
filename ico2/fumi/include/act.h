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

struct GObj;

struct Act;

struct GProc;

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order act.c's inline tail has. */
void actInitialize_geo(void *self);
int ACTReserveTarget(struct GObj *self, void *a1, int a2);
void _ACTRun(int n);
void _ACTWait(int a0);
void actCreateSubThreadGOppArg(void (*fn)(), int pri);
void actSetInterrupt(char *self, int val);
void ConvertStickToAbsCoord(void *a0, float *a1);
void ActSetStartBrainStatus(struct GObj *self, int status);
void actWaitCondition(int a0, int a1);

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order act.c's inline tail has. */

void ACTDebugMove(int a0, int a1);
void actChangeActBrain(struct GObj *self, void (*fn)(), struct GProc **slot);
void actChangeActMain(struct GObj *self, void (*fn)(), struct GProc **slot);
void actCreateMotionThread(void (*fn)(), int pri, struct GProc **slot);
struct GProc *actCreateSubThread(void (*fn)(), int pri);
struct Act *actInitialize(struct GObj *self);
void actInitialize_ext_charcter(char *self);
void actInitialize_only_charcter(char *self);

/* act-mode-def: one act mode, 0x50 bytes, indexed by Act+0x34. Readers:
 * ico2/fumi/src/act.c (StatusAttrAct: the act per actor kind, the mail, the
 * intr-list start, the flag bits), commonact.c (CarryRec: name, flags).
 * Owner: ico2/fumi/include/act.h. */
typedef struct { /* field names derived */

    struct {
        void (*act)(); /* +0x00, the mode's act function */
        int word4;     /* +0x04, compared across a mode change */
        int word8;     /* +0x08 */
    } ent[3];          /* 0x00, one per actor kind (Act+0x48) */

    char name[32];      /* 0x24, the debug name */
    int intrList;       /* 0x44, the first actIntrList row */
    int mail;           /* 0x48, ACTSendMailCorrect's mail */
    unsigned int flags; /* 0x4C */
} ActModeRec;           /* derived name */

#endif /* ACT_H */
