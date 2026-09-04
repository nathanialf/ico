extern void debug_StdPrintfDummy();
extern char D_00551F18[];

void isysGObjProcAdd(int *self) {
    int *owner;
    if (self == 0) {
        debug_StdPrintfDummy(D_00551F18);
        return;
    }
    if (self[3] != 0) goto do_prev;
    if (self[2] == 0) goto head;
    goto merge;
do_prev:
    ((int *)self[3])[2] = self[2];
merge:
    if (self[2] != 0) {
        ((int *)self[2])[3] = self[3];
    }
head:
    owner = (int *)self[1] + 0xB;
    if ((int)self == owner[0]) owner[0] = self[2];
    if ((int)self == owner[1]) owner[1] = self[3];
}
