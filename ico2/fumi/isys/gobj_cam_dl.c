#include "debug.h"
#include "gobj_cam_dl.h"
#include "isys.h"

static void add_gobj_to_tail(DLN *self, unsigned int key);

/* sorted insert by key, inlined into isysGObjMoveCameraDLHead and
   isysGObjLinkCameraDLHead */

static inline void insert_camera_dl_by_key(DLN *self, int key) /* derived name */
{
    DLN *head;
    DLN *tail;
    DLN *cur;
    DLN *next;

    self->key = key;
    head = gobj_camera_dl_link_head;
    if (head == 0) {
        gobj_camera_dl_link_tail = self;
        self->prev = 0;
        self->next = 0;
        gobj_camera_dl_link_head = self;
        return;
    }
    if ((unsigned int)head->key >= (unsigned int)key) {
        self->prev = 0;
        self->next = head;
        head->prev = self;
        gobj_camera_dl_link_head = self;
        return;
    }
    tail = gobj_camera_dl_link_tail;
    if ((unsigned int)tail->key < (unsigned int)key) {
        self->prev = tail;
        self->next = 0;
        tail->next = self;
        gobj_camera_dl_link_tail = self;
        return;
    }
    cur = head;
    next = cur->next;
    while ((unsigned int)next->key < (unsigned int)key) {
        cur = next;
        next = cur->next;
    }
    self->prev = cur;
    self->next = cur->next;
    cur->next = self;
    self->next->prev = self;
}

inline void isysGObjCameraDlInit(void)
{
    gobj_camera_dl_link_head = 0;
    gobj_camera_dl_link_tail = 0;
}

static void cut_gobj_camera_dl_link(DLN *gobj)
{
    if (gobj == 0) {
        debug_StdPrintfDummy("isys:null GObj\n");
        return;
    }
    if (gobj->prev == 0) {
        if (gobj->next == 0)
            goto head_check;
    } else {
        gobj->prev->next = gobj->next;
    }
    if (gobj->next != 0) {
        gobj->next->prev = gobj->prev;
    }
head_check:
    if (gobj == gobj_camera_dl_link_head) {
        gobj_camera_dl_link_head = gobj->next;
    }
    if (gobj == gobj_camera_dl_link_tail) {
        gobj_camera_dl_link_tail = gobj->prev;
    }
}

void isysGObjRemoveCameraDL(DLN *self)
{
    cut_gobj_camera_dl_link(self);
}

/* this list's own add_gobj_to_tail, as in isys/gobj */
static void add_gobj_to_tail(DLN *self, unsigned int key)
{
    DLN *head;
    DLN *tail;
    DLN *cur;

    debug_StdPrintfDummy("camera gop:%x\n", self);

    self->key = key;
    head = gobj_camera_dl_link_head;
    if (head == 0) {
        self->prev = 0;
        self->next = 0;
        gobj_camera_dl_link_head = self;
        gobj_camera_dl_link_tail = self;
        debug_StdPrintfDummy("first entry\n");
        return;
    }
    if (key < (unsigned int)head->key) {
        self->prev = 0;
        self->next = head;
        head->prev = self;
        gobj_camera_dl_link_head = self;
        debug_StdPrintfDummy("entry into head\n");
        return;
    }
    tail = gobj_camera_dl_link_tail;
    if (key >= (unsigned int)tail->key) {
        self->prev = tail;
        self->next = 0;
        tail->next = self;
        gobj_camera_dl_link_tail = self;
        debug_StdPrintfDummy("entry into tail\n");
        return;
    }

    cur = head;
    while (key >= (unsigned int)cur->next->key) {
        cur = cur->next;
    }

    self->prev = cur;
    self->next = cur->next;
    cur->next = self;
    self->next->prev = self;
}

inline void isysGObjLinkCameraDLHead(DLN *self, void *dl, int key, int kindMask, int drawMask)
{
    self->dl = dl;
    self->kindMask = kindMask;
    self->drawMask = drawMask;
    insert_camera_dl_by_key(self, key);
}

void isysGObjMoveCameraDL(DLN *self, int key)
{
    cut_gobj_camera_dl_link(self);
    return add_gobj_to_tail(self, key);
}

inline void isysGObjMoveCameraDLHead(DLN *self, int key)
{
    cut_gobj_camera_dl_link(self);
    insert_camera_dl_by_key(self, key);
}

inline void isysObjMoveCameraDLAfterGObj(DLN *self, DLN *obj)
{
    cut_gobj_camera_dl_link(self);
    self->id = obj->id;
    self->prev = obj;
    self->next = obj->next;
    obj->next = self;
    self->key = obj->key;
    if (self->next == 0) {
        gobj_camera_dl_link_tail = self;
    }
}

inline void isysObjMoveCameraDLBeforeGObj(DLN *self, DLN *obj)
{
    DLN *prev;
    cut_gobj_camera_dl_link(self);
    self->id = obj->id;
    prev = obj->prev;
    self->next = obj;
    self->prev = prev;
    obj->prev = self;
    self->key = obj->key;
    if (self->prev == 0) {
        gobj_camera_dl_link_head = self;
    }
}

void isysGObjLinkCameraDL(DLN *self, void *dl, int key, int kindMask, int drawMask)
{
    debug_StdPrintfDummy("LinkCameraDL in\n");
    self->dl = dl;
    self->kindMask = kindMask;
    self->drawMask = drawMask;
    add_gobj_to_tail(self, key);
    debug_StdPrintfDummy("LinkCameraDL out\n");
}

void isysGObjLinkCameraDLAfterGObj(DLN *self, void *dl, int kindMask, int drawMask, DLN *obj)
{
    register DLN *t1 = self;
    DLN *next;
    int key;
    if (obj == 0) {
        debug_StdPrintfDummy("isys:null GObj\n");
        return;
    }

    t1->kindMask = kindMask;
    t1->drawMask = drawMask;
    t1->dl = dl;
    t1->id = obj->id;
    t1->prev = obj;
    next = obj->next;
    key = obj->key;
    t1->next = next;
    obj->next = t1;
    t1->key = key;
    if (t1->next == 0) {
        gobj_camera_dl_link_tail = t1;
    }
}

void isysGObjLinkCameraDLBeforeGObj(DLN *self, void *dl, int kindMask, int drawMask, DLN *obj)
{
    register DLN *t1 = self;
    DLN *next;
    int key;
    if (obj == 0) {
        debug_StdPrintfDummy("isys:null GObj\n");
        return;
    }

    t1->kindMask = kindMask;
    t1->drawMask = drawMask;
    t1->dl = dl;
    t1->id = obj->id;
    t1->prev = obj;
    next = obj->next;
    key = obj->key;
    t1->next = next;
    obj->next = t1;
    t1->key = key;
    if (t1->next == 0) {
        gobj_camera_dl_link_tail = t1;
    }
}
