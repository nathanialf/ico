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

extern void queen_barrier_anim(void);
extern void queen_barrier_disp_init(void);
extern void queen_barrier_disp_proc(float);
extern void queen_barrier_set_damage(void);

#endif /* QUEEN_BARRIER_DISP_H */
