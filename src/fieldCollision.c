#include "common.h"



extern char D_002A4C48[];
extern void _ACTWait();
extern void debug_assertMessage();
extern char D_00558F68[];
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", MakeCollisionDependGObjList);

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

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", clip_wall_1);

int clip_floor_1(int *a0)
{
    int *p = (int *)(D_002A4C48 + a0[2] * 0x4C);
    return (((unsigned int)p[0x48 / 4] >> 21) & 1) ^ 1;
}

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", DispCollisionPC);

unsigned int makeCollisionBlockTable(unsigned int a0)
{
  volatile unsigned int local = a0;
  unsigned int v = local;
 do { *((int *) ((*((int *) (v + 0x15C))) + 0x550)) = 0; } while (0);
  *((int *) ((*((int *) (v + 0x15C))) + 0x380)) = 0;
  return v;
}

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", _Clip);

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", __ClipWall);

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", __ClipFloor);

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", DrawGObjWallCollision);

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", DrawGObjFloorCollision);

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", DBG_VECTOR);

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", GetEdgeOfFloor);

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", DrawCollisionRay);

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", MakeExitAttributeIndex);

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", ClipFloorByGObj);

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", func_00167280);

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", ClipWallDebug);

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", ClipWall);

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", ClipWallR);

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", ClipWallWaveForce);

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", ClipWallFuchiHangWalkStop);

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", ClipWallField);

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", ClipWallEField);

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", ClipWallBoxStop);

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", ClipWallAdjustPos);

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", ClipWallE);

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", ClipWallCheckCB);

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", ClipWallFieldCheckCB);

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", ClipFloor);

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", ClipFloorE);

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", ClipFloorR);

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", ClipFloorIH);

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", ClipFloorCheckCB);

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", ClipCollision);

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", ChangeFieldCollisionDebugMode);

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", LoadCollision);

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", DrawCollision);

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", ClipPlane);

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", GetOrientOfWall);

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", SetSimplePlane);

