/*
 * ico2/sugipon/include/handManager.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what handManager.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef HANDMANAGER_H
#define HANDMANAGER_H

/* motion-ik-eff-def: one hand IK mode, 0x10 bytes, indexed by a nibble of
 * MotionRec's modeBits. Readers: ico2/sugipon/src/handManager.c (the vec
 * _handManager takes), ico2/fumi/src/act-game.c (HandModeRow). */
typedef struct {  /* field names derived */
    float dir[3]; /* 0x00 */
    int mode;     /* 0x0C */
} HandModeRow;

struct GObj;

void HandManager(struct GObj *obj);
float _handManager(struct GObj *obj, char *hw, char *vec, char *ref, int node);
void connectToTarget(struct GObj *obj, char *hw, int na, int nb, int nc);

#endif /* HANDMANAGER_H */
