/*
 * ico2/seki/include/MicroCode.h
 *
 * The declarations of what MicroCode.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef MICROCODE_H
#define MICROCODE_H

/* MicroCode.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order). */
void mc_TransMicroCode(int a0, int a1);
void mc_Reset(void);
void mc_Init(void);
void mc_SetMicroCode(int mode, int a1, int a2, int a3, int pri);
/* MicroCode.c's one .data object, read from DisplayP2O.c as well: the VU1
   microprogram address per microprogram id. */
extern int MicroCodeAddress[];

#endif /* MICROCODE_H */
