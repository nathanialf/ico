/*
 * ico2/script/include/st25a.h
 *
 * The declarations of what st25a.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ST25A_H
#define ST25A_H

#include "typedef.h"

void actConte12(GObj *volatile a0);
void actConte12Jimaku(GObj *volatile a0);
void actConte13Jimaku(GObj *volatile a0);
void actSt25aElevCharaChk(GObj *volatile a0);
void actSt25aElevChk(GObj *volatile a0);
void actSt25aQueenAppearChk(GObj *volatile a0);
void actSt25aQueenDeadChk(GObj *volatile a0);
void actSt25aQueenTalkChk(GObj *volatile a0);
extern const char faceShadowTex[];
extern const char faceShadowTex00[];
/* st25a.o's .sdata globals: ADPCM request slots */
extern char *conte12;
extern char *sd2;
extern char *dead;
void BoySekikaTexScroll(void);

extern ActMail queen_appear_mes[]; /* st25a.o .data: the queen-appear actor mail list */

#endif /* ST25A_H */
