/*
 * ico2/sugipon/include/boy.h
 *
 * The declarations of what boy.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef BOY_H
#define BOY_H

struct GObj;

#if !defined(VERSION_AUG6) && !defined(VERSION_JUN26)
/* unmapped_00533FC0: one girl-to-boy motion pair, 8 bytes: the girl's
   motion and the boy's that synchronizeMotionOutputOriginForGirl keeps in
   step with it. */
typedef struct { /* field names derived */
    int girl;    /* 0x00 */
    int boy;     /* 0x04 */
} MotSyncPair;   /* derived name */

extern MotSyncPair motSyncPairs[]; /* derived name */
#endif

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order boy.c's inline tail has. */
struct LightLineExt;

extern struct LightLineExt *llExtGeo;

#ifdef VERSION_JUN26
void LightLineGeo(void);
#else
void SelectBoyCrown(struct GObj *self, int crown);
void LightLineGeo(void);
void SetBoyStonizedVisual(struct GObj *self);
#endif

#endif /* BOY_H */
