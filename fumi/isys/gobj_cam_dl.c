#include "common.h"

extern void debug_assertMessage();
extern char D_006137A0[];
extern char D_006137B0[];
extern char D_006137C0[];
extern char D_006137D8[];
extern int *D_0062A4D4;
extern int *D_0062A4D8;

void cut_gobj_camera_dl_link(int a0, int a1)
{
    int *self = (int *)a0;
    int key = a1;
    int *head;
    int *tail;
    int *cur;

    debug_assertMessage(D_006137A0, self);
    self[0x11] = key;
    head = D_0062A4D4;
    if (head == 0) {
        self[0xE] = 0;
        self[0xD] = 0;
        D_0062A4D4 = self;
        D_0062A4D8 = self;
        debug_assertMessage(D_006137B0);
        return;
    }
    if ((unsigned int)key < (unsigned int)head[0x11]) {
        self[0xE] = 0;
        self[0xD] = (int)head;
        head[0xE] = (int)self;
        D_0062A4D4 = self;
        debug_assertMessage(D_006137C0);
        return;
    }
    tail = D_0062A4D8;
    if ((unsigned int)key >= (unsigned int)tail[0x11]) {
        self[0xE] = (int)tail;
        self[0xD] = 0;
        tail[0xD] = (int)self;
        D_0062A4D8 = self;
        debug_assertMessage(D_006137D8);
        return;
    }
    cur = head;
    while ((unsigned int)key >= (unsigned int)((int *)cur[0xD])[0x11]) {
        cur = (int *)cur[0xD];
    }
    self[0xE] = (int)cur;
    self[0xD] = cur[0xD];
    cur[0xD] = (int)self;
    ((int *)self[0xD])[0xE] = (int)self;
}

extern void func_001F8C30();
extern void cut_gobj_camera_dl_link(int a0, int a1);

void isysGObjRemoveCameraDL(int a0, int a1)
{
    func_001F8C30(a0);
    return cut_gobj_camera_dl_link(a0, a1);
}

extern void debug_assertMessage();

extern char D_006137F0[];

extern char D_00613808[];

void func_001F8E08(char *self, int a1, int a2, int a3, int a4)
{
    debug_assertMessage(D_006137F0);
    *(int *)(self + 0x48) = a1;
    *(int *)(self + 0x4C) = a3;
    *(int *)(self + 0x50) = a4;
    cut_gobj_camera_dl_link((int)self, a2);
    debug_assertMessage(D_00613808);
}

extern int *D_0062A4D8;

extern char D_00613790[];

void isysGObjMoveCameraDL(int *self, int a1, int a2, int a3, int *t0)
{
    register int *t1 = self;
    int v34, v44;
    if (t0 == 0) {
        debug_assertMessage(D_00613790);
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
        D_0062A4D8 = t1;
    }
}

void isysGObjLinkCameraDL(int *self, int a1, int a2, int a3, int *t0)
{
    register int *t1 = self;
    int v34, v44;
    if (t0 == 0) {
        debug_assertMessage(D_00613790);
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
        D_0062A4D8 = t1;
    }
}

extern int *D_0062A4D4;

void isysGObjLinkCameraDLAfterGObj(void) {
    D_0062A4D4 = 0;
    D_0062A4D8 = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj_cam_dl", isysGObjLinkCameraDLBeforeGObj);
