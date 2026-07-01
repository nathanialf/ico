
extern int *D_0027DDF0[];
int soundInit(int a0, int val5, int val6);
extern int AdpcmPlay();
extern void func_00258948(void);
extern void func_002589F8(int a0);
extern void func_00259040(int a0, int a1);
extern void func_00259058(int a0, int a1);
extern void func_002590E0(int a0);
extern char D_00551FA0[];
extern char D_00551FB0[];
extern int D_0062A260;
extern int D_0062A4F8;
extern unsigned long long D_0062BFC8;
extern unsigned long long D_0062BFD0;
extern char D_006A3070[];
extern char D_006A3370[];
extern int D_0062A4FC;
extern void func_002590B8(int a0);
void soundAllocIopHeap(int a0);
extern int D_0062A4F0;
extern int func_00259070(int a, int b, int c);
extern int func_00259208(int a, int b, int c);
void soundAllocIopFree(int a0);
extern int new_mblock_node(int a, void *b, int c);
extern void debug_assertMessage();
extern int D_0062A528;
extern char D_00551FC8[];
extern char D_00551FD8[];
extern char D_00551FF0[];
void soundDataOpenChk(void);
extern void func_00246700(int a0);
extern int D_0062A528;
void soundBufAlloc(void);
extern char D_00551FC8[];
extern char D_0062C388[];
extern int D_0062A4E8;
extern int D_0062A4EC;
extern int D_0062BFC0;
extern int D_0062BFC4;
extern void func_001AAD00(char *file, int line);
extern void func_00260380(char *file, int line, char *msg);
void soundDataOpen(int a0, int a1);
extern void func_001AAD00(char *a0, int a1);
extern void func_00260380(char *a0, int a1, char *a2);
extern void AdpcmInterLeaveVolumeSet(int *a0, int a1, int a2, int a3);
extern char D_00551FC8[];
extern char D_0062C388[];
void soundDataClose(int *a0, int a1, int a2, int a3, int a4);
extern void AdpcmVolumeSet(char *a0);
extern void func_00258CF0(int a0);
extern void func_00258FB8(int a0);
extern void func_002593F8(int a0, int a1);
extern void iosMallocCheckLeak2(int a0);
void soundSeVolSet(char *self)
{
  int new_var;
  switch (*((unsigned short *) (self + 4)))
  {
    case 0:
      func_00258CF0(*((int *) (self + 0x28)));
      break;

    case 1:
      if ((*((unsigned long long *) (self + 0x20))) != 0)
    {
      int i;
      do
      {
        i = 0;
      }
      while (0);
      new_var = 0;
      do
      {
        long long mask = 1 << i;
        char *e = D_006A3370 + ((i * 32) * 2);
        if ((*((unsigned long long *) (self + 0x20))) & mask)
        {
          short v = *((short *) (e + 0x10));
          func_002593F8(v, 1);
          func_00258FB8(v);
          {
            char *o = *((char **) (e + 0x30));
            if (o != 0)
            {
              long long t = *((long long *) (o + 0x20));
              if (t & mask)
              {
                long long nt = t & (~mask);
                long long nd = D_0062BFD0 & (~mask);
                unsigned long nc = (*((unsigned short *) e)) + 1;
                *((long long *) (o + 0x20)) = nt;
                D_0062BFD0 = nd;
                *((unsigned short *) e) = nc;
                *((int *) (e + 0x30)) = new_var;
              }
            }
          }
        }
        i++;
      }
      while ((*((unsigned long long *) (self + 0x20))) != new_var);
    }
      func_00258CF0(*((int *) (self + 0x28)));
      iosMallocCheckLeak2(*((int *) (self + 0xC)));
      if ((*((int *) (self + 0x10))) != 0)
    {
      iosMallocCheckLeak2(*((int *) (self + 0x10)));
    }
      break;

    case 2:
      AdpcmVolumeSet(self);
      break;

  }

  *((int *) self) = new_var;
}

extern char D_006A3070[];
extern void soundSeVolSet(char *p);
extern void soundDataOpen(int a0, int a1);
void debug_DispSEInfo(int a0, int a1);
extern void soundSeDefStopNoRelease(int a0, int a1);
void soundSeDefPitchSet(int a0);
void soundReqTickProc(int a0);
extern char D_006A3370[];
extern int func_00259DF8(int a0);
void soundSeEnvPlay(int a0);
extern void debug_assertMessage();
extern void func_001007A0(int a);
extern int func_001008E0(int p, int a);
extern int func_001008C0(int h);
extern char D_00551F50[];
extern char D_00551F68[];
extern char D_00551F80[];
int soundOutputModeGet(int a0, int a1, int a2);
extern int D_0062A4FC;
extern int D_0062A4F0;
int soundReverbDepthGet(void);
int soundBufAdpcmChAlloc(void);
extern unsigned long long D_0062BFC8;
extern char D_00552060[];
extern unsigned long long D_0062BFC8;
void soundDataAreaSearch(void *a0);
char *soundDataAreaGet(int *a0);
extern void func_00260568(void *dst, int val, int size);
inline char *hd_search(char *base, int *pk);
extern int soundSeDefStop(int a0, int a1, int a2, int a3, float f, int t0, int t1);
extern void _soundSeDefStop(int *p);
int soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);
int soundSeDefVolumeRateGet(int a0, int a1, int a2, int a3);
float soundSeDefVolumeRateSet(int a0);
void soundSeGroupStop(int a0, float f);
void soundSeGroupGet(int arg);
extern int D_0062A524;
int soundSePlayModeStop(void);
void soundVBlank(int arg);
extern int func_00259108(int a0, int a1);
extern int D_0062AF94;
extern int D_00271240[];
void soundSeKindBuild(void);
extern void AdpcmStop(char *p);
void soundSeSemiCommonLoadChk(void);
extern char D_002E2A10[];
extern char D_005E44A0[];
void soundSeEnvDefaultSet(int idx);
extern int D_0062A500;
int debug_req(void);
typedef struct 
{
  unsigned int f_0;
  unsigned int f_4;
  short f_10;
  unsigned int f_30;
} S_006A3370;
typedef struct 
{
  unsigned int f_60;
} S_005E1C00;
typedef struct 
{
  unsigned int f_0;
  unsigned short f_2;
} S_006A3070;
typedef struct 
{
  unsigned short f_0;
} S_002E2A10;
typedef struct 
{
  unsigned short f_0;
} S_005E44A0;
typedef struct 
{
  unsigned int f_0;
} S_bl_00551F30;
