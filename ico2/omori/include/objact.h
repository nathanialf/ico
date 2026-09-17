/*
 * ico2/omori/include/objact.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what objact.c.inc defines, in the order the
 * coalescing TU's prototype block carried them; every type here is read from
 * the ROM's calling convention at the call sites.
 */

#ifndef OBJACT_H
#define OBJACT_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order objact.c's inline tail has. */
void ObjAction_CorrectGeo(int a0, int a1);
void ObjAction_Mail(void *a0, int a1);
void ObjAction_MailCenter(void *a0, int a1);
void ObjAction_Init(void);

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order objact.c's inline tail has. */

#endif /* OBJACT_H */
