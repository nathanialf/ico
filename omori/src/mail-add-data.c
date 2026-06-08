#include "common.h"

int InitMailAdditionalData(int a0)
{
    if (a0 < -135) a0 = 180;
    else if (a0 < -45) a0 = -90;
    else if (a0 < 45) a0 = 0;
    else {
        int v = a0;
        a0 = 180;
        if (v <= 134) a0 = 90;
    }
    return a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/mail-add-data", ActSendMail_WithAdditionalData);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/mail-add-data", GetMailAdditionalData);

extern float D_006CCE30[];
extern int D_00271240[];
extern float D_0062C0B0;

void ClearMailAdditionalData(void)
{
    int a = D_00271240[0];
    int b = D_00271240[1];
    int t = a * 10;
    int diff = 0x3C - t;
    int q;
    *(int *)&D_006CCE30[0] = 0;
    *(int *)&D_006CCE30[1] = 0;
    q = diff / b;
    D_0062C0B0 = 60.0f / (float)q;
}


void func_00192628(void)
{
    int a = D_00271240[0];
    int b = D_00271240[1];
    int t = a * 10;
    int diff = 0x3C - t;
    int q;
    *(int *)&D_006CCE30[0] = 0;
    *(int *)&D_006CCE30[1] = 0;
    q = diff / b;
    D_006CCE30[5] = 120.0f;
    D_006CCE30[6] = 80.0f;
    D_0062C0B0 = 60.0f / (float)q;
}


void func_001926A8(float a0, float a1) {
    D_006CCE30[5] = a0;
    D_006CCE30[6] = a1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/mail-add-data", func_001926C0);

extern void func_001929A0(char *self);

void func_001927E8(int **a0, int a1) {
    int *p = a0[0x59];
    p[0x19D] = a1;
    func_001929A0(a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/mail-add-data", func_001927F8);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/mail-add-data", func_001928F8);

extern void func_001AAD00(const char *, int);
extern void func_00260380(const char *, int, const char *);

extern char D_005550C8[];

extern char D_005550E0[];

void func_001929A0(char *self)
{
    char *sub_a = *(char **)(self + 0x164);
    int *sub_b;
    if (sub_a == 0) {
        func_001AAD00(D_005550C8, 0x47);
        func_00260380(D_005550C8, 0x47, D_005550E0);
        sub_a = *(char **)(self + 0x164);
    }
    sub_b = *(int **)(sub_a + 0x674);
    *sub_b = 0;
}

extern void gif_SpriteOffset(int a0);
extern void gsb_SetFrame(int a0, int a1, int a2);

void func_00192A08(void) {
    gif_SpriteOffset(0xB);
    gsb_SetFrame(1, 2, 0x40);
}

extern void func_0010F9D0(void);

void func_00192A30(void) {
    func_0010F9D0();
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/mail-add-data", func_00192A38);

extern void MatrixDrive_TurnXObjectMatrixYZ(void *dst, void *src);
extern char D_00287300[];

void func_00192B50(void *a0) {
    MatrixDrive_TurnXObjectMatrixYZ(D_00287300, a0);
    gif_SpriteOffset(0xB);
}
