/*
 * sce/libc/string.h
 *
 * PUBLIC SDK NAMING RUNG.  The disc attests no declaration-only header: a
 * header that only declares leaves no instruction in SRCFILE.TXT and no
 * symbol in MAIN.MAP, so neither its name nor its contents can be read off
 * the ROM.  What places this file is the public naming of the PS2 SDK and of
 * newlib, whose header for these entry points is called string.h and whose
 * archive is this directory's; the declarations themselves are the tree's
 * own facts, each one either the signature of the member that defines the
 * symbol in sce/ or, where the member is still an assembled stub, the
 * spelling the calling TUs already carried and which keeps every one of them
 * byte-identical.  Nothing here is copied from an SDK header.
 *
 * Only what this tree uses is declared.
 */
#ifndef SCE_LIBC_STRING_H
#define SCE_LIBC_STRING_H

void *memcpy(void *dst, const void *src, unsigned int n); /* newlib's prototype; the game compiled with builtins live, and the ROM's aligned six-byte copy in layout_action is the builtin expansion */
void *memmove(void *dst, const void *src, unsigned int n);
/* The return type is ROM bytes, not naming: a non-void return makes gcc emit
 * call_value, so the unused $2 is marked live at the call insn and the next
 * quantity born there is pushed off $2. sce/libsndn2/sound.c
 * SgGetSpuSlotMalloc only matches with it, and all 106 call sites stay
 * byte-identical either way. */
void *memset(void *dst, int c, unsigned int n); /* newlib's prototype */
char *strcat(char *dst, const char *src);
int strcmp(const char *a, const char *b);
char *strcpy(char *dst, const char *src);                /* dominant spelling at 10 sites */
unsigned int strlen(const char *s);
int strncmp(const char *a, const char *b, unsigned int n);
char *strncpy(char *d, const char *s, unsigned int n);
char *strstr(const char *searchee, const char *lookfor); /* definition in sce/ */

#endif /* SCE_LIBC_STRING_H */
