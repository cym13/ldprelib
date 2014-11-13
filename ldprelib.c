#include <stdio.h>

/*************************************************/
/* Compile with gcc -o mylib.dylib -fPIC -shared */
/*************************************************/

#define MIN(a,b) ((a)<(b) ? (a) : (b))
#define MAX(a,b) ((a)<(b) ? (b) : (a))

ssize_t strlen(const char* s)
{
    int i;

    printf("[ldpreload] strlen(\"%s\");\n", s);

    for (i=0 ; *(s+i)!=0 ; i++){}
    return i;
}

int strcmp(const char* a, const char* b)
{
    int i;
    printf("[ldpreload] strcmp(\"%s\",\"%s\");\n", a, b);

    for (i=0 ; (*(a+i)!=0) && (*(b+i)!=0) ; i++) {
        if (*(a+i)==*(b+i)) return i+1;
    }

    return i;
}
