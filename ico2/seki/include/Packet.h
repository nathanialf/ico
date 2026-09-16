/*
 * ico2/seki/include/Packet.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what Packet.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef PACKET_H
#define PACKET_H

extern void pac_DispQW(void *p, int size);
extern void pac_Init(void);
extern void pac_MakePacket(char *a0);
extern void pac_makePacket(void *a0, int a1, int a2);

#endif /* PACKET_H */
