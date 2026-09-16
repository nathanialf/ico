/*
 * ico2/fumi/include/act-parallel-control.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what act-parallel-control.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ACT_PARALLEL_CONTROL_H
#define ACT_PARALLEL_CONTROL_H

int *ActPara_GetDefTbl(void);
void ActPara_InitSystem(void);
void ActPara_MakeTbl(int *tbl, unsigned long long mask, int n);

#endif /* ACT_PARALLEL_CONTROL_H */
