extern int iosMsgSend(void *a, void *b, int c, int d);
extern int D_0027D308[];
typedef union { long long ll; int w[2]; } McHdr;

int iosMcSaveIconBlock(void *a0) {
    McHdr *h = (McHdr *)a0;
    h->w[1] = 7;
    h->ll &= -2;
    return iosMsgSend(D_0027D308, a0, 0, -2);
}
