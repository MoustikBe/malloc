#include "includes/main.h"

int main(void)
{
    int *nb = ft_malloc(sizeof(int) * 5);
    for(int i = 0; i < 5; i++){
        nb[i] = i;
        printf("nb -> %d\n", nb[i]);
    }
}