#include "GobjProc.h"
#include "way_sys.h"

/* PAL's manager object word is not in this build: the TU has no .sdata in
   the demo */

/* void * (void *, int) here, void (int, int) in act.h */
extern void *actCreateSubThreadGOppArg(void *entry, int arg);
/* as in act.h, which this file does not include */
extern void _ACTWait(int frames);

#include "waySystemManager.h"

static void actWaySystemCore(volatile unsigned int self);
static void thStart(void);

static inline void actWaySystemCore(volatile unsigned int self)
{
    WayRequest *s = (WayRequest *)((int *)self)[0x20 / 4];
    s->result = _FUNC_GetWay_begin(s->from, &s->way, s->goal, 1);
    s->done = 1;
    s->proc = 0;
}

static inline void thStart(void)
{
    for (;;) {
        _ACTWait(1);
    }
}
