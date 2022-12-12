#include <stdlib.h>
#include <stdio.h>

int main()
{
    char *str;
    str = malloc(5);
    str[0] = 't';
    // free(str);
    return (0);
}