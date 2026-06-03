#include "common.h"

extern void (*jtbl_0062A6D0)(void *a0, int a1);
extern void (*D_0062A6D4)(void *a0, int a1);

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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fieldCollision", MakeExitAttributeIndex);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fieldCollision", ClipFloorByGObj);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fieldCollision", ClipWallDebug);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fieldCollision", ClipWall);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fieldCollision", ClipWallR);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fieldCollision", ClipWallWaveForce);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fieldCollision", ClipWallFuchiHangWalkStop);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fieldCollision", ClipWallField);

void ClipWallEField(void *a0) {
    jtbl_0062A6D0(a0, 0);
    __asm__ __volatile__("");
}

void ClipWallBoxStop(void *a0) {
    jtbl_0062A6D0(a0, 0x1);
    __asm__ __volatile__("");
}

void ClipWallAdjustPos(void *a0) {
    jtbl_0062A6D0(a0, 0x2);
    __asm__ __volatile__("");
}

void ClipWallE(void *a0) {
    jtbl_0062A6D0(a0, 0x6);
    __asm__ __volatile__("");
}

void ClipWallCheckCB(void *a0) {
    jtbl_0062A6D0(a0, 0x7);
    __asm__ __volatile__("");
}

void ClipWallFieldCheckCB(void *a0) {
    jtbl_0062A6D0(a0, 0x3);
    __asm__ __volatile__("");
}

void ClipFloor(void *a0) {
    jtbl_0062A6D0(a0, 0x5);
    __asm__ __volatile__("");
}

void ClipFloorE(void *a0) {
    jtbl_0062A6D0(a0, 0xA);
    __asm__ __volatile__("");
}

void ClipFloorR(void *a0) {
    jtbl_0062A6D0(a0, 0xB);
    __asm__ __volatile__("");
}

void ClipFloorIH(void *a0) {
    jtbl_0062A6D0(a0, 0x4);
    __asm__ __volatile__("");
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fieldCollision", ClipFloorCheckCB);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fieldCollision", ClipCollision);

void ChangeFieldCollisionDebugMode(void *a0) {
    D_0062A6D4(a0, 0xC);
    __asm__ __volatile__("");
}

void LoadCollision(void *a0) {
    D_0062A6D4(a0, 0xD);
    __asm__ __volatile__("");
}

void DrawCollision(void *a0) {
    D_0062A6D4(a0, 0xE);
    __asm__ __volatile__("");
}

void ClipPlane(void *a0) {
    D_0062A6D4(a0, 0xF);
    __asm__ __volatile__("");
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fieldCollision", GetOrientOfWall);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fieldCollision", SetSimplePlane);
