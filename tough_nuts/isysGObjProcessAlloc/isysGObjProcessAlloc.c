extern int D_0062A308;
extern char *D_0062BFB0;
extern int D_0062BFB4;
extern void debug_assertMessage();
extern char D_00551EB8[];
extern char D_00551EE0[];
extern char D_00551EF0[];
extern int iosThreadWakeup();
extern int iosThreadJoin(int handle);

int isysGObjProcessAlloc(int a0, int a1, int a2, int a3, int a4, int a5) {
    int flag = a3 & 0xFF;
    int *mgr = (int *)a0;
    int *slot;
    unsigned int count;
    unsigned int i;

    if (a2 == 0) {
        return 0;
    }

    count = D_0062BFB4;
    i = 0;
    if (count != 0) {
        char *p = D_0062BFB0;
        if (*(int *)p != 0) {
            i++;
            while (i < count) {
                p += 0x94;
                if (*(int *)p == 0) {
                    break;
                }
                i++;
            }
        }
    }

    if (i == count) {
        unsigned int j;
        debug_assertMessage(D_00551EB8);
        debug_assertMessage(D_00551EB8);
        j = 0;
        if (D_0062BFB4 != 0) {
            do {
                int *e = (int *)(j * 0x94 + (int)D_0062BFB0);
                debug_assertMessage(D_00551EE0, e[0], e[7], e[0x17]);
                j++;
            } while (j < D_0062BFB4);
        }
        slot = 0;
    } else {
        slot = (int *)(D_0062BFB0 + i * 0x94);
    }

    if (slot == 0) {
        debug_assertMessage(D_00551EF0);
        return 0;
    }

    slot[0] = (int)slot;
    if (flag == 0) {
        int handle = (int)slot + 0x24;
        iosThreadWakeup(handle, 1, a2, a1 ? a1 : (int)slot, D_0062A308, a5, a4);
        iosThreadJoin(handle);
        slot[7] = 0;
    } else {
        slot[7] = a2;
    }

    {
    int *head = (int *)mgr[0xB];
    slot[4] = flag;
    slot[6] = 1;
    slot[1] = a0;
    slot[5] = a4;
    if (head == 0) {
        slot[3] = 0;
        slot[2] = 0;
        mgr[0xB] = (int)slot;
        mgr[0xC] = (int)slot;
    } else {
        if ((unsigned int)a4 < (unsigned int)head[5]) {
            int *h = (int *)mgr[0xB];
            slot[2] = (int)h;
            slot[3] = 0;
            h[3] = (int)slot;
            mgr[0xB] = (int)slot;
        } else {
            int *tail = (int *)mgr[0xC];
            if ((unsigned int)a4 >= (unsigned int)tail[5]) {
                slot[3] = (int)tail;
                slot[2] = 0;
                tail[2] = (int)slot;
                mgr[0xC] = (int)slot;
            } else {
                int *prev = head;
                int *cur = (int *)head[2];
                while ((unsigned int)a4 >= (unsigned int)cur[5]) {
                    prev = cur;
                    cur = (int *)cur[2];
                }
                slot[3] = (int)prev;
                slot[2] = prev[2];
                prev[2] = (int)slot;
                ((int *)slot[2])[3] = (int)slot;
            }
        }
    }
    }
    return (int)slot;
}
