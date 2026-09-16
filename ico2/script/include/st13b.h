/*
 * ico2/script/include/st13b.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what st13b.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ST13B_H
#define ST13B_H

void actConte10c(volatile int a0);
void actSt13bBossAfterChk(volatile int a0);
void actSt13bBossChk(volatile int a0);
void actSt13bConte02(volatile int a0);
void actSt13bConte02Jimaku(volatile int a0);
void actSt13bDoorMain(volatile int a0);
void actSt13bDoorSwitch(volatile int a0);
void actSt13bDoorUp(volatile int a0);
void actSt13bDoorUpSub(volatile int a0);
void actSt13bElev2CharaChk(volatile int a0);
void actSt13bElev2Chk(volatile int a0);
void actSt13bElevDown(volatile int a0);
void actSt13bElevDownSub(volatile int a0);
void actSt13bElevMain(volatile int a0);
void actSt13bElevSwitch(volatile int a0);
void actSt13bElevUpChk(volatile int a0);
void actSt13bElevUpSub(volatile int a0);
void actSt13bFloorChk(volatile int a0);
void actSt13bMeetAgainChk(volatile int a0);
void actSt13bMeetAgainSub(volatile int a0);
void actSt13bSekizo2Chk(volatile int a0);
void actSt13bSekizoChk(volatile int a0);

#endif /* ST13B_H */
