#include "common.h"




typedef struct AnimNode {
    long field0;            /* 0x00 */
    char _pad[0x14 - 0x8];
    struct AnimNode *next;  /* 0x14 */
} AnimNode;
extern int D_00633C58;
extern void dl_GetPri();
extern void dpk_Init();
extern void mc_TransMicroCode(void *dst, void *src);
extern int D_00633C54;
extern void GetInverseQuaternion();
extern char D_00674058[];
void tex_AllocVramAuto(int key, int arg1, int arg2)
{
    int count = *(volatile int *)&D_00633C54;
    int i = 0;
    char *e = (char *)D_00674058;
    if (count <= 0) return;
    do {
        int *entry1 = *(int **)(e + 0x280);
        if (key == entry1[0x58 / 4]) {
            int *entry2;
            char *target;
            entry2 = *(int **)(e + 0x284);
            target = *(char **)((char *)entry2 + 0x24);
            mc_TransMicroCode(target, arg1);
            entry2 = *(int **)(e + 0x284);
            target = *(char **)((char *)entry2 + 0x24);
            GetInverseQuaternion(target + 0x10, arg2);
            count = *(volatile int *)&D_00633C54;
        }
        i++;
        e += 0x290;
    } while (i < count);
}

void tex_loadImage(int a0, int a1)
{
    AnimNode *p = (AnimNode *)D_00633C58;
    int count = 0;
    while (p != 0) {
        long v = p->field0;
        if ((((unsigned short)v << 18) >> 18) == a0) {
            if (!(v & 0x8000)) {
                count++;
                if (a1 < count) {
                    p->field0 = v | 0x8000;
                }
            }
        }
        p = p->next;
    }
}

INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_setTexReg);

INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_transVramClutTex);

INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_transVramDirectTex);

INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_transRegister);

INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_transTM2);

INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_initClutTexture);

void tex_setRegisters(int a0)
{
    dpk_Init(2, a0 + 0x58, 5);
    dl_GetPri();
}

INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_initTM2);

INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_convertClutCSM2ToCSM1);

INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_convertImage);

INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_makeCopyImage);

INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_makeTexturePacket);

INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_initTextureSub);

INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_LoadTexturePart);

INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_TransTexture);

INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_scrollClut);

INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_textureAnimation);

INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_SetClutAnimation);

INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_FreeTexture);

INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_ResetVram);

INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_dispClut);

INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_printTexture);

INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_Tool);

INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_ListTool);

INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_GetTWTH);

