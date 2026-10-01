#include "debug.h"
#include "icoMisc.h"
#include "gobj_dl.h"
#include "camera-root.h"
#include "GobjProc.h"
#include "gobj.h"
#include "gobj_process.h"

/* .sdata: the number of entries in gobj_table. */
static int gobjCount = 0; /* derived name */

/* .bss: the table of created game objects, 208 entries */
static GObj *gobj_table[208]; /* derived name */

/* this TU passes a4 as unsigned int; gobj_cam_dl.h declares an int */
extern void isysGObjLinkCameraDL(char *a0, int a1, int a2, int a3, unsigned int a4);

void ResetGObjProc(void)
{
    gobjCount = 0;
}

int GetMaxGObj(void)
{
    return gobjCount;
}

GObj *GetGObjP(int idx)
{
    return gobj_table[idx];
}

int GetGObjId(GObj *gobj)
{
    int i;
    for (i = 0; i < gobjCount; i++) {
        if (gobj == gobj_table[i]) {
            return i;
        }
    }
    return -1;
}

void PrintGObjID(GObj *gobj)
{
    int i;
    for (i = 0; i < gobjCount; i++) {
        if (gobj == gobj_table[i]) {
            debug_StdPrintfDummy("%d\n", i);
        }
    }
}

GObj *InitCameraGObjs(int a0, int from, int to)
{
    GObj *g = 0;
    GObj *cam;
    int i;

    for (i = from; i < to; i++) {
        g = isysGObjAdd((int)SetCameraMatrix, 0, 0);
        g->act = 0;
        g->labelType = 0;
        g->labelId = -1;
        g->kind = -1;
        g->active = 1;
        isysGObjLinkObjDL(g, DispIcoMisc, 0, 0, 0xFFFFFFFF);
    }

    cam = isysGObjAdd(0, 0, 0);
    cam->act = 0;
    isysGObjLinkCameraDL(cam, 0, 0, 1, 0xFFFFFFFF);

    return g;
}

inline GObj *CreateGObjByFuncSet(void (*before)(GObj *), void (*ai)(GObj *), void (*geo)(GObj *),
                                 void (*afterGeo)(GObj *), void (*start)(), void (*dl)(GObj *),
                                 int key)
{
    GObj *g;

    g = isysGObjAdd(before, 0, 0);
    g->act = 0;
    g->labelType = 1;
    g->labelId = -1;
    g->kind = -1;
    g->active = 1;
    gobj_table[gobjCount++] = g;
    isysGObjProcAdd(g, ai, 1, 22);
    isysGObjProcAdd(g, geo, 1, 23);
    isysGObjProcAdd(g, afterGeo, 1, 24);
    isysGObjLinkObjDL(g, dl, 0, key, 0xFFFFFFFF);
    if (start != 0) {
        isysGObjProcAddS(g, start, 0, 19, 6144);
    }
    return g;
}

GObj *CreateGObj(ObjKindEnt *p, int a1, int a2, int a3, int a4)
{
    GObj *g;
    void (*start)() = 0;

    if (a4 != 0) {
        start = p->start;
    }
    g = CreateGObjByFuncSet(p->before, p->ai, p->geo, p->afterGeo, start, p->dl, a3);
    g->labelId = a2;
    isysGObjKindTableAdd(g, a1);
    return g;
}
