#include "common.h"

extern int D_0062BF54;
extern char D_0066DBD8[];
extern void mc_TransMicroCode(char *target, int arg1);
extern void GetInverseQuaternion(char *target, int arg2);

void tex_AllocVramAuto(int key, int arg1, int arg2)
{
    int count = *(volatile int *)&D_0062BF54;
    int i = 0;
    char *e = (char *)D_0066DBD8;
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
            count = *(volatile int *)&D_0062BF54;
        }
        i++;
        e += 0x290;
    } while (i < count);
}

extern int D_0062BF58;

typedef struct AnimNode { long field0; char _pad[0x14 - 0x8]; struct AnimNode *next; } AnimNode;

void tex_loadImage(int a0, int a1)
{
    AnimNode *p = (AnimNode *)D_0062BF58;
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
    char *e = (char *)D_0066DBD8;
    for (i = 0; i < D_0062BF54; i++, e += 0x290) {
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

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_transVramClutTex);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_transVramDirectTex);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_transRegister);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_transTM2);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_initClutTexture);

extern void dpk_Init(int a0, void *a1, int a2);
extern int dl_GetPri(void);

void tex_setRegisters(void *a0) {
    dpk_Init(2, (char *)a0 + 0x58, 5);
    dl_GetPri();
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_initTM2);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_convertClutCSM2ToCSM1);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_convertImage);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_makeCopyImage);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_makeTexturePacket);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_initTextureSub);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_LoadTexturePart);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_TransTexture);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_scrollClut);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_textureAnimation);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_SetClutAnimation);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_FreeTexture);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_ResetVram);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_dispClut);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_printTexture);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_Tool);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_ListTool);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_GetTWTH);


/* recovered struct shapes */
typedef struct {
    short              f_0;  /* 0x00 */
    short              f_2;  /* 0x02 */
    short              f_4;  /* 0x04 */
} S_0067ADF8;  /* stride 0x6 */

typedef struct {
    short              f_0;  /* 0x00 */
    unsigned int       f_4;  /* 0x04 */
} S_002725D8;  /* stride 0xC */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_002725B8;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_00272620;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_005502D0;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00550480;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00550570;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00550660;  /* stride 0x4 */

/* end struct shapes */
