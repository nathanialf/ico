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

int GetGObjP(int idx)
{
    return (int)gobj_table[idx];
}

int GetGObjId(int a0)
{
    int i;
    for (i = 0; i < gobjCount; i++) {
        if (a0 == (int)gobj_table[i]) {
            return i;
        }
    }
    return -1;
}

void PrintGObjID(int a0)
{
    int i;
    for (i = 0; i < gobjCount; i++) {
        if (a0 == (int)gobj_table[i]) {
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

inline GObj *CreateGObjByFuncSet(int a0, int a1, int a2, int a3, int a4, int a5, int a6)
{
    GObj *g;

    g = isysGObjAdd(a0, 0, 0);
    g->act = 0;
    g->labelType = 1;
    g->labelId = -1;
    g->kind = -1;
    g->active = 1;
    gobj_table[gobjCount++] = g;
    isysGObjProcAdd(g, a1, 1, 0x16);
    isysGObjProcAdd(g, a2, 1, 0x17);
    isysGObjProcAdd(g, a3, 1, 0x18);
    isysGObjLinkObjDL(g, a5, 0, a6, 0xFFFFFFFF);
    if (a4 != 0) {
        isysGObjProcAddS(g, a4, 0, 0x13, 0x1800);
    }
    return g;
}

GObj *CreateGObj(ObjKindEnt *p, int a1, int a2, int a3, int a4)
{
    GObj *g;
    int r21 = 0;

    if (a4 != 0) {
        r21 = (int)p->start;
    }
    g = CreateGObjByFuncSet((int)p->before, (int)p->ai, (int)p->geo, p->afterGeo, r21, (int)p->dl,
                            a3);
    g->labelId = a2;
    isysGObjKindTableAdd(g, a1);
    return g;
}
