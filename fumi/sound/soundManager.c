#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", sndBgmReadyNextStage);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", sndInit);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", sndManager);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_00143298);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_001432E0);

extern void ExecIcoMisc(int a0, int a1);

void func_001433E0(int *a0) {
    ExecIcoMisc(a0[3], a0[2]);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_001433F0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_001434C0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_00143610);

extern void *D_00629DE4, *D_00629DE8;
extern void _ACTGame_SearchGObj(void *a0, int a1, int a2, int a3, void *a4, int a5, int a6);

void func_001438A8(void) {
    _ACTGame_SearchGObj(D_00629DE4, 1, 4, 5, D_00629DE8, 0, 0);
}

void func_001438C8(void) {
    _ACTGame_SearchGObj(D_00629DE4, 1, 4, 0, 0, 0, 0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_001438E8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_00143910);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_00143B00);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_00143DB8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_00143DE0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_00143FB0);

extern void ActPara_GetDefTbl(void *a0, int a1);

void func_001440F0(void *a0) {
    int *p = *(int **)((char *)a0 + 0x164);
    p[0x20] = 0;
    ActPara_GetDefTbl(a0, 0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_00144100);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_00144260);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_001443B8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_00144440);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_001446F8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_001449B8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_00144C10);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00552210;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00552240;  /* stride 0x4 */

/* end struct shapes */
