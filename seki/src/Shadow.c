#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Shadow", shadow_Reset);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Shadow", shadow_Draw);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Shadow", shadow_Render);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Shadow", shadow_getShadowVectorAverage);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Shadow", shadow_EntryClusterShadow);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Shadow", shadow_EntryNormalShadow);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Shadow", __GetCameraPos);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Shadow", shadow_RenderVolume);

extern void shadow_Reset(void *a0);
extern void reg_setNMatrixPacketNoLightCalc(void *a0);
extern void reg_dispPointLineObj(void *a0);
extern void reg_RenderReflection(void *a0);

void shadow_RenderVolumeMulti(void *a0) {
    if (*(unsigned short *)((char *)a0 + 0x808) == 2) {
        int mode = (unsigned short)(*(unsigned long long *)(*(int *)((char *)a0 + 0x810) + 0x30) >> 16) & 3;
        if (mode == 2) {
            shadow_Reset(a0);
        } else {
            reg_setNMatrixPacketNoLightCalc(a0);
        }
    } else {
        int mode = (unsigned short)(*(unsigned long long *)(*(int *)((char *)a0 + 0x810) + 0x30) >> 16) & 3;
        switch (mode) {
            case 0:
                reg_dispPointLineObj(a0);
                break;
            case 1:
                reg_RenderReflection(a0);
                break;
            case 2:
                shadow_Reset(a0);
                break;
        }
    }
}

extern void reg_DispAccessoryWithShadow(void);
extern int D_0062A040;

void shadow_MakeObjectData(void) {
    reg_DispAccessoryWithShadow();
}

void shadow_Tool(int a0) {
    D_0062A040 = a0;
}

extern int tex_SetClutAnimation(int a0);
extern int D_0062AF6C;

void reg_TransTexturePacket(int a0) {
    if (a0 >= 0) {
        D_0062AF6C += tex_SetClutAnimation(a0);
    }
}

void shadow_DispCancel(void) {
    D_0062A040 = 0;
}

int reg_GetShinePri(int a0) {
    switch (a0) {
    case 1: return 7;
    case 2: return 8;
    case 3: return 9;
    }
    return 7;
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Shadow", shadow_Init);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Shadow", func_00122FE8);

extern void debug_StdPrintfDummy(void *a0);
extern unsigned char D_0054FCD0[];

void func_00123AA8(void) {
    volatile int frame_pad[2];  /* reserves the o32 arg-save area the ROM keeps */
    debug_StdPrintfDummy(D_0054FCD0);
}

extern void mc_TransMicroCode(int a0, int a1);
extern void _SetCurrentMatrix(void *a0);
extern void func_00118108(void);
extern void _ApplyCurrentMatrix(void *a0, void *a1);
extern void _NormalizeVector(int a0, int a1);
extern char *D_00629C70;

void func_00123AC8(int a0, int a1) {
    mc_TransMicroCode(a0, a1 + 0x820);
    _SetCurrentMatrix(D_00629C70 + 0x80);
    func_00118108();
    _ApplyCurrentMatrix((void *)a0, (void *)a0);
    _NormalizeVector(a0, a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Shadow", func_00123B18);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0054FC30;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0054FC40;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0054FC5C;  /* stride 0x10 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0054FC9C;  /* stride 0x10 */

/* end struct shapes */
