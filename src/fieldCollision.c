#include "common.h"

#include "ico/types.h"

typedef struct { unsigned int lo; unsigned char m[3]; unsigned char hi; } FcBlk8;



extern char D_002A4C48[];
extern void _ACTWait();
extern void debug_assertMessage();
extern char D_00558F68[];
extern char D_00558F50[];
extern int ExecMotionOrient(int a0, int a1, int a2);
extern void _ACTWait(int a0);

void MakeCollisionDependGObjList(volatile int a0) {
    int gobj = *(int *)(a0 + 0x164);
    int r;
    debug_assertMessage(D_00558F50);
    r = ExecMotionOrient(a0, 0xC, gobj + 0x610);
    *(int *)(gobj + 0x120) = r;
    *(int *)(r + 0x114) = 0;
    _ACTWait(0);
}

void GetReflectionElement(volatile unsigned int a0)
{
  int *new_var;
  volatile int local;
  int *s0;
  new_var = *((int **) (a0 + 0x164));
  debug_assertMessage(D_00558F68);
  s0 = new_var;
  s0[0x30 / 4] = 0x4;
  _ACTWait(0);
}

extern void *isysGObjSearchFromObjLayoutID(int a0);
extern void *isysGObjSearchFromObjKindID_begin(void *a0);
void *clip_wall_1(void *a0) {
    void *obj = isysGObjSearchFromObjLayoutID(4);
    while (obj != 0) {
        if (obj != a0) {
            char *p = *(char **)((char *)obj + 0x164);
            if (*(int *)(p + 0x30) == 0xF) return obj;
            if ((int)(*(long long *)(p + 0x20) >> 1) & 1) return obj;
        }
        obj = isysGObjSearchFromObjKindID_begin(obj);
    }
    return 0;
}

int clip_floor_1(int *a0)
{
    int *p = (int *)(D_002A4C48 + a0[2] * 0x4C);
    return (((unsigned int)p[0x48 / 4] >> 21) & 1) ^ 1;
}

extern int ChangeBrain_ToKidnap(void *a0, int a1, int a2, int a3, unsigned char a4, float a5);
extern int func_00163B40(void *a0, int a1, int a2, int a3, unsigned char a4, float a5);

int DispCollisionPC(void *a0, int a1, int a2, int a3, unsigned char a4, float a5)
{
    int brain = *(int *)(*(int *)((char *)a0 + 0x164) + 0x670);
    if (*(int *)(brain + 0x1DC) != 3)
        return ChangeBrain_ToKidnap(a0, a1, a2, a3, a4, a5);
    return func_00163B40(a0, a1, a2, a3, a4, a5);
}

unsigned int makeCollisionBlockTable(unsigned int a0)
{
  volatile unsigned int local = a0;
  unsigned int v = local;
 do { *((int *) ((*((int *) (v + 0x15C))) + 0x550)) = 0; } while (0);
  *((int *) ((*((int *) (v + 0x15C))) + 0x380)) = 0;
  return v;
}

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", _Clip);

extern float MatrixDrive_GetTurnZAngleYX(void *a0, void *a1);
extern void MatrixDrive_TurnObjectMatrix(void *a0, void *a1);
extern float func_00168BA0(void *a0, void *a1);
extern void func_00243AD0(void *a0, void *a1, void *a2);
extern void func_00243AE8(void *a0, void *a1, void *a2);
extern void func_00243B18(void *a0, void *a1, float a2);
extern void func_00244448(void *a0, void *a1, float a2);

