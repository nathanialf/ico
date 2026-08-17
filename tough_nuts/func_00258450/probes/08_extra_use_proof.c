extern long long D_x; long long f(unsigned long long*p,int n){long long v=(long long)(*p>>(64-n))<<32;D_x=v;return v>>32;} /* an extra USE of the <<32 value also defeats the fold - but costs an sd */
