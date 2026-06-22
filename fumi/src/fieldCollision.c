#include "common.h"
#include "ico/types.h"

extern int (*jtbl_0062A6D0)(void *a0, int a1);
extern int D_0062C024;

extern int (*D_0062A6D4)(void *a0, int a1);
INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fieldCollision", MakeCollisionDependGObjList);

extern void debug_assertMessage();
extern void _ACTWait(int a0);
extern char D_00553268[];

void GetReflectionElement(volatile unsigned int a0)
{
  volatile int local;
  int *new_var;
  int *s0;
  new_var = *((int **) (a0 + 0x164));
  debug_assertMessage(D_00553268);
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
            if (*(int *)(p + 0x20) & 1) return obj;
        }
        obj = isysGObjSearchFromObjKindID_begin(obj);
    }
    return 0;
}

typedef struct { char _[0x48]; unsigned int f48; } NestEntry;
extern NestEntry D_002A0A90[];

int clip_floor_1(int *a0) {
    NestEntry *t = D_002A0A90;
    int idx = a0[2];
    return ((t[idx].f48 >> 21) & 1) ^ 1;
}

extern int ChangeBrain_ToKidnap(void *a0, int a1, int a2, int a3, unsigned char a4, float a5);
extern int func_00161998(void *a0, int a1, int a2, int a3, unsigned char a4, float a5);

int DispCollisionPC(void *a0, int a1, int a2, int a3, unsigned char a4, float a5)
{
    int brain = *(int *)(*(int *)((char *)a0 + 0x164) + 0x670);
    if (*(int *)(brain + 0x1DC) != 3)
        return ChangeBrain_ToKidnap(a0, a1, a2, a3, a4, a5);
    return func_00161998(a0, a1, a2, a3, a4, a5);
}



void makeCollisionBlockTable(int a0) {
    int base = *(volatile int *)&a0;
    GOBJ_SUB(base)->f_540 = 0;
    GOBJ_SUB(base)->f_370 = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fieldCollision", _Clip);

extern void MatrixDrive_TurnObjectMatrix(void *a0, void *a1);
extern float MatrixDrive_GetTurnZAngleYX(void *a0, void *a1);
extern float func_001669D0(void *a0, void *a1);
extern void func_0023FFF0(void *a0, void *a1, void *a2);
extern void func_00240008(void *a0, void *a1, void *a2);
extern void func_00240038(void *a0, void *a1, float a2);
extern void func_00240968(void *a0, void *a1, float a2);

void __ClipWall(char *a0, float arg0, float arg1) {
    float buf0[4];
    float L10[4];
    float L20[4];
    float z;

    MatrixDrive_TurnObjectMatrix(L10, a0 + 0xA0);
    *(int *) &L10[3] = 0;
    func_00240008(buf0, a0 + 0x10, a0);
    func_00240038(a0 + 0x30, L10, -func_001669D0(L10, buf0));
    func_0023FFF0(a0 + 0x40, buf0, a0 + 0x30);
    func_00240968(a0 + 0x30, a0 + 0x30, arg1);
    func_00240968(a0 + 0x40, a0 + 0x40, arg0);
    func_0023FFF0(a0 + 0x60, a0 + 0x40, a0 + 0x30);
    {
        float *p20 = L20;
        z = MatrixDrive_GetTurnZAngleYX(a0 + 0x20, a0 + 0x10);
        func_00240038(p20, a0 + 0x60, z / MatrixDrive_GetTurnZAngleYX(a0, a0 + 0x10));
        func_0023FFF0(a0 + 0x50, a0 + 0x20, p20);
    }
}


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fieldCollision", __ClipFloor);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fieldCollision", DrawGObjWallCollision);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fieldCollision", DrawGObjFloorCollision);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fieldCollision", DBG_VECTOR);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fieldCollision", GetEdgeOfFloor);

extern int GetEdgeOfFloor(void *a0);
typedef struct { unsigned int lo; unsigned char m[3]; unsigned char hi; } FcBlk8;
extern FcBlk8 D_0062A6A0;

void DrawCollisionRay(char *a0) {
    *(int *)(a0 + 0xB0) = 0;
    *(int *)(a0 + 0x94) = 0;
    *(int *)(a0 + 0x88) = 0;
    *(FcBlk8 *)(a0 + 0x80) = D_0062A6A0;
    GetEdgeOfFloor(a0);
}

void MakeExitAttributeIndex(void *a0) {
    *(int *)((char *)a0 + 0x94) = 0;
    *(FcBlk8 *)((char *)a0 + 0x8C) = D_0062A6A0;
    GetEdgeOfFloor(a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fieldCollision", ClipFloorByGObj);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fieldCollision", ClipWallDebug);

extern int func_00260340(float f);

extern char D_005535C0[];

void ClipWall(float *vec)
{
    return debug_assertMessage(D_005535C0, func_00260340(vec[0]),
                         func_00260340(vec[1]), func_00260340(vec[2]));
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fieldCollision", ClipWallR);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fieldCollision", ClipWallWaveForce);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fieldCollision", ClipWallFuchiHangWalkStop);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fieldCollision", ClipWallField);

int ClipWallEField(void *a0) {
    return jtbl_0062A6D0(a0, 0);
}

int ClipWallBoxStop(void *a0) {
    return jtbl_0062A6D0(a0, 0x1);
}

int ClipWallAdjustPos(void *a0) {
    return jtbl_0062A6D0(a0, 0x2);
}

int ClipWallE(void *a0) {
    return jtbl_0062A6D0(a0, 0x6);
}

int ClipWallCheckCB(void *a0) {
    return jtbl_0062A6D0(a0, 0x7);
}

int ClipWallFieldCheckCB(void *a0) {
    return jtbl_0062A6D0(a0, 0x3);
}

int ClipFloor(void *a0) {
    return jtbl_0062A6D0(a0, 0x5);
}

int ClipFloorE(void *a0) {
    return jtbl_0062A6D0(a0, 0xA);
}

int ClipFloorR(void *a0) {
    return jtbl_0062A6D0(a0, 0xB);
}

int ClipFloorIH(void *a0) {
    return jtbl_0062A6D0(a0, 0x4);
}

void ClipFloorCheckCB(void *a0, int a1) {
    D_0062C024 = a1;
    jtbl_0062A6D0(a0, 8);
}

void ClipCollision(void *a0, int a1) {
    D_0062C024 = a1;
    jtbl_0062A6D0(a0, 9);
}

int ChangeFieldCollisionDebugMode(void *a0) {
    return D_0062A6D4(a0, 0xC);
}

int LoadCollision(void *a0) {
    return D_0062A6D4(a0, 0xD);
}

int DrawCollision(void *a0) {
    return D_0062A6D4(a0, 0xE);
}

int ClipPlane(void *a0) {
    return D_0062A6D4(a0, 0xF);
}

void GetOrientOfWall(void *a0, int a1) {
    D_0062C024 = a1;
    D_0062A6D4(a0, 0x10);
}

extern void func_00240080(int *dst, int *src);

void SetSimplePlane(int *self)
{
    int buf[4];
    int *p10 = self + 4;
    func_00240080(buf, p10);
    jtbl_0062A6D0((int)self, 1);
    func_00240080(p10, self + 8);
    D_0062A6D4((int)self, 0xC);
    func_00240080(p10, buf);
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
    unsigned int       f_C;  /* 0x0C */
} S_0027EA00;  /* stride 0x10 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_006A4740;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_006A4BC0;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0062A6D0;  /* stride 0x4 */

/* end struct shapes */
