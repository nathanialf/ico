#include "debug.h"
#include "icoMisc.h"
#include "gobj_dl.h"
#include "camera-root.h"
#include "GobjProc.h"
#include "gobj.h"
#include "gobj_process.h"

/* .sdata, owned by GobjProc.o (VMA 0x63C0C8..0x63C0CC; MAIN.MAP names no
   symbol in the run): the number of entries in gobj_table. */
static int gobjCount = 0; /* derived name */

/* .bss, owned by GobjProc.o and reached only from this file (MAIN.MAP names no
   symbol in the run): the table of created game objects, 208 entries. */
static PObjGObj *gobj_table[208];

/* kept local: a4 is unsigned int here, int in gobj_cam_dl.h */
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

PObjGObj *InitCameraGObjs(int a0, int from, int to)
{
    PObjGObj *g = 0;
    PObjGObj *cam;
    int i;

    for (i = from; i < to; i++) {
        g = isysGObjAdd((int)SetCameraMatrix, 0, 0);
        g->act = 0;
        g->labelType = 0;
        g->labelId = -1;
        g->kind = -1;
        g->active = 1;
        isysGObjLinkObjDL(g, (int)DispIcoMisc, 0, 0, 0xFFFFFFFF);
    }

    cam = isysGObjAdd(0, 0, 0);
    cam->act = 0;
    isysGObjLinkCameraDL(cam, 0, 0, 1, 0xFFFFFFFF);

    return g;
}

inline PObjGObj *CreateGObjByFuncSet(int a0, int a1, int a2, int a3, int a4, int a5, int a6)
{
    PObjGObj *g;

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

PObjGObj *CreateGObj(PObjGObj *p, int a1, int a2, int a3, int a4)
{
    PObjGObj *g;
    int r21 = 0;

    if (a4 != 0) {
        r21 = p->dlLinkId;
    }
    g = CreateGObjByFuncSet(p->mailArg, p->mailType, p->drawMask, p->word4C, r21, p->dl, a3);
    g->labelId = a2;
    isysGObjKindTableAdd(g, a1);
    return g;
}
