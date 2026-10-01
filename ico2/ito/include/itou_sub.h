/*
 * ico2/ito/include/itou_sub.h
 *
 * The declarations of what itou_sub.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ITOU_SUB_H
#define ITOU_SUB_H

void lw_pos_to_ico_pos(float *dst, float *src);
void apply_matrix_w1(void *a0, void *a1, void *a2);
int ico_m33_to_quat(void *q, void *m);
void pbga_start(int **slot, int key);
int m33_to_quat(float *q, float (*m)[4]);

#endif /* ITOU_SUB_H */
