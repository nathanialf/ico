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

extern void apply_matrix_w1(void *a0, void *a1, void *a2);
extern int ico_m33_to_quat(int a0);
extern void lw_pos_to_ico_pos(float *dst, float *src);
extern int m33_to_quat(float *q, float (*m)[4]);
extern void pbga_start(int *self, int *q);

#endif /* ITOU_SUB_H */
