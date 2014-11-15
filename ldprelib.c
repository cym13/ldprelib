#include <stdio.h>

/*************************************************/
/* Compile with gcc -o mylib.dylib -fPIC -shared */
/*************************************************/

// Coroutines
#define BEGIN    static int state=0; switch (state) { case 0:
#define YIELD(x) do { state=__LINE__; return x; case __LINE__:; } while(0);
#define FINISH   }

#define MIN(a,b) ((a)<(b) ? (a) : (b))
#define MAX(a,b) ((a)<(b) ? (b) : (a))

ssize_t strlen(const char* s)
{
    int i;

    for (i=0 ; *(s+i)!=0 ; i++){}

    fprintf(stderr, "[ldpreload] strlen(\"%s\") = %d\n", s, i);
    return i;
}

int strcmp(const char* a, const char* b)
{
    int i;

    for (i=0 ; (*(a+i)!=0) && (*(b+i)!=0) ; i++) {
        if (*(a+i)==*(b+i)) return i+1;
    }

    fprintf(stderr, "[ldpreload] strcmp(\"%s\",\"%s\") = %d\n", a, b, i);
    return i;
}

void* memcpy(void* dest, const void* src, size_t len)
{
    const char *s = src;
    char *d = dest;
    size_t i = len;

    while (i-- > 0)
      *d++ = *s++;

    fprintf(stderr, "[ldpreload] memcpy(%x, %x, %d) = %x",
                                      dest, src, len, dest);

    return dest;
}

void* memccpy(void* dest, const void* src, int c, size_t n)
{
    const char *s = src;
    char *d = dest;
    size_t i = n;
    const char x = c;
    void* ret = NULL;

    while (i-- > 0)
      if ((*d++ = *s++) == x) {
        ret = d;
        break;
      }

    fprintf(stderr, "[ldpreload] memccpy(%x, %x, %d, %d) = %x",
                                        dest, src, c, n, ret);

    return ret;
}

int rand_r(unsigned int *seed)
{
    unsigned int next = *seed;
    int result;

    next *= 1103515245;
    next += 12345;
    result = (unsigned int) (next / 65536) % 2048;

    next *= 1103515245;
    next += 12345;
    result <<= 10;
    result ^= (unsigned int) (next / 65536) % 1024;

    next *= 1103515245;
    next += 12345;
    result <<=10;
    result ^= (unsigned int) (next / 65536) % 1024;

    fprintf(stderr, "[ldpreload] rand_r(%d) = %d\n", *seed, result);

    *seed = next;

    return result;
}
