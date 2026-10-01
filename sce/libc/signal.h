/*
 * sce/libc/signal.h
 *
 * PUBLIC NEWLIB NAMING RUNG, as sce/libc/stdio.h: newlib's header of this
 * name declares raise and the reentrant signal layer (signal/signal.c, reent/signalr.c's kill wrapper is libkernl's glue).
 * Each declaration is the definition's in sce/ where that is C, else the
 * spelling its callers carry.  Only what this tree uses is declared.
 */
#ifndef SCE_LIBC_SIGNAL_H
#define SCE_LIBC_SIGNAL_H

int raise(int a0);                      /* definition in sce/ */
int _raise_r(void *ptr, int sig);       /* definition in sce/ */
int _init_signal_r(void *ptr);          /* definition in sce/ */
int __sigtramp_r(void *ptr, int signo); /* definition in sce/ */
int kill(int a0, void *a1);             /* definition in sce/ */

#endif /* SCE_LIBC_SIGNAL_H */
