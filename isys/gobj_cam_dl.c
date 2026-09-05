#include "common.h"

typedef struct EnNode { char pad[0x34]; struct EnNode *next; struct EnNode *prev; } EnNode;
typedef struct { char p[0x34]; void *f34; void *f38; char p2[4]; unsigned char f40; char p3[3]; int f44; } AdpT;
extern char D_00621970[];
extern int *D_0063A614;
extern AdpT *D_0063A618;
extern void debug_StdPrintfDummy();
extern int func_0020BFD8();
extern char D_006219D0[];
extern char D_006219E8[];
/* listing lines 130-165: sorted insert by key, inlined into
   isysGObjMoveCameraDLHead and isysGObjLinkCameraDLHead */
/* prototypes: their order is the inline tail's emission order */
void isysGObjCameraDlInit(void);
void isysGObjMoveCameraDLHead(int a0, int a1);
void isysGObjLinkCameraDLHead(int *self, int a1, int key, int a3, int a4);
void isysObjMoveCameraDLAfterGObj(AdpT *a0, AdpT *a1);
void isysObjMoveCameraDLBeforeGObj(char *a0, char *a1);
static inline void insert_camera_dl_by_key(int *self, int key)
{
    int *head;
    int *tail;
    int *cur;
    int *next;

    self[0x11] = key;
    head = D_0063A614;
    if (head == 0) {
        *(int *)&D_0063A618 = (int)self;
        self[0xE] = 0;
        self[0xD] = 0;
        *(int *)&D_0063A614 = (int)self;
        return;
    }
    if ((unsigned int)head[0x11] >= (unsigned int)key) {
        self[0xE] = 0;
        self[0xD] = (int)head;
        head[0xE] = (int)self;
        D_0063A614 = self;
        return;
    }
    tail = (int *)D_0063A618;
    if ((unsigned int)tail[0x11] < (unsigned int)key) {
        self[0xE] = (int)tail;
        self[0xD] = 0;
        tail[0xD] = (int)self;
        D_0063A618 = (AdpT *)self;
        return;
    }
    cur = head;
    next = (int *)cur[0xD];
    while ((unsigned int)next[0x11] < (unsigned int)key) {
        cur = next;
        next = (int *)cur[0xD];
    }
    self[0xE] = (int)cur;
    self[0xD] = cur[0xD];
    cur[0xD] = (int)self;
    ((int *)self[0xD])[0xE] = (int)self;
}
inline void isysGObjCameraDlInit(void) {
    D_0063A614 = 0;
    D_0063A618 = 0;
}
void cut_gobj_camera_dl_link(EnNode *gobj)
{
    if (gobj == 0) {
        debug_StdPrintfDummy(D_00621970);
        return;
    }
    if (gobj->prev == 0) {
        if (gobj->next == 0) goto head_check;
    } else {
        gobj->prev->next = gobj->next;
    }
    if (gobj->next != 0) {
        gobj->next->prev = gobj->prev;
    }
head_check:
    if (gobj == (EnNode *)D_0063A614) {
        D_0063A614 = (int *)gobj->next;
    }
    if (gobj == (EnNode *)D_0063A618) {
        D_0063A618 = (AdpT *)gobj->prev;
    }
}
void isysGObjRemoveCameraDL(void *a0)
{
    cut_gobj_camera_dl_link((EnNode *)a0);
}
INCLUDE_ASM("asm/nonmatchings/isys/gobj_cam_dl", func_0020BFD8);
inline void isysGObjLinkCameraDLHead(int *self, int a1, int key, int a3, int a4)
{
    self[0x12] = a1;
    self[0x13] = a3;
    self[0x14] = a4;
    insert_camera_dl_by_key(self, key);
}
void isysGObjMoveCameraDL(int a0, int a1)
{
    cut_gobj_camera_dl_link((EnNode *)a0);
    return func_0020BFD8(a0, a1);
}
inline void isysGObjMoveCameraDLHead(int a0, int a1)
{
    cut_gobj_camera_dl_link((EnNode *)a0);
    insert_camera_dl_by_key((int *)a0, a1);
}
inline void isysObjMoveCameraDLAfterGObj(AdpT *a0, AdpT *a1) {
    cut_gobj_camera_dl_link((EnNode *)a0);
    a0->f40 = a1->f40;
    a0->f38 = a1;
    a0->f34 = a1->f34;
    a1->f34 = a0;
    a0->f44 = a1->f44;
    if (a0->f34 == 0) {
        D_0063A618 = a0;
    }
}
inline void isysObjMoveCameraDLBeforeGObj(char *a0, char *a1) {
    int next;
    cut_gobj_camera_dl_link((EnNode *)a0);
    *(unsigned char *)(a0 + 0x40) = *(unsigned char *)(a1 + 0x40);
    next = *(int *)(a1 + 0x38);
    *(int *)(a0 + 0x34) = (int)a1;
    *(int *)(a0 + 0x38) = next;
    *(int *)(a1 + 0x38) = (int)a0;
    *(int *)(a0 + 0x44) = *(int *)(a1 + 0x44);
    if (*(int *)(a0 + 0x38) == 0) {
        D_0063A614 = (int *)a0;
    }
}
void isysGObjLinkCameraDL(char *a0, int a1, int a2, int a3, int a4) {
    debug_StdPrintfDummy(D_006219D0);
    *(int *)(a0 + 0x48) = a1;
    *(int *)(a0 + 0x4C) = a3;
    *(int *)(a0 + 0x50) = a4;
    func_0020BFD8(a0, a2);
    debug_StdPrintfDummy(D_006219E8);
}
void isysGObjLinkCameraDLAfterGObj(int *self, int a1, int a2, int a3, int *t0)
{
    register int *t1 = self;
    int v34, v44;
    if (t0 == 0) {
        debug_StdPrintfDummy(D_00621970);
        return;
    }

    t1[0x13] = a2;
    t1[0x14] = a3;
    t1[0x12] = a1;
    *((unsigned char *)t1 + 0x40) = *((unsigned char *)t0 + 0x40);
    t1[0xE] = (int)t0;
    v34 = t0[0xD];
    v44 = t0[0x11];
    t1[0xD] = v34;
    t0[0xD] = (int)t1;
    t1[0x11] = v44;
    if (t1[0xD] == 0) {
        D_0063A618 = (AdpT *)t1;
    }
}
void isysGObjLinkCameraDLBeforeGObj(int *self, int a1, int a2, int a3, int *t0)
{
    register int *t1 = self;
    int v34, v44;
    if (t0 == 0) {
        debug_StdPrintfDummy(D_00621970);
        return;
    }

    t1[0x13] = a2;
    t1[0x14] = a3;
    t1[0x12] = a1;
    *((unsigned char *)t1 + 0x40) = *((unsigned char *)t0 + 0x40);
    t1[0xE] = (int)t0;
    v34 = t0[0xD];
    v44 = t0[0x11];
    t1[0xD] = v34;
    t0[0xD] = (int)t1;
    t1[0x11] = v44;
    if (t1[0xD] == 0) {
        D_0063A618 = (AdpT *)t1;
    }
}
