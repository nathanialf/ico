long long f(unsigned long long*p,int n){return (long long)(int)(*p>>(64-n));}      /* 8 words: truncdisi2 + move-in-slot */
