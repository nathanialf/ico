/*
 * ico2/sugipon/include/handManager.h
 *
 * The declarations of what handManager.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef HANDMANAGER_H
#define HANDMANAGER_H

/* motion-ik-eff-def: one hand IK mode, 0x10 bytes, indexed by a nibble of
 * MotionRec's modeBits. Readers: ico2/sugipon/src/handManager.c (the vec
 * _handManager takes), ico2/fumi/src/act-game.c (HandModeRow). */
typedef struct {  /* field names derived */
    float dir[3]; /* 0x00 */
    int mode;     /* 0x0C */
} HandModeRow;    /* derived name */

struct GObj;

void HandManager(struct GObj *obj);

#endif /* HANDMANAGER_H */
