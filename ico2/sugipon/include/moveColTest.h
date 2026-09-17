/*
 * ico2/sugipon/include/moveColTest.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what moveColTest.c.inc defines, in the order the
 * coalescing TU's prototype block carried them; every type here is read from
 * the ROM's calling convention at the call sites.
 */

#ifndef MOVECOLTEST_H
#define MOVECOLTEST_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order moveColTest.c's inline tail has. */
short *InitMoveColTestGeo(int a0, int *self);

#endif /* MOVECOLTEST_H */
