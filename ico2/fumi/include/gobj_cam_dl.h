/*
 * ico2/fumi/include/gobj_cam_dl.h
 *
 * The declarations of what gobj_cam_dl.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef GOBJ_CAM_DL_H
#define GOBJ_CAM_DL_H

typedef struct { /* field names derived */
    char pad0[52];
    void *dlNext;
    void *dlPrev;
    char pad3C[4];
    unsigned char dlLink;
    char pad41[3];
    int dlKey;
} AdpT; /* derived name */

/* gobj_cam_dl.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order). */
void isysGObjCameraDlInit(void);
void isysGObjMoveCameraDLHead(int a0, int a1);
void isysGObjLinkCameraDLHead(int *self, int a1, int key, int a3, int a4);
void isysObjMoveCameraDLAfterGObj(AdpT *a0, AdpT *a1);
void isysObjMoveCameraDLBeforeGObj(char *a0, char *a1);
void isysGObjLinkCameraDL(char *a0, int a1, int a2, int a3, int a4);

#endif /* GOBJ_CAM_DL_H */
