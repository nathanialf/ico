/*
 * ico2/ito/include/itou_sub.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what itou_sub.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ITOU_SUB_H
#define ITOU_SUB_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order itou_sub.c's inline tail has. */
void lw_pos_to_ico_pos(float *dst, float *src);
void apply_matrix_w1(void *a0, void *a1, void *a2);
int ico_m33_to_quat(int a0);
void pbga_start(int *self, int *q);

int m33_to_quat(float *q, float (*m)[4]);

#endif /* ITOU_SUB_H */
