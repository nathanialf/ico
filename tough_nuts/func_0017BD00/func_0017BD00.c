#include "common.h"

/* st25a 0x164 actor-state view (local) */
typedef struct { char _0[0x100]; int f_100, f_104, f_108; char _pad10c[0x21C]; int f_328, f_32C; char _pad330[0xC]; int f_33C; } St25State;

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", actSt25aQueenAppear);

extern int *isysGObjSearchFromObjLayoutID(int x);
extern void Generator_Mask(int *p);
extern int *isysGObjSearchFromObjKindID_begin(int *p);

void actSt25aQueenAppearChk(void)
{
    int *p = isysGObjSearchFromObjLayoutID(0x21);
    while (p != 0) {
        Generator_Mask(p);
        p = isysGObjSearchFromObjKindID_begin(p);
    }
}

extern int *isysGObjAddHead(void);
extern void iosOmBeforeFuncStandard(int a, int b, int c);
extern unsigned char D_002A0A90[];

void actConte11(void)
{
  char *new_var;
  int *p = isysGObjAddHead();
  if (p != 0)
  {
    iosOmBeforeFuncStandard((int) p, 0x26, (int) p);
    new_var = (char *) D_002A0A90;
    *((unsigned short *) ((new_var + (p[0x8 / 4] * 0x4C)) + 0x42)) = 0;
  }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", actSt25aQueenTalkChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", actConte12);

void actConte12Jimaku(void *a0) {
    St25State *p = *(St25State **)((char *)a0 + 0x164);
    p->f_33C = 0;
    p->f_100 = 0;
    p->f_104 = 0;
    p->f_108 = 0;
    p->f_32C = 0x7F;
    p->f_328 = 0x7F;
}


int actSt25aQueenDeadChk(void) {
    return isysGObjAddHead();
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", actConte13Jimaku);

extern int ExecMotionOrient(void *a0, int a1, void *a2);

void BoySekikaTexScroll(void *a0, int a1) {
    char *p = *(char **)((char *)a0 + 0x164);
    *(int *)(p + 0x110) = ExecMotionOrient(a0, a1, p + 0x610);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", actSt25aGenerator);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", actSt25aQueenBefore);

extern int D_0062C030;

void actSt25aQueenTalk(void) {
    D_0062C030 = 0;
}

extern int actItouQueenAttack(int a0, int a1, int a2, int a3, int a4, int a5);
int actSt25aQueenDead(int a0, int a1, int a2) {
    return actItouQueenAttack(a0, a1, a2, 0, 0, 0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", actItouQueenAttack);

extern int D_00629DF0;
extern void stgmgrForceSwitch(int a0, int a1, int a2, int a3);

int actSwordEff(int a0, int a1, int a2, int a3)
{
    int ret = 0;
    a1 = a1 & 0xFF;
    a2 = a2 & 0xFF;
    a3 = a3 & 0xFF;
    if (D_00629DF0 == 0) {
        if (D_0062C030 == 0) {
            stgmgrForceSwitch(a0, a1, a2, a3);
            D_0062C030 = 1;
            ret = 1;
        }
    }
    return ret;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", actSwordEffXL);

extern float D_0062BA7C;
extern int D_0062BA80, D_0062BA78;
extern unsigned char D_0062BA88, D_0062BA89, D_0062BA8A;

void actSt25aQueenBeforeChk(float a0, int a1, int a2, int a3) {
    D_0062BA78 = 1;
    D_0062BA7C = a0;
    D_0062BA80 = 1;
    D_0062BA88 = a1;
    D_0062BA89 = a2;
    D_0062BA8A = a3;
}

extern int D_0062BA78;
extern int D_0062BA80;

void actConte11Jimaku(float a0) {
    D_0062BA78 = 1;
    D_0062BA7C = -a0;
    D_0062BA80 = 0;
}

int actSt25aQueenDeadEvent(void) {
    int g = D_0062BA78;
    if (g == 0) {
        goto ret0;
    }
    if (g != 3) {
        goto ret1;
    }
ret0:
    return 0;
ret1:
    return 1;
}

extern int *D_00629DE4;
extern int checkHit(int a0);

int actItouQueenAttackChk(void) {
    int *p = (int *)D_00629DE4[0x59];
    int v = p[0x4C];
    if (v == 0) {
        return 0;
    }
    return checkHit(v);
}

extern int func_001BDF80(void);

int func_0017BCC0(void) {
    return func_001BDF80();
}

extern int ACTGameCollisionOn(void);

int func_0017BCE0(void) {
    return ACTGameCollisionOn() != 0;
}

typedef struct{int _0,_4,f8;}S;int func_0017BD00(int a0, int a1) {
    int p = ACTGameCollisionOn();
    return p ? *(int *)(p + 8) == a1 : 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", func_0017BD40);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", func_0017BE60);

extern void MatrixDrive_TurnObjectMatrix(void *a0, float *a1);

void func_0017BF18(char *a0, float x, float y, float z) {
    float v[4] = {x, y, z, 0};
    int p = *(int *)(a0 + 0x15C);
    MatrixDrive_TurnObjectMatrix((void *)(p + 0x660), v);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", func_0017BF50);