void __ClipWall(char *a0, float arg0, float arg1) {
    float buf0[4];
    float L10[4];
    float L20[4];
    float z;

    MatrixDrive_TurnObjectMatrix(L10, a0 + 0xA0);
    *(int *) &L10[3] = 0;
    func_00243AE8(buf0, a0 + 0x10, a0);
    func_00243B18(a0 + 0x30, L10, -func_00168BA0(L10, buf0));
    func_00243AD0(a0 + 0x40, buf0, a0 + 0x30);
    func_00244448(a0 + 0x30, a0 + 0x30, arg1);
    func_00244448(a0 + 0x40, a0 + 0x40, arg0);
    func_00243AD0(a0 + 0x60, a0 + 0x40, a0 + 0x30);
    {
        float *p20 = L20;
        z = MatrixDrive_GetTurnZAngleYX(a0 + 0x20, a0 + 0x10);
        func_00243B18(p20, a0 + 0x60, z / MatrixDrive_GetTurnZAngleYX(a0, a0 + 0x10));
        func_00243AD0(a0 + 0x50, a0 + 0x20, p20);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", __ClipFloor);

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", DrawGObjWallCollision);

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", DrawGObjFloorCollision);

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", DBG_VECTOR);

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", GetEdgeOfFloor);

extern FcBlk8 D_006323C0;
extern int GetEdgeOfFloor(void *a0);

void DrawCollisionRay(char *a0) {
    *(int *)(a0 + 0xB0) = 0;
    *(int *)(a0 + 0x94) = 0;
    *(int *)(a0 + 0x88) = 0;
    *(FcBlk8 *)(a0 + 0x80) = D_006323C0;
    GetEdgeOfFloor(a0);
}

void MakeExitAttributeIndex(void *a0) {
    *(int *)((char *)a0 + 0x94) = 0;
    *(FcBlk8 *)((char *)a0 + 0x8C) = D_006323C0;
    GetEdgeOfFloor(a0);
}

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", ClipFloorByGObj);

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", ClipWallDebug);

extern char D_005592D0[];
extern int func_00263FB0(float f);

void ClipWall(float *vec)
{
    return debug_assertMessage(D_005592D0, func_00263FB0(vec[0]),
                         func_00263FB0(vec[1]), func_00263FB0(vec[2]));
}

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", ClipWallR);

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", ClipWallWaveForce);

extern char D_00559400[];
extern char D_00559420[];
extern int D_00631960;
extern int D_006323C8;
extern int D_00633D04;
extern int D_00633D38;
extern void *D_006AAC80[];
extern void *D_006AB100[];

void ClipWallFuchiHangWalkStop(void) {
    int i;
    char *entry;
    int j;
    int n;
    int *p70;
    void *obj;
    int slot;

    debug_assertMessage(D_00559400, D_00631960);
    D_00633D38 = 0;
    i = 0xF;
    do {
        D_006AB100[i] = 0;
        i--;
    } while (i >= 0);
    D_00633D04 = 0;
    obj = D_006AAC80[0];
    if (D_006323C8 > 0) {
        do {
            p70 = (int *)GOBJ_SUB(obj)->f_70;
            for (j = 0; j < p70[0xC / 4]; j++) {
                entry = (char *)p70[0x14 / 4] + j * 0x70;
                slot = *(int *)(entry + 0x60) & 0xF;
                if (slot != 0) {
                    if (D_006AB100[slot] == 0) {
                        debug_assertMessage(D_00559420, slot);
                        D_00633D38 = D_00633D38 + 1;
                        D_006AB100[slot] = entry;
                    }
                }
            }
            D_00633D04 = D_00633D04 + 1;
            obj = D_006AAC80[D_00633D04];
        } while (D_00633D04 < D_006323C8);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", ClipWallField);

extern int (*D_006323F0)(void *a0, int a1);

int ClipWallEField(void *a0) {
    return D_006323F0(a0, 0);
}

int ClipWallBoxStop(void *a0) {
    return D_006323F0(a0, 0x1);
}

int ClipWallAdjustPos(void *a0) {
    return D_006323F0(a0, 0x2);
}

int ClipWallE(void *a0) {
    return D_006323F0(a0, 0x6);
}

int ClipWallCheckCB(void *a0) {
    return D_006323F0(a0, 0x7);
}

int ClipWallFieldCheckCB(void *a0) {
    return D_006323F0(a0, 0x3);
}

int ClipFloor(void *a0) {
    return D_006323F0(a0, 0x5);
}

int ClipFloorE(void *a0) {
    return D_006323F0(a0, 0xA);
}

int ClipFloorR(void *a0) {
    return D_006323F0(a0, 0xB);
}

int ClipFloorIH(void *a0) {
    return D_006323F0(a0, 0x4);
}

extern int D_00633D34;

void ClipFloorCheckCB(void *a0, int a1) {
    D_00633D34 = a1;
    D_006323F0(a0, 8);
}

void ClipCollision(void *a0, int a1) {
    D_00633D34 = a1;
    D_006323F0(a0, 9);
}

extern int (*D_006323F4)(void *a0, int a1);

int ChangeFieldCollisionDebugMode(void *a0) {
    return D_006323F4(a0, 0xC);
}

int LoadCollision(void *a0) {
    return D_006323F4(a0, 0xD);
}

int DrawCollision(void *a0) {
    return D_006323F4(a0, 0xE);
}

int ClipPlane(void *a0) {
    return D_006323F4(a0, 0xF);
}

extern int D_00633D34;

void GetOrientOfWall(void *a0, int a1) {
    D_00633D34 = a1;
    D_006323F4(a0, 0x10);
}

extern void func_00243B60(int *dst, int *src);

void SetSimplePlane(int *self)
{
    int buf[4];
    int *p10 = self + 4;
    func_00243B60(buf, p10);
    D_006323F0((int)self, 1);
    func_00243B60(p10, self + 8);
    D_006323F4((int)self, 0xC);
    func_00243B60(p10, buf);
}

