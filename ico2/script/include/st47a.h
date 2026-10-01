/*
 * ico2/script/include/st47a.h
 *
 * The declarations of what st47a.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ST47A_H
#define ST47A_H

#include "typedef.h"

/* st47a.o's .sdata globals */
extern char *sekizo47a;
extern char *hane1up;
extern char *hane2up;
extern char *hane1down;
extern char *hane2down;
extern int sekizo_47a;
extern unsigned char sekizo_47a_vol;
void actSt47aBarricadeChk(GObj *volatile a0);
void actSt47aEneChk(GObj *volatile a0);
void actSt47aExit2Chk(GObj *volatile a0);
void actSt47aExitChk(GObj *volatile a0);
void actSt47aGirlWay(GObj *volatile a0);
void actSt47aHane1Down(GObj *volatile a0);
void actSt47aHane1Main(GObj *volatile a0);
void actSt47aHane1Switch(GObj *volatile a0);
void actSt47aHane1Up(GObj *volatile a0);
void actSt47aHane1_1Girl(GObj *volatile a0);
void actSt47aHane1_2Girl(GObj *volatile a0);
void actSt47aHane2Down(GObj *volatile a0);
void actSt47aHane2Girl(GObj *volatile a0);
void actSt47aHane2Main(GObj *volatile a0);
void actSt47aHane2Switch(GObj *volatile a0);
void actSt47aHane2Up(GObj *volatile a0);
void actSt47aHint2OnChk(GObj *volatile a0);
void actSt47aRopeChk(GObj *volatile a0);
void actSt47aRopeSub(GObj *volatile a0);
void actSt47aSekizo1Chk(GObj *volatile a0);

#endif /* ST47A_H */
