/*
 * ico2/sugipon/include/spider.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what spider.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef SPIDER_H
#define SPIDER_H

int CheckSpidersInsideOfReviveRange(int *out, char *gp, void *center);
int DeadAllSpiders(char *gp);
void DeleteAllSpidersOfLayoutGroup(char *gp);
char *DeleteSpiderFromLayoutGroup(char *a0, int a1);
void DispAllMemberOfSpider(char *self, int *col);
int GetAliveSpiders(char *gp);
void SetSpiderGroupReviveStatus(char *a0);
void SleepSpiderGroup(char *gp);
void WakeUpLayoutedSpiders(void *self);
void WakeupSpiderGroup(char *gp);

#endif /* SPIDER_H */
