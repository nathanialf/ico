/*
 * ico2/sugipon/include/boy.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what boy.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef BOY_H
#define BOY_H

struct GObj;

/* unmapped_00533FC0: one girl-to-boy motion pair, 8 bytes: the girl's
   motion and the boy's that synchronizeMotionOutputOriginForGirl keeps in
   step with it. */
typedef struct { /* field names derived */
    int girl;    /* 0x00 */
    int boy;     /* 0x04 */
} MotSyncPair;

extern MotSyncPair motSyncPairs[]; /* derived name */

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order boy.c's inline tail has. */
struct LightLineExt;

extern struct LightLineExt *llExtGeo;
void SelectBoyCrown(struct GObj *a0, int a1);
void LightLineGeo(void);
void SetBoyStonizedVisual(struct GObj *a0);

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order boy.c's inline tail has. */

#endif /* BOY_H */
