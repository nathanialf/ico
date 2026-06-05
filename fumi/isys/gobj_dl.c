#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj_dl", cut_gobj_dl_link);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj_dl", isysGObjRemoveObjDL);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj_dl", func_0013E7E0);

extern unsigned int D_0062A4CC;

void func_0013E828(int a0, int a1) {
    if (a1 == 0) {
        D_0062A4CC &= ~(1 << a0);
    } else {
        D_0062A4CC |= (1 << a0);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj_dl", isysGObjMoveObjDL);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj_dl", isysGObjMoveObjDLHead);

extern void isysGObjMoveObjDLHead(void);

void isysGObjLinkObjDL(void) {
    isysGObjMoveObjDLHead();
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj_dl", isysGObjLinkObjDLHead);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj_dl", isysGObjLinkObjDLAfterGObj);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj_dl", isysGObjLinkObjDLBeforeGObj);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj_dl", isysGObjDlInit);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj_dl", isysGObjMoveObjDLAfterGObj);

extern void isysGObjLinkObjDLAfterGObj(void *a0, unsigned char a1, void *a2);

void isysGObjMoveObjDLBeforeGObj(void *a0, void *a1, unsigned char a2, void *a3, void *a4) {
    if (a1 != 0) {
        *(void **)((char *)a0 + 0x48) = a1;
        *(void **)((char *)a0 + 0x50) = a4;
        isysGObjLinkObjDLAfterGObj(a0, a2, a3);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj_dl", func_0013ECE0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj_dl", func_0013ED48);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0027DE30;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0027DE50;  /* stride 0x4 */

/* end struct shapes */
