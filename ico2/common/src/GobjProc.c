#include "common.h"
#include "debug.h"
#include "icoMisc.h"
#include "gobj_dl.h"
#include "camera-root.h"
#include "GobjProc.h"
#include "gobj.h"
#include "gobj_process.h"

extern int D_0063C0C8;

/* .bss, owned by GobjProc.o and reached only from this file (MAIN.MAP names no
   symbol in the run): the table of created game objects, 208 entries. */
static PObjGObj *gobj_table[208];

/* kept local: the declaration in gobj_cam_dl.h changes this TU codegen */
extern void isysGObjLinkCameraDL(void *a0, int a1, int a2, int a3, unsigned int a4);

void ResetGObjProc(void)
{
    D_0063C0C8 = 0;
}

int GetMaxGObj(void)
{
    return D_0063C0C8;
}

int GetGObjP(int idx)
{
    return (int)gobj_table[idx];
}

int GetGObjId(int a0)
{
    int i;
    for (i = 0; i < D_0063C0C8; i++) {
        if (a0 == (int)gobj_table[i]) {
            return i;
        }
    }
    return -1;
}

void PrintGObjID(int a0)
{
    int i;
    for (i = 0; i < D_0063C0C8; i++) {
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
        g->f04 = 0;
        g->f08 = -1;
        g->f0C = -1;
        g->f16C = 1;
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
    g->f04 = 1;
    g->f08 = -1;
    g->f0C = -1;
    g->f16C = 1;
    gobj_table[D_0063C0C8++] = g;
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
        r21 = p->f40;
    }
    g = CreateGObjByFuncSet(p->f60, p->f5C, p->f50, p->f4C, r21, p->f48, a3);
    g->f08 = a2;
    isysGObjKindTableAdd(g, a1);
    return g;
}
