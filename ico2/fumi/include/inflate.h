/*
 * ico2/fumi/include/inflate.h
 *
 * The declarations of what inflate.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef INFLATE_H
#define INFLATE_H

/* reads up to size bytes of compressed data into buf */
typedef long long (*InflateReadFn)(void *buf, long long size, void *handle); /* derived name */
void close_inflate_handler(void *a0);
long long inflate(void *w, unsigned char *out, long long outlen);
void *open_inflate_handler(InflateReadFn read, void *handle);

#endif /* INFLATE_H */
