/* fumi/ios/thread.c — iosThreadMessage parked seed (rc2, permuter-improved from rc5).
   f0 store after the if/else (permuter-found). Residual rc2: gcc shares one %hi base
   for the same-TU symbols iosThreadStart/Stop/Init (addiu +offset) vs ROM's per-symbol
   %hi/%lo relocs — genuinely different bytes (ninja fails). Re-attack: force per-symbol
   %hi/%lo (the same-TU shared-%hi is the floor). Apply + match_loop.py reset. */
extern void iosThreadStart(void);
extern void iosThreadStop(unsigned char *a0);
extern int iosThreadInit(void);
extern int D_0062A4A8;

void iosThreadMessage(void **a0) {
    void *s = (void *)iosThreadStop;
    a0[2] = s;
    if (iosThreadStart) {
        a0[1] = (void *)iosThreadStart;
    } else {
        a0[1] = (void *)iosThreadInit;
    }
    a0[0] = 0;
    a0[3] = &D_0062A4A8;
}
