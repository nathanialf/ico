/* libc.a member makebuf.o */
#include <reent.h>
#include <sys/stat.h>
#include <libc_internal.h>
#include <stdlib.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

/* Only st_mode is reached here, at 0x04; the record is 0x70 bytes, the size
   of the stat buffer in this member's frame.  The trailing bytes are
   padding, not a known field layout. */
#define __SLBF 0x0001
#define __SNBF 0x0002
#define __SOPT 0x0400
#define __SNPT 0x0800
#define __SMOD 0x0080
#define BUFSIZ 1024

/* this member's own declaration; unistd.h declares it as `int isatty(void)` */
extern int isatty(int fd);

void __smakebuf(Fil *fp)
{
    unsigned int size;
    int couldbetty;
    void *p;
    struct stat st;

    if (fp->flags & __SNBF) {
        fp->bf.base = fp->p = fp->nbuf;
        fp->bf.size = 1;
        return;
    }
    if (fp->file < 0 || _fstat_r(fp->data, fp->file, &st) < 0) {
        couldbetty = 0;
        size = BUFSIZ;
        fp->flags |= __SNPT;
    } else {
        couldbetty = (st.st_mode & S_IFMT) == S_IFCHR;
        size = BUFSIZ;
        if ((st.st_mode & S_IFMT) == S_IFREG && fp->seek == __sseek) {
            fp->blksize = size;
            fp->flags |= __SOPT;
        } else {
            fp->flags |= __SNPT;
        }
    }
    if ((p = _malloc_r(fp->data, size)) == 0) {
        fp->flags |= __SNBF;
        fp->bf.base = fp->p = fp->nbuf;
        fp->bf.size = 1;
        return;
    }
    fp->data->cleanup = (void *)_cleanup_r;
    fp->flags |= __SMOD;
    fp->bf.base = fp->p = (unsigned char *)p;
    fp->bf.size = size;
    if (couldbetty && isatty(fp->file)) {
        fp->flags |= __SLBF;
    }
}
