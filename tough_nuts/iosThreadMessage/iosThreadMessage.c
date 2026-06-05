/* fumi/ios/thread.c — iosThreadMessage parked seed (rc5). */
extern void iosThreadStart(void);
extern void iosThreadStop(unsigned char *a0);
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
