#include "common.h"

typedef struct { int w[6]; } SugiRec;
extern SugiRec D_00706DA8[];
typedef struct { char _pad[0x10]; int data; void (*fp)(int); } SugiCb;
extern SugiCb D_00706DA8_cb[] __asm__("D_00706DA8");

void SugiLeafGeo2(int a0, int a1) {
    D_00706DA8[a0].w[5] = a1;
}

extern int D_0062B9E8;
extern void func_001EDA08(int x);

void SugiLeafDL2(void)
{
    int i;
    if (D_0062B9E8 == 0) {
        return;
    }
    for (i = 0; i < D_0062B9E8; i++) {
        func_001EDA08(D_00706DA8_cb[i].data);
        if (D_00706DA8_cb[i].fp != 0) {
            D_00706DA8_cb[i].fp(D_00706DA8_cb[i].data);
        }
    }
    D_0062B9E8 = 0;
}

extern void func_001EDA68(void);

int InitSugiLeafGeo(void) {
    func_001EDA68();
    return 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/sugiTree", SugiLeafGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/sugiTree", InitSugiLeafGeo2);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/sugiTree", func_001EE648);

/* The `r % 0x10000` store is the key: signed-mod-by-65536 keeps the bgez +
 * ori 0xFFFF + addu bias (the negative-remainder correction) live and pins
 * the 0x30 frame, while the short store truncates to raw r. */
extern short *iosFree(int handle, int size, void *file, int line);
extern int D_0062A310;
extern const char D_006130A8[];
extern int func_002610F0(void);

short *func_001EE7E0(void) {
    short *h = iosFree(D_0062A310, 2, (void *)D_006130A8, 0xC);
    int r = func_002610F0();
    *h = r % 0x10000;
    return h;
}

extern void *func_00105078(void);
extern void MatrixDrive_TurnXObjectMatrixYZ(void *dst, void *src);
extern float p2o_SetDefaultEnviroment(int a0);
extern void func_00104DC0(int a0);
extern void func_00104D48(int a0);

void func_001EE838(int a0) {
    int sub = *(int *)(a0 + 0x15C);
    short *geo = (short *)*(int *)(sub + 0x7F0);
    void *r;

    r = func_00105078();
    MatrixDrive_TurnXObjectMatrixYZ(r, (void *)(sub + 0x20));
    func_00104DC0((short)(p2o_SetDefaultEnviroment(geo[0]) * 256.0f));
    func_00104D48((short)(p2o_SetDefaultEnviroment((short)(geo[0] * 2)) * 256.0f));
    r = func_00105078();
    MatrixDrive_TurnXObjectMatrixYZ(*(void **)(sub + 0xC), r);
    geo[0] = (unsigned short)geo[0] + 0x80;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/sugiTree", func_001EE8F0);

extern void ExecFrameDependSequence(int a0);
extern void playSEConditionID(int a0, int a1);

void func_001EE978(int a0) {
    ExecFrameDependSequence(a0);
    playSEConditionID(a0, 0x41);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/sugiTree", func_001EE9A8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/sugiTree", func_001EEB10);
