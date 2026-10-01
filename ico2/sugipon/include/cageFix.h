/*
 * ico2/sugipon/include/cageFix.h
 *
 * The declarations of what cageFix.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef CAGEFIX_H
#define CAGEFIX_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order cageFix.c's inline tail has. */
int InitCageFixGeo(void);

#endif /* CAGEFIX_H */
