#include "common.h"

#include "sugiCommon.h"

typedef struct {
    float *phase; /* 0x00 */
    float *speed; /* 0x04 */
    float *unk8;  /* 0x08 */
} LightLineExt;
extern LightLineExt *llExtGeo;
extern void AdjustMotionHeightToNearestField(void *a0);
/* prototypes: their order is the inline tail's emission order */
void SelectBoyCrown(char *a0, int a1);
void LightLineGeo(void);
void SetBoyStonizedVisual(char *a0);
INCLUDE_ASM("asm/nonmatchings/src/boy", dispClothes);
ASM_LIT4_SLOT(D_0063940C, 0.98f);
ASM_LIT4_SLOT(D_00639410, 0.98f);
ASM_LIT4_SLOT(D_00639414, 0.98f);
ASM_LIT4_SLOT(D_00639418, 0.98f);
ASM_LIT4_SLOT(D_0063941C, 0.98f);
ASM_LIT4_SLOT(D_00639420, 0.98f);
ASM_LIT4_SLOT(D_00639424, 0.999f);
INCLUDE_ASM("asm/nonmatchings/src/boy", execClothes);
ASM_LIT4_SLOT(D_00639428, 0.1f);
ASM_LIT4_SLOT(D_0063942C, 0.01f);
ASM_LIT4_SLOT(D_00639430, 0.9f);
INCLUDE_ASM("asm/nonmatchings/src/boy", InitLightLineGeo);
inline void LightLineGeo(void)
{
    int i;

    for (i = 0; i < 100; i++) {
        llExtGeo->phase[i] += llExtGeo->speed[i];
        if (llExtGeo->phase[i] > 1.0f) {
            llExtGeo->speed[i] = random_unit() * 0.01f + 0.001f;
            llExtGeo->phase[i] = 0;
        }
    }
}
ASM_LIT4_SLOT(D_00639434, 0.05f);
ASM_LIT4_SLOT(D_00639438, 0.4f);
ASM_LIT4_SLOT(D_0063943C, 18.99998f);
ASM_LIT4_SLOT(D_00639440, 0.05f);
ASM_LIT4_SLOT(D_00639444, 0.4f);
INCLUDE_ASM("asm/nonmatchings/src/boy", LightLineDL);
inline void SelectBoyCrown(char *a0, int a1) {
    *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x0) = a1;
}
INCLUDE_ASM("asm/nonmatchings/src/boy", InitBoyGeo);
ASM_LIT4_SLOT(D_00639448, 0.9f);
INCLUDE_ASM("asm/nonmatchings/src/boy", synchronizeMotionOutputOriginForGirl);
ASM_LIT4_SLOT(D_0063944C, 0.98f);
INCLUDE_ASM("asm/nonmatchings/src/boy", actionOfWater);
ASM_LIT4_SLOT(D_00639450, 0.7f);
INCLUDE_ASM("asm/nonmatchings/src/boy", BoyGeo);
INCLUDE_ASM("asm/nonmatchings/src/boy", dispSubParts);
INCLUDE_ASM("asm/nonmatchings/src/boy", dispCrown);
inline void SetBoyStonizedVisual(char *a0) {
    char *crown = (char *)*(int *)(*(int *)(a0 + 0x15C) + 0x830);
    AdjustMotionHeightToNearestField(a0);
    *(int *)(crown + 0x18) = 1;
    *(int *)(crown + 0x1C) = 0;
    *(int *)(*(int *)(a0 + 0x15C) + 0x62C) = 0;
}
INCLUDE_ASM("asm/nonmatchings/src/boy", BoyDL);
