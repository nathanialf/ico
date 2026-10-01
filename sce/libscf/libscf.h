/*
 * sce/libscf/libscf.h
 *
 * Declarations of the entry points this tree calls, under the public name
 * of the PS2 SDK and newlib header for them (libscf.h).  Each one is
 * the signature of the member that defines the symbol in sce/.  Nothing here
 * is copied from an SDK header.
 *
 * Only what this tree uses is declared.
 */
#ifndef SCE_LIBSCF_LIBSCF_H
#define SCE_LIBSCF_LIBSCF_H

int sceScfGetLanguage(void);   /* definition in sce/ */
int sceScfGetSummerTime(void); /* definition in sce/ */
int sceScfGetTimeZone(void);   /* definition in sce/ */

#endif /* SCE_LIBSCF_LIBSCF_H */
