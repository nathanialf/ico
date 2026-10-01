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
typedef struct InflateHandler InflateHandler; /* derived name */
void close_inflate_handler(InflateHandler *h);
long long inflate(InflateHandler *w, unsigned char *out, long long outlen);
InflateHandler *open_inflate_handler(InflateReadFn read, void *handle);

#endif /* INFLATE_H */
