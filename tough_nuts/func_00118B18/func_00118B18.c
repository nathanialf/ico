
const char D_00554FD0[16] = "src/Packet.c";
const char D_00555038[24] = "pac_makeNormalStrip";
const char D_00555050[24] = "pac_getWeight(0)";
const char D_00555068[24] = "pac_getWeight(1)";
const char D_00555080[24] = "pac_getWeight(2)";
const char D_00555138[24] = "pac_makeClusterStrip";
const char D_005551E0[16] = "GIFTAG    :";
const char D_00555308[32] = "pac_countOneVertexPacketSize";
const char D_00554EE0[48] = "IN %s\n%s:NoTexture Polygon(s) exist(s).\n";
const char D_00554F10[48] = "IN %s\n%s:NoNormal Cluster Model exists.\n";
const char D_00554F40[48] = "IN %s\n%s:Abnormal Weight Data exist(s).\n";
const char D_00554F70[56] = "IN %s\n%s:Too Much Weight (>=4) Vertex exist(s).\n";
const char D_00554FA8[40] = "IN %s\n%s:No Weight Vertex exist(s).\n";
const char D_00555098[56] = "vertex has 3 cluster-weights %d(%f) %d(%f) %d(%f)\n";
const char D_005550D0[40] = "warning:weight total %f VtxIdx:%d\n";
const char D_00555150[32] = "over 60 skeltons exist.\n";
const char D_00555170[32] = "color table not exists.\n";
const char D_00555190[16] = "DMAOPEN   :%p\n";
const char D_005551A0[32] = "VIFUNPACK :%08x %08x (%p:%d)\n";
const char D_005551F0[40] = "pac_continueTag:Packet too small. %d\n";
const char D_00555218[40] = "Original Strip Too Long. Size %d\n";
const char D_00555240[24] = "size(0x%x) strips(%d)\n";
const char D_00555258[16] = "--- cut ---\n\n";
const char D_00555268[56] = "gif over! cut! %d/%d polys:%d/%d fchain:%d vif+gif:%d\n";
const char D_005552A0[24] = "chain too long! cut!\n";
const char D_005552B8[48] = "pac_copyStrip:No Enough Memory for Packet.\n";
const char D_005552E8[32] = "ALL:src:%p => dst:%p (size:%x)\n";
const char D_00555328[40] = "pac_makeStrip:No Memory To Convert.\n";
const char D_00555350[40] = "pac_makeStrip:No Tex Poly Exists.%s\n";
const char D_00555398[88] = "IN OBJECT \"%s\"\nHUGE PACKET (SIZE:0x%x) APPEARED\nMAYBE INFLATE MEMORY AREA WAS BROKEN.\n";
const char D_005553F0[48] = "pac_makeTextureTable:\n\tTexture not Found. %s\n";
const char D_00555420[56] = "pac_makePacket:Material Table Not Found. (%s:%s)\n";
const char D_00555458[24] = "illegal size = %d\n";
const char D_00555470[32] = "illegal vertex num %d\n";
extern int D_00672F90[];
extern int D_00633C3C;
extern int D_004C7710[];
void func_001FBA80(int v);
void func_001FBAA8(int a, void *p, int zero);
void func_001FB8B8(void);
void func_00118B18(int count, int arg)
{
  int *p;
  int v;
  int *new_var2;
  int *new_var;
  int a;
  p = (int *) D_004C7710[4];
  D_004C7710[6] = 0;
  D_004C7710[3] = (D_004C7710[5] = (int) p);
  D_004C7710[7] = 0;
  *((long long *) p) = 0x10000000LL;
  D_004C7710[4] = (int) (p - (-2));
  if (((unsigned) (count - 1)) < 5)
  {
    int *cp;
    new_var2 = (cp = 0);
    switch (count - 1)
    {
      case 0:

      case 1:
        cp = (int *) D_004C7710[4];
        *cp = 0x03000100;
        a = 0x02000180;
        break;

      case 2:
        cp = (int *) D_004C7710[4];
        *cp = 0x03000100;
        a = 0x02000180;
        asm __volatile__("" : "+r"(cp));
        break;
        new_var = D_004C7710;

      case 3:
        cp = new_var[4];
        *cp = 0x03000010;
        a = 0x020001F8;
        break;
        cp += 1;

      case 4:
        cp = (int *) D_004C7710[4];
        *cp = 0x03000010;
        a = 0x0200016A;
        break;

    }

    D_004C7710[4] = (int) cp;
    *new_var2 = a;
    D_004C7710[4] = (int) (cp + 1);
    D_004C7710[6] = 0;
  }
  {
    int *q = (int *) D_004C7710[4];
    D_004C7710[5] = (int) q;
    *q = 0x60000000LL;
    D_004C7710[4] = q + 2;
    q[2] = 0;
    D_004C7710[4] = (int) (q + 3);
    q[3] = 0;
    D_004C7710[4] = (int) (q + 4);
  }
  func_001FBA80(arg);
  func_001FBAA8(5, (void *) D_004C7710[3], 0);
  func_001FB8B8();
}

void func_00118F58(void);
void func_00118F98(void);
extern void func_001A2D78(const char *fmt, char *arg, char *ctx);
extern void func_001AD768(const char *str, int len);
extern void __assert(const char *str, int len, char *ctx);
extern char D_00672FD0[];
extern char D_00631CF8[];
void func_00119470(char *self, int idx);
void func_0011BF40(int a0);
const char D_00554FF8[64] = "\033[31msorce normal model data broken! %f %f %f %f [%d]\033[0m\n";
const char D_005550F8[64] = "\033[31msorce cluster model data broken! %f %f %f %f [%d]\033[0m\n";
const char D_00555378[32] = "\033[31mMaxPacketSize = %d\033[0m\n";
