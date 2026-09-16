/*
 * ico2/omori/include/ebrain.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what ebrain.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef EBRAIN_H
#define EBRAIN_H

extern int GetStageFromLabel(int label);
extern void *eBrainGetTarget(char *self);
extern int eBrainGetTargetGeneratorFromLabel(int label);
extern void eBrainInit(void);
extern void eBrainSendMes(void *gop, int mes);

#endif /* EBRAIN_H */
