/*
 * ico2/sugipon/include/chandelier.h
 *
 * The declarations of what chandelier.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef CHANDELIER_H
#define CHANDELIER_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order chandelier.c's inline tail has. */
int InitChandelierGeo(void);

#endif /* CHANDELIER_H */
