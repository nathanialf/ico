/*
 * ico2/ito/include/queen_barrier_disp.h
 *
 * The declarations of what queen_barrier_disp.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef QUEEN_BARRIER_DISP_H
#define QUEEN_BARRIER_DISP_H

void queen_barrier_anim(void);


void queen_barrier_disp_init(void);
void queen_barrier_disp_proc(struct GObj *g, float k);
void queen_barrier_set_damage(void);

/* a quadword read as four floats or as two doublewords */
typedef union { /* field names derived */
    float f[4];
    long long ll[2];
} __attribute__((aligned(16))) QVec;

#endif /* QUEEN_BARRIER_DISP_H */
