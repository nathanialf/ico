/*
 * ico2/seki/include/MicroCode.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what MicroCode.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef MICROCODE_H
#define MICROCODE_H

void mc_Reset(void);
void mc_SetMicroCode();
void mc_TransMicroCode(int a0, int a1);
void mc_setBaseOffset(int base, int pri);

#endif /* MICROCODE_H */
