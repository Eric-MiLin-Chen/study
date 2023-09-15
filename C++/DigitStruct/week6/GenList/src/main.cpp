#include "../lib/week6.h"

int main()
{
    char *s = "(b,(b,a,(#),d),((a,b),c,((#))))";
    GeneralList g = s;
    g.DispGL();
    printf("\n");
    printf("广义表长度\t:%d\n", g.GLLength());
    printf("广义表深度\t:%d\n", g.GLDepth());
    printf("原子个数\t:%d\n", g.atomnum());
    return 0;
}