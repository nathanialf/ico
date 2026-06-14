#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Shadow", shadow_Reset);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Shadow", shadow_Draw);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Shadow", shadow_Render);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Shadow", shadow_getShadowVectorAverage);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Shadow", shadow_EntryClusterShadow);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Shadow", shadow_EntryNormalShadow);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Shadow", __GetCameraPos);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Shadow", shadow_RenderVolume);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Shadow", shadow_RenderVolumeMulti);

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

void shadow_KillShadow(int a0) {
    if (a0 >= 0) {
        D_0062AF6C += tex_SetClutAnimation(a0);
    }
}

void shadow_DispCancel(void) {
    D_0062A040 = 0;
}

int shadow_SetLength(int a0) {
    switch (a0) {
    case 1: return 7;
    case 2: return 8;
    case 3: return 9;
    }
    return 7;
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Shadow", shadow_Init);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Shadow", func_00122FE8);

extern void debug_assertMessage(void *a0);
extern unsigned char D_0054FCD0[];

void func_00123AA8(void) {
    volatile int frame_pad[2];  /* reserves the o32 arg-save area the ROM keeps */
    debug_assertMessage(D_0054FCD0);
}

extern void mc_TransMicroCode(int a0, int a1);
extern void _PopCurrentMatrix(void *a0);
extern void func_00118108(void);
extern void _ClearTransCurrentMatrix(void *a0, void *a1);
extern void _SetCurrentMatrix(int a0, int a1);
extern char *D_00629C70;

void func_00123AC8(int a0, int a1) {
    mc_TransMicroCode(a0, a1 + 0x820);
    _PopCurrentMatrix(D_00629C70 + 0x80);
    func_00118108();
    _ClearTransCurrentMatrix((void *)a0, (void *)a0);
    _SetCurrentMatrix(a0, a0);
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
