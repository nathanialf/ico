/*
 * ico2/script/include/st25a.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what st25a.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
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
/* MAIN.MAP globals of st25a.o's .sdata: ADPCM request slots */
extern char *conte12;
extern char *sd2;
extern char *dead;
void BoySekikaTexScroll(void);

#endif /* ST25A_H */
