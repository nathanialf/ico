/*
 * ico2/script/include/end.h
 *
 * The declarations of what end.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef END_H
#define END_H

#include "typedef.h"

struct SqEntry;

/* end.o's .sdata globals */
extern struct SqEntry *ed1;

#ifdef VERSION_JUN26
extern struct SqEntry *sea;
#else
extern struct SqEntry *ed2;
extern struct SqEntry *ed3;
extern struct SqEntry *ed4;

#ifdef VERSION_NTSC
extern struct SqEntry *ed5;
extern struct SqEntry *ed6;
#else
#ifdef VERSION_AUG6
extern struct SqEntry *ed5;
extern struct SqEntry *ed6;
extern struct SqEntry *sea;
extern struct SqEntry *happy_end;
#else
extern int ed5;
extern struct SqEntry *ed6;
extern struct SqEntry *sea;
extern int happy_end;
#endif
#endif
#endif

void actConte14_1(GObj *volatile self);
void actConte14_10(GObj *volatile self);
void actConte14_10_Jimaku(GObj *volatile self);
void actConte14_11(GObj *volatile self);
void actConte14_12(GObj *volatile self);
void actConte14_13(GObj *volatile self);
void actConte14_14(GObj *volatile self);
void actConte14_2(GObj *volatile self);
void actConte14_3(GObj *volatile self);
void actConte14_4(GObj *volatile self);
void actConte14_5(GObj *volatile self);
void actConte14_6(GObj *volatile self);
void actConte14_7(GObj *volatile self);

#ifdef VERSION_JUN26
void actConte14_8(GObj *volatile self);
#endif

void actEndDemo01Chk(GObj *volatile self);
void actEndDemo02Chk(GObj *volatile self);
void actEndDemo03Chk(GObj *volatile self);
void actEndDemo04Chk(GObj *volatile self);
void actEndDemo05Chk(GObj *volatile self);
void actEndDemo06Chk(GObj *volatile self);
void actEndDemo07Chk(GObj *volatile self);

#ifdef VERSION_JUN26
void actEndDemo08Chk(GObj *volatile self);
#endif

void actEndDemo10Chk(GObj *volatile self);
void actEndDemo11Chk(GObj *volatile self);
void actEndDemo12Chk(GObj *volatile self);
void actEndDemo13Chk(GObj *volatile self);
void actEndDemo14Chk(GObj *volatile self);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
void actEndLogoFade(GObj *volatile self);
#else
void actEndLogoChk(GObj *volatile self);
#endif

void actSt27aEndChk(GObj *volatile self);
void actSt27aEndDemo(GObj *volatile self);
void actStaff1Chk(GObj *volatile self);
void actStaff1Demo(GObj *volatile self);

#ifndef VERSION_JUN26
void actStaff2Chk(GObj *volatile self);
void actStaff2Demo(GObj *volatile self);
#endif

void actStaff3Chk(GObj *volatile self);
void actStaff3Demo(GObj *volatile self);
void actStaff3RollChk(GObj *volatile self);

#endif /* END_H */
