#include "includes/main.h"

int main(void)
{
    char *str = malloc(sizeof(char) * 100);
    str[0] = 'L';
    printf("-> %c\n", str[0]);
}