long long f(unsigned long long*p,int n){return (long long)(*p>>(64-n))<<32>>32;}   /* 6 words: combine folds to extendsidi2 = move */
