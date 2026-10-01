#include "debug.h"
#include "gobj_cam_dl.h"
#include "isys.h"

static void add_gobj_to_tail(GObj *self, unsigned int key);

/* sorted insert by key, inlined into isysGObjMoveCameraDLHead and
   isysGObjLinkCameraDLHead */

static inline void insert_camera_dl_by_key(GObj *self, int key) /* derived name */
{
    GObj *head;
    GObj *tail;
    GObj *cur;
    GObj *next;

    self->dlKey = key;
    head = gobj_camera_dl_link_head;
    if (head == 0) {
        gobj_camera_dl_link_tail = self;
        self->dlPrev = 0;
        self->dlNext = 0;
        gobj_camera_dl_link_head = self;
        return;
    }
    if ((unsigned int)head->dlKey >= (unsigned int)key) {
        self->dlPrev = 0;
        self->dlNext = head;
        head->dlPrev = self;
        gobj_camera_dl_link_head = self;
        return;
    }
    tail = gobj_camera_dl_link_tail;
    if ((unsigned int)tail->dlKey < (unsigned int)key) {
        self->dlPrev = tail;
        self->dlNext = 0;
        tail->dlNext = self;
        gobj_camera_dl_link_tail = self;
        return;
    }
    cur = head;
    next = cur->dlNext;
    while ((unsigned int)next->dlKey < (unsigned int)key) {
        cur = next;
        next = cur->dlNext;
    }
    self->dlPrev = cur;
    self->dlNext = cur->dlNext;
    cur->dlNext = self;
    self->dlNext->dlPrev = self;
}

inline void isysGObjCameraDlInit(void)
{
    gobj_camera_dl_link_head = 0;
    gobj_camera_dl_link_tail = 0;
}

static void cut_gobj_camera_dl_link(GObj *gobj)
{
    if (gobj == 0) {
        debug_StdPrintfDummy("isys:null GObj\n");
        return;
    }
    if (gobj->dlPrev == 0) {
        if (gobj->dlNext == 0)
            goto head_check;
    } else {
        gobj->dlPrev->dlNext = gobj->dlNext;
    }
    if (gobj->dlNext != 0) {
        gobj->dlNext->dlPrev = gobj->dlPrev;
    }
head_check:
    if (gobj == gobj_camera_dl_link_head) {
        gobj_camera_dl_link_head = gobj->dlNext;
    }
    if (gobj == gobj_camera_dl_link_tail) {
        gobj_camera_dl_link_tail = gobj->dlPrev;
    }
}

void isysGObjRemoveCameraDL(GObj *self)
{
    cut_gobj_camera_dl_link(self);
}

/* this list's own add_gobj_to_tail, as in isys/gobj */
static void add_gobj_to_tail(GObj *self, unsigned int key)
{
    GObj *head;
    GObj *tail;
    GObj *cur;

    debug_StdPrintfDummy("camera gop:%x\n", self);

    self->dlKey = key;
    head = gobj_camera_dl_link_head;
    if (head == 0) {
        self->dlPrev = 0;
        self->dlNext = 0;
        gobj_camera_dl_link_head = self;
        gobj_camera_dl_link_tail = self;
        debug_StdPrintfDummy("first entry\n");
        return;
    }
    if (key < (unsigned int)head->dlKey) {
        self->dlPrev = 0;
        self->dlNext = head;
        head->dlPrev = self;
        gobj_camera_dl_link_head = self;
        debug_StdPrintfDummy("entry into head\n");
        return;
    }
    tail = gobj_camera_dl_link_tail;
    if (key >= (unsigned int)tail->dlKey) {
        self->dlPrev = tail;
        self->dlNext = 0;
        tail->dlNext = self;
        gobj_camera_dl_link_tail = self;
        debug_StdPrintfDummy("entry into tail\n");
        return;
    }

    cur = head;
    while (key >= (unsigned int)cur->dlNext->dlKey) {
        cur = cur->dlNext;
    }

    self->dlPrev = cur;
    self->dlNext = cur->dlNext;
    cur->dlNext = self;
    self->dlNext->dlPrev = self;
}

inline void isysGObjLinkCameraDLHead(GObj *self, void *dl, int key, int kindMask, int drawMask)
{
    self->dl = dl;
    self->kindMask = kindMask;
    self->drawMask = drawMask;
    insert_camera_dl_by_key(self, key);
}

void isysGObjMoveCameraDL(GObj *self, int key)
{
    cut_gobj_camera_dl_link(self);
    return add_gobj_to_tail(self, key);
}

inline void isysGObjMoveCameraDLHead(GObj *self, int key)
{
    cut_gobj_camera_dl_link(self);
    insert_camera_dl_by_key(self, key);
}

inline void isysObjMoveCameraDLAfterGObj(GObj *self, GObj *obj)
{
    cut_gobj_camera_dl_link(self);
    self->dlLinkId = obj->dlLinkId;
    self->dlPrev = obj;
    self->dlNext = obj->dlNext;
    obj->dlNext = self;
    self->dlKey = obj->dlKey;
    if (self->dlNext == 0) {
        gobj_camera_dl_link_tail = self;
    }
}

inline void isysObjMoveCameraDLBeforeGObj(GObj *self, GObj *obj)
{
    GObj *prev;
    cut_gobj_camera_dl_link(self);
    self->dlLinkId = obj->dlLinkId;
    prev = obj->dlPrev;
    self->dlNext = obj;
    self->dlPrev = prev;
    obj->dlPrev = self;
    self->dlKey = obj->dlKey;
    if (self->dlPrev == 0) {
        gobj_camera_dl_link_head = self;
    }
}

void isysGObjLinkCameraDL(GObj *self, void *dl, int key, int kindMask, unsigned int drawMask)
{
    debug_StdPrintfDummy("LinkCameraDL in\n");
    self->dl = dl;
    self->kindMask = kindMask;
    self->drawMask = drawMask;
    add_gobj_to_tail(self, key);
    debug_StdPrintfDummy("LinkCameraDL out\n");
}

void isysGObjLinkCameraDLAfterGObj(GObj *self, void *dl, int kindMask, int drawMask, GObj *obj)
{
    register GObj *t1 = self;
    GObj *next;
    int key;
    if (obj == 0) {
        debug_StdPrintfDummy("isys:null GObj\n");
        return;
    }

    t1->kindMask = kindMask;
    t1->drawMask = drawMask;
    t1->dl = dl;
    t1->dlLinkId = obj->dlLinkId;
    t1->dlPrev = obj;
    next = obj->dlNext;
    key = obj->dlKey;
    t1->dlNext = next;
    obj->dlNext = t1;
    t1->dlKey = key;
    if (t1->dlNext == 0) {
        gobj_camera_dl_link_tail = t1;
    }
}

void isysGObjLinkCameraDLBeforeGObj(GObj *self, void *dl, int kindMask, int drawMask, GObj *obj)
{
    register GObj *t1 = self;
    GObj *next;
    int key;
    if (obj == 0) {
        debug_StdPrintfDummy("isys:null GObj\n");
        return;
    }

    t1->kindMask = kindMask;
    t1->drawMask = drawMask;
    t1->dl = dl;
    t1->dlLinkId = obj->dlLinkId;
    t1->dlPrev = obj;
    next = obj->dlNext;
    key = obj->dlKey;
    t1->dlNext = next;
    obj->dlNext = t1;
    t1->dlKey = key;
    if (t1->dlNext == 0) {
        gobj_camera_dl_link_tail = t1;
    }
}
