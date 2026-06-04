#include "common.h"

extern int (*jtbl_0062A6D0)(void *a0, int a1);
extern int D_0062C024;
extern int (*D_0062A6D4)(void *a0, int a1);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fieldCollision", MakeCollisionDependGObjList);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fieldCollision", GetReflectionElement);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fieldCollision", clip_wall_1);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fieldCollision", clip_floor_1);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fieldCollision", DispCollisionPC);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fieldCollision", makeCollisionBlockTable);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fieldCollision", _Clip);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fieldCollision", __ClipWall);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fieldCollision", __ClipFloor);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fieldCollision", DrawGObjWallCollision);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fieldCollision", DrawGObjFloorCollision);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fieldCollision", DBG_VECTOR);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fieldCollision", GetEdgeOfFloor);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fieldCollision", DrawCollisionRay);

extern int GetEdgeOfFloor(void *a0);
typedef struct { unsigned int lo; unsigned char m[3]; unsigned char hi; } FcBlk8;
extern FcBlk8 D_0062A6A0;

void MakeExitAttributeIndex(void *a0) {
    *(int *)((char *)a0 + 0x94) = 0;
    *(FcBlk8 *)((char *)a0 + 0x8C) = D_0062A6A0;
    GetEdgeOfFloor(a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fieldCollision", ClipFloorByGObj);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fieldCollision", ClipWallDebug);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fieldCollision", ClipWall);

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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fieldCollision", SetSimplePlane);


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
