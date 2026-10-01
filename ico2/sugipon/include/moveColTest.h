/*
 * ico2/sugipon/include/moveColTest.h
 *
 * The declarations of what moveColTest.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef MOVECOLTEST_H
#define MOVECOLTEST_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order moveColTest.c's inline tail has. */
short *InitMoveColTestGeo(int gobj, int *layout);

struct GObj;

void MoveColTestGeo(struct GObj *self);
void MoveColTestDL(int a0, int a1, int a2, int a3);

#endif /* MOVECOLTEST_H */
