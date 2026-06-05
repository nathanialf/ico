/* fumi/ios/thread.c — iosThreadMessage parked seed (rc5).
   Struct-filler: f0=0; f4 = iosThreadStart ? &iosThreadStart : &iosThreadInit;
   f8 = &iosThreadStop; fC = &D_0062A4A8 (gp_rel). Registers match (start=v0,
   stop=v1) via if/else + stop-temp + f8-store-early; residual = lui order
   (stop-first vs start-first) + f8 store position (early vs late). Apply, then
   match_loop.py reset iosThreadMessage. */
extern void iosThreadStart(void);
extern int iosThreadInit(void);
extern int D_0062A4A8;

void iosThreadMessage(void **a0) {
    void *s = (void *)iosThreadStop;
    a0[0] = 0;
    a0[2] = s;
    if (iosThreadStart) {
        a0[1] = (void *)iosThreadStart;
    } else {
        a0[1] = (void *)iosThreadInit;
    }
    a0[3] = &D_0062A4A8;
}
