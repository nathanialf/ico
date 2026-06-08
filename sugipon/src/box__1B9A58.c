#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1B9A58", initFallDown);

typedef struct { short f_0; short f_2; char _4[0xC]; void *f_10; } BoxC1B9A58;

extern void func_0010F048(void *a0);
extern void func_00104D20(void);
extern void *func_00105078(void);
extern void LocalizeDirectionOrient(void *buf, void *gobj);
extern void func_00104E38(int a0);
extern void func_00104D48(int a0);
extern void MatrixDrive_TurnXObjectMatrixYZ(void *dst, void *src);
extern void file_Init(void *a0);
extern void func_00105068(void);

void checkFieldContact(void *a0) {
    BoxC1B9A58 *box = *(BoxC1B9A58 **)((char *)(*(int **)((char *)a0 + 0x15C)) + 0x7F0);
    void *m;
    void *p10;
    func_0010F048(a0);
    func_00104D20();
    m = func_00105078();
    LocalizeDirectionOrient(m, a0);
    func_00104E38(box->f_2);
    func_00104D48(box->f_0);
    p10 = box->f_10;
    m = func_00105078();
    MatrixDrive_TurnXObjectMatrixYZ(*(void **)((char *)p10 + 0xC), m);
    file_Init(box->f_10);
    func_00105068();
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1B9A58", execNormalMove);
