
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
extern const char D_00554DD0[];
extern const char D_00554DE8[];
extern const char D_00631CD8[];
extern const char D_00631CE0[];
extern const char D_00631CE8[];
extern const char D_00631CF0[];
void func_001A6E28(const char *fmt, ...);
float func_00263FB0(float v);
void func_00118FD8(unsigned char *arg, int slot_size)
{
  int is_float = 0;
  if (((unsigned) slot_size) >= 0x11)
  {
    goto end;
  }
  switch (slot_size)
  {
    case 0:
      func_001A6E28(D_00554DD0, arg);
      is_float = 1;
      slot_size = 4;
      break;

    case 1:

    case 2:

    case 4:

    case 8:

    case 16:
      func_001A6E28(D_00554DE8, arg, slot_size);
      break;

    default:
      return;

  }

  if (slot_size == 0)
  {
    asm volatile("break 0,7");
  }
  {
    int rows;
    int row = 0;
    if ((0x10 / slot_size) <= 0)
    {
      goto end;
    }
    do
    {
      if (is_float == 0)
      {
        int col = slot_size - 1;
        if (col >= 0)
        {
          do
          {
            func_001A6E28(D_00631CD8, arg[(row * slot_size) + col]);
            col--;
          }
          while (col >= 0);
        }
        func_001A6E28(D_00631CE0);
      }
      else
      {
        float v = *((float *) (arg + (row * slot_size)));
        float r = func_00263FB0(v);
        (void) r;
        func_001A6E28(D_00631CE8, r);
      }
      row++;
    }
    while (row < (0x10 / slot_size));
  }
  end:
  func_001A6E28(D_00631CF0);

}

void func_00118F58(void);
void func_00118F98(void);
extern void func_001A2D78(const char *fmt, char *arg, char *ctx);
extern void func_001AD768(const char *str, int len);
extern void func_00263FF0(const char *str, int len, char *ctx);
extern char D_00672FD0[];
extern char D_00631CF8[];
void func_00119470(char *self, int idx);
void func_0011BF40(int a0);
const char D_00554FF8[64] = "\033[31msorce normal model data broken! %f %f %f %f [%d]\033[0m\n";
const char D_005550F8[64] = "\033[31msorce cluster model data broken! %f %f %f %f [%d]\033[0m\n";
const char D_00555378[32] = "\033[31mMaxPacketSize = %d\033[0m\n";
