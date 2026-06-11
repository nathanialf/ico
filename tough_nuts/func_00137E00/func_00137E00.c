extern int iosMsgSend(void *a, void *b, int c, int d);
extern int D_0027D308[];
typedef union { long long ll; int w[2]; } McHdr;

int func_00137E00(void *a0) {
    McHdr *h;
    McHdr *hp;
    int v;
    h = (McHdr *)a0;
    do { v = 9; hp = h; } while (0);
    hp->w[1] = v;
    h->ll &= -2;
    return iosMsgSend(D_0027D308, a0, 0, -2);
}
