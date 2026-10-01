/*
 * ico2/common/include/kanbanBoot.h
 *
 * The declarations of what kanbanBoot.c.inc defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef KANBANBOOT_H
#define KANBANBOOT_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order kanbanBoot.c's inline tail has. */
void kanbanBootInit(void);
void kanbanBootStart(void);

/* kanbanBoot.o's .sdata global: set when the boot sequence ends */
extern int kanbanBootEnd;

void kanbanBootMain(void);

#endif /* KANBANBOOT_H */
