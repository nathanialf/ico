/*
 * ico2/ito/include/mv_vibuf.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what mv_vibuf.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef MV_VIBUF_H
#define MV_VIBUF_H

void viBufAddDMA();
void viBufBeginPut(void *self, void **addr1, int *size1, void **addr2, int *size2);
int viBufCount(int *self);
int viBufCreate(void *self);
void viBufDelete();
void viBufEndPut(int *self, int a1);
void viBufFlush(int *self);
void viBufGetTs();
int viBufReset();
void viBufRestartDMA();
void viBufStopDMA();

#endif /* MV_VIBUF_H */
