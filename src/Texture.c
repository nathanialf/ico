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

extern int bga_CheckAnimationFrame(int a0, int a1, int a2);
extern int font_Print(int a0, int a1, int a2);

int tex_setTexReg(int a0, int a1, int a2) {
    int i;
    char *e = (char *)D_00674058;
    for (i = 0; i < D_00633C54; i++, e += 0x290) {
        int *entry1 = *(int **)(e + 0x280);
        if (a0 == entry1[0x58 / 4]) {
            int mode = *(int *)(e + 0x28C) >> 30;
            switch (mode) {
                case 0:
                    return bga_CheckAnimationFrame(*(int *)(e + 0x284), a1, a2);
                case 1:
                    return font_Print(*(int *)(e + 0x288), a1, a2);
            }
        }
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_transVramClutTex);

/* Texture .rodata run 0x555E70..0x5565E0 -- byte-verified against baseelf;
 * defs interleave with INCLUDE_ASM stubs so .o section order == VMA order */
const unsigned int D_00555E70[0xC] = { 0x00000000, 0x00000000, 0x00000000, 0x50000002, 0x00008001, 0x10000000, 0x0000000E, 0x00000000, 0x00000001, 0x00000000, 0x0000003F, 0x00000000 };
const char D_00555EA0[0x38] = "tex_loadImage:判別できないテクスチャフォーマットです.\n\0\0";
const char D_00555ED8[0x10] = "src/Texture.c";
const char D_00555EE8[0x38] = "tex_loadImage:テクスチャのサイズが大きすぎます.\n\0\0\0\0\0\0\0\0";

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

const char D_00556010[0x40] = "DIRECTでもCLUTでもないテクスチャタイプが指定されました.\n\0\0\0\0\0\0\0\0";
const char D_00556050[0x38] = "tex_transTM2:ミップマップテクスチャの枚数が多すぎます.\n\0";
const char D_00556088[0x48] = "テクスチャが壊れています.\"%s\"I:%d C:%d iadr:%p cadr:%p hadr:%p\n\0\0\0\0\0\0\0\0\0";

INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_convertClutCSM2ToCSM1);

INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_convertImage);

INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_makeCopyImage);

INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_makeTexturePacket);

INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_initTextureSub);

INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_LoadTexturePart);

const char D_005563A0[0x50] = "tex_makeTexturePacket:テクスチャのユーザースペースフォーマットが異常です.'%s'\n\0\0";

INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_TransTexture);

const char D_00556430[0x38] = "\033[31mパスの違う同名のテクスチャを読み込もうとしました.\n\0";

INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_scrollClut);

INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_textureAnimation);

const char D_00556478[0x40] = "テクスチャが多すぎます.テクスチャリスト領域を増やしてください\n\0\0";
const char D_005564B8[0x28] = "テクスチャ \"%s\" がみつかりません.\n\0\0\0\0\0\0";

INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_SetClutAnimation);

const char D_00556510[0x38] = "tex_TransTexture:テクスチャの転送に失敗しました. %d\n\0\0\0\0";
const char D_00556548[0x38] = "tex_TransTexture:テクスチャの転送に失敗しました. %d:%s\n\0";

INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_FreeTexture);

INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_ResetVram);

INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_dispClut);

INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_printTexture);

INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_Tool);

INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_ListTool);

INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_GetTWTH);

