/*
 * ico2/common/include/icoMisc.h
 *
 * The declarations of what icoMisc.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ICOMISC_H
#define ICOMISC_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order icoMisc.c's inline tail has. */
void ExitIcoMisc(void);

void DispIcoMisc(void);
void InitIcoMisc();

void disp_memory_partition_bar(void);
void disp_memory_partition(void);
void ExecIcoMisc(void);

/* Six debug words nothing reads. */
extern int dbgC0;
extern int dbgC1;
extern int dbgC2;
extern int dbgC3;
extern int dbgC4;
extern int dbgC5;

#endif /* ICOMISC_H */
