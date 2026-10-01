/*
 * ico2/fumi/include/gobj_cam_dl.h
 *
 * The declarations of what gobj_cam_dl.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef GOBJ_CAM_DL_H
#define GOBJ_CAM_DL_H

#include "gobj_dl.h"

/* gobj_cam_dl.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order). */
void isysGObjCameraDlInit(void);
void isysGObjMoveCameraDLHead(struct GObj *self, int key);
void isysGObjLinkCameraDLHead(struct GObj *self, void *dl, int key, int kindMask, int drawMask);
void isysObjMoveCameraDLAfterGObj(struct GObj *self, struct GObj *obj);
void isysObjMoveCameraDLBeforeGObj(struct GObj *self, struct GObj *obj);
void isysGObjLinkCameraDL(struct GObj *self, void *dl, int key, int kindMask, unsigned int drawMask);

#endif /* GOBJ_CAM_DL_H */
