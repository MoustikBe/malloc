#include "includes/main.h"

int main(void)
{
    char *str = ft_malloc(sizeof(char));
    str = "FAILED";
    printf("-> %c\n", str[5]);
}