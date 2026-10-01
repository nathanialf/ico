/*
 * ico2/fumi/include/gobj_dl.h
 *
 * The declarations of what gobj_dl.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef GOBJ_DL_H
#define GOBJ_DL_H

typedef struct DLN { /* field names derived */
    char pad0[0x34];
    struct DLN *next;
    struct DLN *prev;
    char pad3C[0x4];
    unsigned char id;
    char pad41[0x3];
    int key;
    void *dl; /* 0x48, the display function the object manager calls */
    char pad4C[0x4];
    int drawMask; /* 0x50, ANDed with the camera's mask to pick the cameras that draw it */
} DLN;            /* derived name */

/* gobj_dl.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order). */
void isysGObjDlInit(void);
void isysGObjMoveObjDLAfterGObj(DLN *self, DLN *obj);
void isysGObjMoveObjDLBeforeGObj(DLN *self, DLN *obj);
void isysGObjLinkObjDL(void *a0, void *a1, unsigned char a2, int a3, unsigned int a4);

#endif /* GOBJ_DL_H */
