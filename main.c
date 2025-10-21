#include "includes/main.h"

int main(void)
{
    char *str = ft_malloc(sizeof(char) * 10);
    str[5] = '1';
    printf("%c\n", str[5]);
    return(0);
}