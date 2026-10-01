/*
 * ico2/fumi/include/inflate.h
 *
 * The declarations of what inflate.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef INFLATE_H
#define INFLATE_H

void close_inflate_handler(void *a0);
long long inflate(void *w, unsigned char *out, long long outlen);
int inflate_dynamic(void *w, unsigned char *out, long long outlen);
long long inflate_fixed(void *w, unsigned char *out, long long outlen);
long long inflate_stored(void *w, unsigned char *out, long long outlen);
int open_inflate_handler(int a0, int a1);

#endif /* INFLATE_H */
