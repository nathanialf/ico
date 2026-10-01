/*
 * ico2/common/include/kanbanBoot.h
 *
 * The declarations of what kanbanBoot.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef KANBANBOOT_H
#define KANBANBOOT_H

/* kanbanBoot.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order). */
void kanbanBootInit(void);
void kanbanBootStart(void);
/* kanbanBoot.o's .sdata global: set when the boot sequence ends */
extern int kanbanBootEnd;
void kanbanBootMain(void);

#endif /* KANBANBOOT_H */
