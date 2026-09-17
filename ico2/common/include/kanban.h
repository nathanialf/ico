/*
 * ico2/common/include/kanban.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what kanban.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef KANBAN_H
#define KANBAN_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order kanban.c's inline tail has. */
void kanbanReqDel(int *self);
void kanbanReqDelFade(int a0);
void kanbanReqAllDel(void);
void kanbanReqAllDelFade(void);
void kanbanExec(void);

void init_textures_of_specified_property(int first, int last);
void kanbanInit(int no);

#endif /* KANBAN_H */
