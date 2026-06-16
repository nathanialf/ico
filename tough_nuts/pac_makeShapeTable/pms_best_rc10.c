/* do-while-r, D48-first: 268 bytes, head->v0, rc10. Residual = do-while BB-split
   prevents the gp-load from interleaving between srl/sll (EXP: srl; lw D48; sll)
   + return-move placement. Proven: sll inside do-while => head v0 but srl/sll
   pinned; sll outside => head v1; D40-load inside between shifts => head v1.
   No do-while content gives head->v0 AND the interleave. Chain gives one-BB
   interleave but +1 (volatile re-read => 272). Need the dev's single-BB head->v0. */
        volatile int * volatile *pp = (volatile int * volatile *)(base + 0x20);
        volatile int *head;
        int c;
        int r;
        /* ... pac_makeMaterialTable(count); calls ... */
        head = *pp;
        c = *(int *)(base + 0x2C);
        *head = 0;
        do { r = ((unsigned int)((c & mask) - (int)head) >> 4) << 4; } while (0);
        (*pp)[1] = 0;
        D_0062BF48 += 1;
        D_0062BF40 += r;
        return r;
