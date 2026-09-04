#include "common.h"

typedef struct { char _0[0x128]; int f128; int f12C; char _130[0x64]; } GenRange;

typedef struct {
    char _0[0x42];
    unsigned char f42;
    char _43[3];
    unsigned char f46;
    char _47[1];
    unsigned int f48;
} GenElem;

typedef struct { char _0[8]; int f_8; char f_C; char _pad_d; char f_E; } GenGeo;


extern int D_006D0D40[];
INCLUDE_ASM("asm/nonmatchings/src/generator", CheckGeneratorCollision);

INCLUDE_ASM("asm/nonmatchings/src/generator", GetGeneratorSafePosition);

INCLUDE_ASM("asm/nonmatchings/src/generator", endfunc_BGA);

INCLUDE_ASM("asm/nonmatchings/src/generator", IsNeedGenerator);

INCLUDE_ASM("asm/nonmatchings/src/generator", CallEnemy);

extern void gamesysObjInfoUniqDataSet(void *a0);
extern void iosOmSendMail(void *a0, int a1, void *a2);

void Generator_QuickCall(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    GenGeo *q = *(GenGeo **)((char *)p + 0x800);
    *(int *)((char *)q + 0x50) = 1;
    gamesysObjInfoUniqDataSet(a0);
    iosOmSendMail(a0, 1, a0);
}

INCLUDE_ASM("asm/nonmatchings/src/generator", GetMotherGenerator);

INCLUDE_ASM("asm/nonmatchings/src/generator", ReadGeneratorPacket);

extern GenElem D_002A4C48[];

void MakeGeneratorPacket(void) {
    unsigned char *out = (unsigned char *)D_006D0D40;
    int i;
    for (i = 0; i <= 0xD7E; i++) {
        unsigned int v = D_002A4C48[i].f48;
        *out++ = (unsigned char)((((int)(v << 18) >> 28) << 4) | ((v >> 21) & 1));
    }
    for (i = 0; i <= 0xD7E; i++) {
        *out++ = (unsigned char)((D_002A4C48[i].f48 >> 18) & 1);
    }
    for (i = 0; i <= 0xD7E; i++) {
        *out++ = D_002A4C48[i].f42;
    }
}

INCLUDE_ASM("asm/nonmatchings/src/generator", generatorBeforeFunc);

INCLUDE_ASM("asm/nonmatchings/src/generator", GeneratorGeo);

INCLUDE_ASM("asm/nonmatchings/src/generator", GeneratorDL);

INCLUDE_ASM("asm/nonmatchings/src/generator", InitGeneratorGeo);

void Generator_Call(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    GenGeo *q = *(GenGeo **)((char *)p + 0x800);
    q->f_8++;
}

void Generator_ResetCount(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    GenGeo *q = *(GenGeo **)((char *)p + 0x800);
    q->f_E = 1;
}

void Generator_Mask(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    GenGeo *q = *(GenGeo **)((char *)p + 0x800);
    q->f_C = 1;
}

void Generator_MaskOff(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    GenGeo *q = *(GenGeo **)((char *)p + 0x800);
    q->f_C = 0;
}

extern GenRange D_005F2FB8[];
extern int D_00631990;

void SetMotherGenerator(int a0, int a1) {
    int gen;
    int i;
    int cnt;
    if (a0 == 0xD7D) return;
    gen = D_00631990;
    cnt = 0;
    for (i = D_005F2FB8[gen].f128; i < D_005F2FB8[gen].f12C; i++) {
        if (D_002A4C48[i].f46 == 0x21) {
            if (i == a1) {
                GenElem *m = &D_002A4C48[a0];
                m->f48 = ((int)m->f48 & -0x3C01) | ((cnt & 0xF) << 10);
                return;
            }
            cnt++;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/src/generator", Generator_Init);

int *GetbufpGeneratorPacket(void) {
    return D_006D0D40;
}

int GetsizeGeneratorPacket(void) {
    return 10365;
}

