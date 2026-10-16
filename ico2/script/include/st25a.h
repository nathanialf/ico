/*
 * ico2/script/include/st25a.h
 *
 * The declarations of what st25a.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ST25A_H
#define ST25A_H

#include "typedef.h"

struct SqEntry;

void actConte12(GObj *volatile self);
void actConte12Jimaku(GObj *volatile self);
void actConte13Jimaku(GObj *volatile self);
void actSt25aQueenAppearChk(GObj *volatile self);
void actSt25aQueenDeadChk(GObj *volatile self);
void actSt25aQueenTalkChk(GObj *volatile self);
/* st25a.o's .sdata globals: ADPCM request slots */
extern struct SqEntry *conte12;
extern struct SqEntry *sd2;
extern struct SqEntry *dead;
void BoySekikaTexScroll(void);

#endif /* ST25A_H */
