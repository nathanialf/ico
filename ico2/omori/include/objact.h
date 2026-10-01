/*
 * ico2/omori/include/objact.h
 *
 * The declarations of what objact.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef OBJACT_H
#define OBJACT_H

inline void ObjAction_CorrectGeo(int a0, int a1);
void ObjAction_Mail(void *a0, int a1);
void ObjAction_MailCenter(void *a0, int a1);
void ObjAction_Init(void);


typedef struct { /* field names derived */
    int id;
    int idx;
} ObjActMailEnt;

/* The data-only members obj-trigger-def.o and obj-trigger.o: the mail ids
   ObjAction_MailCenter sends, and the object-id to index table it walks. */
extern const int objTriggerDef[];
extern const ObjActMailEnt objTrigger[];

#endif /* OBJACT_H */
