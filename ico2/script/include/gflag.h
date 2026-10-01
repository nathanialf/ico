/*
 * ico2/script/include/gflag.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what gflag.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef GFLAG_H
#define GFLAG_H

int gflagChk(int bit_idx);
void gflagInit(void);
void gflagOff(int bit_idx);
void gflagOn(int bit_idx);

/* gflag.o's .sdata: the game-clear state and the stage the save was made on
 * (gFlagSaveStage is MAIN.MAP's) */
extern int gFlagGameClear;
extern int gFlagSaveStage;

void gflagSave(void *fp);
void gflagLoad(void *fp);

#endif /* GFLAG_H */
