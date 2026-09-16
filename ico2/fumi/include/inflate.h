/*
 * ico2/fumi/include/inflate.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what inflate.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef INFLATE_H
#define INFLATE_H

extern void close_inflate_handler(void *a0);
extern long long inflate(void *w, unsigned char *out, long long outlen);
extern int inflate_dynamic(void *w, unsigned char *out, long long outlen);
extern long long inflate_fixed(void *w, unsigned char *out, long long outlen);
extern long long inflate_stored(void *w, unsigned char *out, long long outlen);
extern int open_inflate_handler(int a0, int a1);

#endif /* INFLATE_H */
