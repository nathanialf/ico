#include "common.h"

extern void BeforeFunc2();

void ObjectBeforeFunc(int a0, int a1, int a2, int a3)
{
    BeforeFunc2(a0, a1, a2, a3);
}
INCLUDE_ASM("asm/nonmatchings/src/objact", ObjAction_CorrectGeo);
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
INCLUDE_ASM("asm/nonmatchings/src/objact", ObjAction_Init);
