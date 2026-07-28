#include "common.h"





extern int *D_00632190;
struct PadNode {
    char pad[0x30];
    struct PadNode *prev;
    struct PadNode *next;
};
extern int iosThreadInit();
extern int D_006A6DB0[];
INCLUDE_ASM("asm/nonmatchings/ios/shockdriver", Vibration_ShotDecode);

INCLUDE_ASM("asm/nonmatchings/ios/shockdriver", Vibration_WaveDecode);

int *Shock_Request(int key, unsigned int val)
{
    int *p = D_006A6DB0;
    int *rv;
    int i;
    val = val & 0xFF;
    i = 0xF;
    while (1) {
        if (*p == key) goto found;
        i--;
        if (i == -1) goto notfound;
        p = (int *)((char *)p + 0x18);
    }
notfound:
    rv = 0;
    goto end;
found:
    rv = p;
end:
    if (rv != 0) {
        *(unsigned char *)((char *)rv + 0x14) = val;
    }
    return rv;
}

INCLUDE_ASM("asm/nonmatchings/ios/shockdriver", Shock_SetMotor);

INCLUDE_ASM("asm/nonmatchings/ios/shockdriver", func_0013BA68);

void Init_ShockVoiceSet(void) {}

void Vibration_SetDecodeData(void) {}

INCLUDE_ASM("asm/nonmatchings/ios/shockdriver", Init_ShockRequestBox);

INCLUDE_ASM("asm/nonmatchings/ios/shockdriver", ShockRequestBox_Clear);

INCLUDE_ASM("asm/nonmatchings/ios/shockdriver", ShockRequestBox_Regst);

INCLUDE_ASM("asm/nonmatchings/ios/shockdriver", ShockRequestBox_Request);

INCLUDE_ASM("asm/nonmatchings/ios/shockdriver", ShockRequestBox_DecodeRequest);

INCLUDE_ASM("asm/nonmatchings/ios/shockdriver", ShockRequestBox_EndRequestFree);

void ShockRequestBox_VoiceSetUseRequestFree(int *a0, int a1, int a2, int a3)
{
    a0[0] = 0;
    if (a1) {
        a0[1] = a1;
    } else {
        a0[1] = (int)&iosThreadInit;
    }
    a0[2] = a2;
    a0[3] = a3;
}

void ShockRequestBox_GetRequest(int *self)
{
    int *node = (int *) self[0];
    if (self[0x8 / 4] == 0)
    {
        goto end;
    }
    if (node == 0)
    {
        goto end;
    }
    do
    {
        int *cur = node;
        node = (int *) node[0x34 / 4];
        (*(void (**)(int, int))((char *) self + 8))((int) cur, self[0xC / 4]);
    } while (node != 0);
end:
    self[0] = 0;
}

void ShockRequestBox_RequestCancel(struct PadNode **head, struct PadNode *new_node) {
    struct PadNode *old = *head;
    new_node->prev = (struct PadNode *)0;
    new_node->next = old;
    if (old != (struct PadNode *)0) {
        old->prev = new_node;
    }
    *head = new_node;
}

INCLUDE_ASM("asm/nonmatchings/ios/shockdriver", ShockRequestBox_RequestDirectCancel);

INCLUDE_ASM("asm/nonmatchings/ios/shockdriver", Init_ShockDriver);

INCLUDE_ASM("asm/nonmatchings/ios/shockdriver", ShockDriver_VoiceSet_NumberRegist);

INCLUDE_ASM("asm/nonmatchings/ios/shockdriver", ShockDriver_VoiceSet_Regist);

int *ShockDriver_VoiceSet_Remove(int **head_ptr, int key)
{
    int *p;
    if (head_ptr == 0) goto fail;
    p = *head_ptr;
    if (p == 0) goto fail;
    do {
        if (p[0x28 / 4] == key) {
            return p;
        }
        p = (int *)p[0x34 / 4];
    } while (p != 0);
fail:
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/ios/shockdriver", ShockDriver_GetShockVoiceMax);

INCLUDE_ASM("asm/nonmatchings/ios/shockdriver", ShockDriver_GetShockVoiceSet);

INCLUDE_ASM("asm/nonmatchings/ios/shockdriver", ShockDriver_GetShockVoice);

int Init_ShockEmulator(unsigned int idx, int val)
{
    int *base = (int *)D_00632190;
    if (idx >= (unsigned int)base[0]) return -1;
    ((int *)base[1])[idx] = val;
    return idx;
}

INCLUDE_ASM("asm/nonmatchings/ios/shockdriver", ShockEmulator_EmulationShot);

int ShockEmulator_EmulationWave(unsigned int idx)
{
    int *base = (int *)D_00632190;
    if (idx >= (unsigned int)base[0]) return -1;
    ((int *)base[1])[idx] = 0;
    return idx;
}

INCLUDE_ASM("asm/nonmatchings/ios/shockdriver", Init_ShockRequestAlloc);

int Get_ShockRequestStruct(unsigned idx) {
    int *base = (int *)D_00632190;
    if (idx >= (unsigned)base[0]) return 0;
    return ((int *)base[1])[idx];
}

INCLUDE_ASM("asm/nonmatchings/ios/shockdriver", Reset_ShockRequestStruct);

INCLUDE_ASM("asm/nonmatchings/ios/shockdriver", ShockRevice_Wave);

int Init_Shock(int a0, int a1)
{
    return a1;
}

