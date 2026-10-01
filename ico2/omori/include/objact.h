/*
 * ico2/omori/include/objact.h
 *
 * The declarations of what objact.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef OBJACT_H
#define OBJACT_H

inline void ObjAction_CorrectGeo(int label, int unused);
void ObjAction_Mail(void *data, int mail);
struct GObj;

void ObjAction_MailCenter(struct GObj *gobj, int step);
void ObjAction_Init(void);


/* One row of obj-trigger: the object a trigger belongs to and the row of
   objTriggerDef that holds its first mail id. */
typedef struct {     /* field names derived */
    int labelId;     /* 0x00, the object's GObj labelId */
    int triggerNo;   /* 0x04, the objTriggerDef row */
} ObjActMailEnt;     /* derived name */

/* The data-only members obj-trigger-def.o and obj-trigger.o: the mail ids
   ObjAction_MailCenter sends, and the object-id to index table it walks. */
extern const int objTriggerDef[];
extern const ObjActMailEnt objTrigger[];

#endif /* OBJACT_H */
