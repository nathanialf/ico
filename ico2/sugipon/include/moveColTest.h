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
short *InitMoveColTestGeo(int a0, int *self);

#endif /* MOVECOLTEST_H */
