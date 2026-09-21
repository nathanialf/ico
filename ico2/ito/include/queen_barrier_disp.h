/*
 * ico2/ito/include/queen_barrier_disp.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what queen_barrier_disp.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef QUEEN_BARRIER_DISP_H
#define QUEEN_BARRIER_DISP_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order queen_barrier_disp.c's inline tail has. */
void queen_barrier_anim(void);

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order queen_barrier_disp.c's inline tail has. */

void queen_barrier_disp_init(void);
void queen_barrier_disp_proc(char *g, float k);
void queen_barrier_set_damage(void);

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record, previously repeated character for character in 2 TUs. */
typedef union {
    float f[4];
    long long ll[2];
} QVec;

#endif /* QUEEN_BARRIER_DISP_H */
