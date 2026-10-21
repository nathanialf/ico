/*
 * ico2/sugipon/include/clipCollisionManager.h
 *
 * The declarations of what clipCollisionManager.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef CLIPCOLLISIONMANAGER_H
#define CLIPCOLLISIONMANAGER_H

#include "typedef.h"

struct GObj;

/* A clip run on the clip-collision thread: the clip, the function that runs
 * it (ClipWall, ClipFloor or one of the actors' own pairs), the object kept
 * out of it while it runs, and the flag set when it is done.  The actors keep
 * one in their work (act-game.c's view clip at ActWork 0x720, the flyer's at
 * 0x690 of its actor record). */
typedef struct ClipColReq {       /* field names derived */
    int done;                     /* 0x00 */
    char pad04[12];
    ClipWork clip;                /* 0x10 */
    struct GObj *obj;             /* 0xD0, hidden (disp 0) while the clip runs */
    void (*func)(ClipWork *clip); /* 0xD4 */
} ClipColReq;                     /* derived name */

#endif /* CLIPCOLLISIONMANAGER_H */
