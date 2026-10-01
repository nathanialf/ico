/*
 * ico2/sugipon/include/sugiTree.h
 *
 * The declarations of what sugiTree.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef SUGITREE_H
#define SUGITREE_H

struct GObj;

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order sugiTree.c's inline tail has. */
short *InitSugiLeafGeo(void);
void SugiLeafGeo(struct GObj *gobj);
short *InitSugiLeafGeo2(struct GObj *gobj);
void SugiLeafGeo2(struct GObj *gobj);
void SugiLeafDL2(struct GObj *gobj);

#endif /* SUGITREE_H */
