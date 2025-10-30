#include "includes/main.h"

int main(void)
{
    char *str = malloc(sizeof(char));
    str = "FAILED";
    printf("-> %c\n", str[5]);
}