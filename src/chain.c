#include "common.h"



extern int D_00632744;
extern int D_006D0680[];
extern int D_00632D30;
extern int D_00632730;

void *UpdateRootPosition(void) {
    if (D_00632730 == 0) {
        return 0;
    }
    return D_006D0680;
}

union PendCopy {
    float f[8];
    long long q[4];
};

void GetCameraInfo_tmp(void *dst, float *out) {
    union PendCopy *s = (union PendCopy *)D_006D0680;
    union PendCopy *d = (union PendCopy *)dst;
    d->q[0] = s->q[0];
    d->q[1] = s->q[1];
    d->q[2] = s->q[2];
    d->q[3] = s->q[3];
    *out = D_00632D30 / 100.0f;
}

extern unsigned char D_00633D8D;

void collisionCheck(void) {
    D_00633D8D = 1;
}

extern int D_00632704;

void chain_simulate_term_simple(void) {
    D_00632704 = 1;
}

void chain_simulate_term_loop(void) {
    D_00632744 = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/chain", chain_simulate_term_swingready);

INCLUDE_ASM("asm/nonmatchings/src/chain", chain_simulate_term_swingstart);
ASM_LIT4_SLOT(D_00630F00, -0.2f);
ASM_LIT4_SLOT(D_00630F04, 0.1f);

/* chain .rodata run 0x55AA90..0x55ADE0 -- byte-verified against baseelf;
 * defs interleave with INCLUDE_ASM stubs so .o section order == VMA order */
const char D_0055AA90[0x10] = "src/chain.c\0\0\0\0\0";
const char D_0055AAA0[0x10] = "nearestNode!=-1\0";

INCLUDE_ASM("asm/nonmatchings/src/chain", chain_simulate_term_moveup);

INCLUDE_ASM("asm/nonmatchings/src/chain", chain_simulate_term_free);
ASM_LIT4_SLOT(D_00630F08, 3.14159274f);
ASM_LIT4_SLOT(D_00630F0C, 0.6f);

INCLUDE_ASM("asm/nonmatchings/src/chain", chain_simulate_term_down);
ASM_LIT4_SLOT(D_00630F10, -0.01f);
ASM_LIT4_SLOT(D_00630F14, -0.05f);
ASM_LIT4_SLOT(D_00630F18, -0.15f);

INCLUDE_ASM("asm/nonmatchings/src/chain", chain_simulate_hangstart);
ASM_LIT4_SLOT(D_00630F1C, -0.01f);
ASM_LIT4_SLOT(D_00630F20, -0.05f);
ASM_LIT4_SLOT(D_00630F24, -0.15f);

INCLUDE_ASM("asm/nonmatchings/src/chain", chain_simulate_term);
ASM_LIT4_SLOT(D_00630F28, -0.01f);
ASM_LIT4_SLOT(D_00630F2C, -0.2f);
ASM_LIT4_SLOT(D_00630F30, -0.3f);

INCLUDE_RODATA("asm/nonmatchings/src/chain", D_0055AB20);

INCLUDE_ASM("asm/nonmatchings/src/chain", chain_simulate_stop);
ASM_LIT4_SLOT(D_00630F34, -0.05f);
ASM_LIT4_SLOT(D_00630F38, -0.15f);
ASM_LIT4_SLOT(D_00630F3C, -1.57079637f);

INCLUDE_RODATA("asm/nonmatchings/src/chain", D_0055AB48);
INCLUDE_RODATA("asm/nonmatchings/src/chain", D_0055AB50);
const char D_0055AB58[0x20] = "chain_simulate_term_free\n\0\0\0\0\0\0\0";
INCLUDE_RODATA("asm/nonmatchings/src/chain", D_0055AB78);
INCLUDE_RODATA("asm/nonmatchings/src/chain", D_0055AB80);
const char D_0055AB88[0x20] = "chain_simulate_hangstart\n\0\0\0\0\0\0\0";
const char D_0055ABA8[0x18] = "chain_simulate_term\n\0\0\0\0";

INCLUDE_ASM("asm/nonmatchings/src/chain", chain_simulate_free);
ASM_LIT4_SLOT(D_00630F40, -0.01f);
ASM_LIT4_SLOT(D_00630F44, -0.05f);
ASM_LIT4_SLOT(D_00630F48, -0.15f);

INCLUDE_ASM("asm/nonmatchings/src/chain", correct_vector);
ASM_LIT4_SLOT(D_00630F4C, -0.01f);
ASM_LIT4_SLOT(D_00630F50, -0.05f);
ASM_LIT4_SLOT(D_00630F54, -0.15f);
ASM_LIT4_SLOT(D_00630F58, -1.57079637f);

extern int D_00632CBC;
extern int D_00633DA0;
extern void traceLine(int a, int b, int c, const char *d);
extern void chain_simulate_term_free(int a0);

void pendulum_Process(int a0) {
    void *p = *(void **)((char *)a0 + 0x15C);
    void *q = *(void **)((char *)p + 0x800);
    if (D_00632CBC & 1) {
        D_00633DA0 = D_00633DA0 + 0xA;
        traceLine(0xA, D_00633DA0, 0x0FFFFFFF, D_0055AB88);
    }
    *(float *)((char *)q + 0x44) = -0.05f;
    chain_simulate_term_free(a0);
}

extern int D_00632CBC;
extern int D_00633DA0;
extern void chain_simulate_term_free(int a0);
extern void traceLine(int a, int b, int c, const char *d);

void InitChainGeo(int a0)
{
    if (D_00632CBC & 1) {
        D_00633DA0 = D_00633DA0 + 0xA;
        traceLine(0xA, D_00633DA0, 0x0FFFFFFF, D_0055ABA8);
    }
    chain_simulate_term_free(a0);
}

INCLUDE_ASM("asm/nonmatchings/src/chain", chain_simulate_climb);

INCLUDE_ASM("asm/nonmatchings/src/chain", chain_set_charachara);
ASM_LIT4_SLOT(D_00630F60, 0.675f);

INCLUDE_ASM("asm/nonmatchings/src/chain", ChainGeo);
ASM_LIT4_SLOT(D_00630F64, 3.14159274f);

INCLUDE_ASM("asm/nonmatchings/src/chain", ChainDL);
ASM_LIT4_SLOT(D_00630F68, 0.2f);

const char D_0055AC60[0x40] = "º¿¤ÎÄ¹¤µ¤¬Ã»¤«¤¹¤®¤Þ¤¹(ÇÛÃÖÉ½¤ÎY-scale¤Ç»ØÄê¤·¤Þ¤¹)\0\0\0\0\0\0\0\0\0\0\0\0\0";
const unsigned int D_0055ACA0[0x4] = { 0x00000000, 0x00000000, 0xC1C80000, 0x3F800000 };
const unsigned int D_0055ACB0[0x4] = { 0x00000000, 0x00000000, 0x41C80000, 0x3F800000 };
const char D_0055ACC0[0x68] = "\033[33mº¿¤Î¾å¤ÎÊÉ¤ò¸«ÉÕ¤±¤ë¤³¤È¤¬¤Ç¤­¤Þ¤»¤ó¡£\nÊý¸þ¤¬´Ö°ã¤Ã¤Æ¤¤¤ë¤«¡¢ÊÉ¤¬Ìµ¤¤¤È¤³¤í¤ËÃÖ¤¤¤Æ¤¤¤Þ¤»¤ó¤«?\033[m\n\0";

INCLUDE_ASM("asm/nonmatchings/src/chain", GetPositionOnTheChain);
ASM_LIT4_SLOT(D_00630F6C, 3.14159274f);

INCLUDE_ASM("asm/nonmatchings/src/chain", TestChainUpDown);
ASM_LIT4_SLOT(D_00630F70, 3.14159274f);

INCLUDE_ASM("asm/nonmatchings/src/chain", func_0018ECC8);
ASM_LIT4_SLOT(D_00630F74, -0.2f);
ASM_LIT4_SLOT(D_00630F78, 0.1f);
ASM_LIT4_SLOT(D_00630F7C, -0.2f);
ASM_LIT4_SLOT(D_00630F80, 0.1f);

INCLUDE_ASM("asm/nonmatchings/src/chain", ReleaseChain);

INCLUDE_ASM("asm/nonmatchings/src/chain", GetChainPendulum);

INCLUDE_ASM("asm/nonmatchings/src/chain", IncreasePdlChain);

INCLUDE_ASM("asm/nonmatchings/src/chain", DecreasePdlChain);

/* chain 0x800 view (local) */
typedef struct {
    int f_0; char _pad4[0x1C];
    float f_20, f_24, f_28; char _pad2C[0x18];
    float f_44; char _pad48[0x18];
    char f_60; char _pad61[7];
    int f_68; unsigned char f_6C; char _pad6D[3];
    float f_70; int f_74; char _pad78[0x28];
    unsigned char f_A0; char _padA1[0xF];
    float f_B0, f_B4, f_B8; char _padBC[4];
    unsigned char f_C0;
} ChainGeoL;

extern void chain_simulate_term_swingstart(void *a0);

void PlumbOrientUpdateChain(void *a0) {
    ChainGeoL *p = *(ChainGeoL **)(*(char **)((char *)a0 + 0x15C) + 0x800);
    chain_simulate_term_swingstart(a0);
    p->f_60 = 1;
}

void isBottomOfChain(void *a0) {
    void *p = *(void **)((char *)a0 + 0x15C);
    ChainGeoL *q = *(ChainGeoL **)((char *)p + 0x800);
    q->f_60 = 0;
}

void isStopChain(void *a0, float *a1, float *a2, float *a3) {
    ChainGeoL *p = *(ChainGeoL **)(*(char **)((char *)a0 + 0x15C) + 0x800);
    *a1 = *(float *)((char *)p + 0x30);
    *a2 = *(float *)((char *)p + 0x34);
    if (*(float *)((char *)p + 0x48) < *(float *)((char *)p + 0x34)) {
        *a2 = *(float *)((char *)p + 0x48);
    }
    *a3 = *(float *)((char *)p + 0x40);
}


void GetChainClimbOrient(void *a0) {
    void *p = *(void **)((char *)a0 + 0x15C);
    ChainGeoL *q = *(ChainGeoL **)((char *)p + 0x800);
    q->f_44 = 0.1f;
}

extern int D_00632D98;

void CheckChainClimbablePos(void *a0) {
    ChainGeoL *p = *(ChainGeoL **)(*(char **)((char *)a0 + 0x15C) + 0x800);
    p->f_44 = (float)D_00632D98 * 0.5f * -0.1f;
}

void GetChainClimbCollision(void *a0, float *a1) {
    void *p = *(void **)((char *)a0 + 0x15C);
    ChainGeoL *q = *(ChainGeoL **)((char *)p + 0x800);
    q->f_20 = a1[0];
    q->f_24 = a1[1];
    q->f_28 = a1[2];
}

int SetChainParentGObj(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    ChainGeoL *q = *(ChainGeoL **)((char *)p + 0x800);
    return q->f_68 == q->f_74 - 1;
}

int GetChainDirCorrectVal(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    ChainGeoL *q = *(ChainGeoL **)((char *)p + 0x800);
    return q->f_C0;
}

void GetRootPositionHandExtra(float *a0, void *a1) {
    void *p = *(void **)((char *)a1 + 0x15C);
    ChainGeoL *q = *(ChainGeoL **)((char *)p + 0x800);
    a0[0] = q->f_B0;
    a0[1] = q->f_B4;
    a0[2] = q->f_B8;
}

int InitPendulum(void *a0) {
    void *p = *(void **)((char *)a0 + 0x15C);
    ChainGeoL *q = *(ChainGeoL **)((char *)p + 0x800);
    if (q->f_A0) {
        if (q->f_68 < 3) {
            return 1;
        }
    }
    return 0;
}

typedef struct { unsigned int lo; unsigned char m[3]; unsigned char hi; } Blk8;
typedef struct { Blk8 a; int b; } Geo12;

void LockChainGeo(char *a0, void *a1) {
    int *p = *(int **)((char *)a1 + 0x15C);
    ChainGeoL *q = *(ChainGeoL **)((char *)p + 0x800);
    *(Geo12 *)a0 = *(Geo12 *)((char *)q + 0xA4);
}

void UnLockChainGeo(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    ChainGeoL *q = *(ChainGeoL **)((char *)p + 0x800);
    q->f_0 = a1;
}


int func_00190440(void *a0, int *out)
{
    void *p = *(void **)((char *)a0 + 0x15C);
    ChainGeoL *q = *(ChainGeoL **)((char *)p + 0x800);
    *out = (int)(q->f_70 * 180.0f / 3.1415927f);
    return q->f_6C;
}


/* .data â€” carved VMA 0X28AFB0..0X28B100 (3 symbols), bytes verified against baserom/baseelf.rom */
unsigned int D_0028AFB0[16] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x43B40000, 0x42340000,
    0x00000001, 0x00000000, 0x00000000, 0x00000000,
};
unsigned int D_0028AFF0[56] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0xFFFFFFFF, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000001, 0x00000000, 0x428C0000, 0x00000100,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};
unsigned int D_0028B0D0[12] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0xFFFFFFFF, 0x00000000,
};

/* .sdata â€” carved VMA 0X632758..0X632770 (4 symbols), bytes verified against baserom/baseelf.rom */
unsigned int D_00632758[2] = {
    0x7F7FFFFF, 0x00000000,
};
unsigned int D_00632760[2] = {
    0x00000030, 0x00000000,
};
unsigned int D_00632768 = 0x000A6425;
unsigned int D_0063276C = 0x7F7FFFFF;
