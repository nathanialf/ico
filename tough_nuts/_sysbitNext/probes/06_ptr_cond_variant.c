long long f(unsigned long long*p,int n){long long v;int k;if(p){k=64-n;v=(long long)(*p>>k)<<32;}else{k=64-n;v=(long long)(*p>>k)<<32;}return v>>32;} /* also ROM-exact; same crutch */
