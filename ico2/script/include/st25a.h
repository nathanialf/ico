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

#ifndef VERSION_NTSC
extern const char faceShadowTex[];
extern const char faceShadowTex00[];
#endif

#ifdef VERSION_JUN26
extern const char wall01Tex[];
#endif

/* st25a.o's .sdata globals: ADPCM request slots */
extern struct SqEntry *conte12;
extern struct SqEntry *sd2;
extern struct SqEntry *dead;
void BoySekikaTexScroll(void);

#ifndef VERSION_NTSC
#ifdef VERSION_JUN26
extern ActMail queen_before_mes[]; /* st25a.o .data: the queen-before actor mail list */

void actSt25aQueenBeforeChk(
    GObj *volatile self); /* the handler scpObj1882 puts in queen_before_mes */
#else
extern ActMail queen_appear_mes[]; /* st25a.o .data: the queen-appear actor mail list */
#endif
#endif

#endif /* ST25A_H */
