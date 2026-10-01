/*
 * sce/libc/string.h
 *
 * Declarations of the entry points this tree calls, under the public name
 * of the PS2 SDK and newlib header for them (string.h).  Each one is
 * the signature of the member that defines the symbol in sce/.  Nothing here
 * is copied from an SDK header.
 *
 * Only what this tree uses is declared.
 */
#ifndef SCE_LIBC_STRING_H
#define SCE_LIBC_STRING_H

void *memcpy(
    void *dst, const void *src,
    unsigned int
        n); /* newlib's prototype; the game compiles with builtins live, so small fixed copies expand inline */

void *memmove(void *dst, const void *src, unsigned int n);
void *memset(void *dst, int c, unsigned int n);             /* newlib's prototype */
int memcmp(const void *s1, const void *s2, unsigned int n); /* newlib's prototype */
char *strcat(char *dst, const char *src);
int strcmp(const char *a, const char *b);
char *strcpy(char *dst, const char *src);
unsigned int strlen(const char *s);
int strncmp(const char *a, const char *b, unsigned int n);
char *strncpy(char *d, const char *s, unsigned int n);
char *strstr(const char *searchee, const char *lookfor); /* definition in sce/ */
char *strrchr(const char *s, int i);                     /* definition in sce/ */
void *memchr(const void *s, int c, int n);
int strtok_r(int str, int sep, int lastp); /* definition in sce/ */

#endif /* SCE_LIBC_STRING_H */
