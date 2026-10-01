/*
 * ico2/fumi/include/gobj_dl.h
 *
 * The declarations of what gobj_dl.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef GOBJ_DL_H
#define GOBJ_DL_H

/* The display lists link game objects through GObj + 0x34 (typedef.h). */
struct GObj;

/* gobj_dl.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order). */
void isysGObjDlInit(void);
void isysGObjMoveObjDLAfterGObj(struct GObj *self, struct GObj *obj);
void isysGObjMoveObjDLBeforeGObj(struct GObj *self, struct GObj *obj);
void isysGObjLinkObjDL(void *self, void *dl, unsigned char kind, int key, unsigned int drawMask);

#endif /* GOBJ_DL_H */
