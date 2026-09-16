/*
 * ico2/sugipon/include/rope.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what rope.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ROPE_H
#define ROPE_H

void SetRopeFixPoint(char *a0, void *a1);
void ropeGeo(void *a0);

#endif /* ROPE_H */
