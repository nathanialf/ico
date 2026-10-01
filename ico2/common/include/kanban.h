/*
 * ico2/common/include/kanban.h
 *
 * The declarations of what kanban.c defines, for the files that use
 * them.  The file name is derived.
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

/* kanban.o's .sdata global */
extern int kanbanCommonRead;

struct Node;
void display_layout(struct Node *k);

#endif /* KANBAN_H */
