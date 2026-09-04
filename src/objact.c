#include "common.h"

extern void BeforeFunc2();

void ObjectBeforeFunc(int a0, int a1, int a2, int a3)
{
    BeforeFunc2(a0, a1, a2, a3);
}
typedef struct { char pad[0x34]; int x34; char pad2[0x4C - 0x38]; } OaRecA;
typedef struct { int x0; int x4; int x8; int xC; int x10; } OaRecB;
extern OaRecA D_002C2DC8[];
extern OaRecB D_002BC6E0[];
void ObjAction_CorrectGeo(int a0, int a1) {
    int e;
    OaRecB *p;
    if (a0 < 0) return;
    e = D_002C2DC8[a0].x34;
    if (e != 0) {
        p = &D_002BC6E0[e];
    } else {
        p = 0;
    }
    if (p == 0) return;
    if ((p->x10 & 1) == 1u) {
        p->xC = 0x3CC;
    }
    if (p->xC == 0x3CC) {
        p->xC = p->x0;
    }
}
extern void iosOmSendMail(void *a0, int a1, void *a2);
extern void *isysGObjGetExist_begin(void);
extern void *isysGObjGetExist_next(void *a0);

void ObjAction_Mail(void *a0, int a1) {
    void *p = isysGObjGetExist_begin();
    while (p != 0) {
        iosOmSendMail(p, a1, a0);
        p = isysGObjGetExist_next(p);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/objact", ObjAction_MailCenter);
extern void ObjAction_CorrectGeo(int a0, int a1);

void ObjAction_Init(void) {
    int *p = (int *)isysGObjGetExist_begin();
    while (p != 0) {
        ObjAction_CorrectGeo(p[2], 0);
        p = (int *)isysGObjGetExist_next(p);
    }
}
