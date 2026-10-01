/*
 * ico2/ito/include/mv_main.h
 *
 * The declarations of what mv_main.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef MV_MAIN_H
#define MV_MAIN_H

int movie_init(char *name, int imageW, int imageH, int dbx, int dby, int mono, int clearCol);
void movie_end(void);
int movie_proc(int (*poll)(void));
void switchThread(void);

#endif /* MV_MAIN_H */
